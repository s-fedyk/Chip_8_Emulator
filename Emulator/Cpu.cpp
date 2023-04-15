//
// Created by Stanislav Fedyk on 2023-04-12.
//
#include "Cpu.h"
#include "Instruction/InstructionFactory.h"
#define MEMORY_LENGTH 512;

Cpu::Cpu(GraphicsAdapter *graphics) {
    // zero out registers
    for(int i = 0; i < 16; i ++) {
        this->registers[i] = 0;
    }

    this->graphics = graphics;
    this->load_rom();
    this->start();
}

void Cpu::start() {
    // jump by twos since a single instruciton is 16-bit
    for (this->pc; this->pc < 512; this->pc+=2) {
        uint16_t instruction = load(this->pc);

        // registers are 4-bit
        uint8_t x_register = (instruction & 0x0F00) >> 8;
        uint8_t y_register = (instruction & 0x00F0) >> 4;
        // mem-addr is actually 12-bit max
        uint16_t mem_addr = (instruction & 0x0FFF);
        // sprite number is 0-15 decimal
        uint8_t nth_sprite = (instruction & 0x000F);

        uint8_t constant = (instruction & 0x00FF);

        if (execute(decode(instruction), x_register, y_register, mem_addr, nth_sprite, constant) < 0) {
            std::cout << "decode failure\n";
            break;
        }
    }
}
/** Fetches next instruction
 *
 * @param address
 * @return
 */
uint16_t Cpu::load(uint16_t address) {
    uint16_t high = this->memory[address] << 8;
    uint16_t low = this->memory[address + 1];

    return high+low;
}

int Cpu::execute(Instruction instruction, uint8_t x_register, uint8_t y_register, uint16_t mem_addr, uint8_t nth_sprite, uint8_t constant) {
    switch (instruction) {
        case Instruction::ClearScreen:
            this->graphics->clear();
            std::cout << "clearing screen\n";
            break;
        case Instruction::Return:
            break;
        case Instruction::JumpToAddressAt:
            std:: cout << "jumping\n";
            break;
        case Instruction::CallAddressAt:
            break;
        case Instruction::SkipNextXEqualsConstant:
            break;
        case Instruction::SkipNextXNotEqualsConstant:
            break;
        case Instruction::SkipNextXEqualsY:
            break;
        case Instruction::LoadXWithValue:
            this->registers[x_register] = constant;
            break;
        case Instruction::AddXWithValue:
            std::cout << "adding x with value\n";
            break;
        case Instruction::LoadXWithValueInY:
            break;
        case Instruction::OrXWithY:
            break;
        case Instruction::AndXWithY:
            break;
        case Instruction::XORXWithY:
            break;
        case Instruction::AddXWithYSetCarry:
            break;
        case Instruction::SubXWithYSetBorrow:
            break;
        case Instruction::DivideByTwoSetCarry:
            break;
        case Instruction::SubYWithXSetBorrow:
            break;
        case Instruction::MultiplyXByTwoSetCarry:
            break;
        case Instruction::SkipNextInstructionXNotEqualY:
            break;
        case Instruction::LoadIWithAddress:
            this->i = mem_addr;
            std::cout << "loading i with value\n";
            break;
        case Instruction::JumpLocationPlusV0:
            break;
        case Instruction::SetXRandomByteANDKK:
            break;
        case Instruction::DrawNthSpriteAtXYSetCollision:
            std::cout << " drawing at  " << this->registers[x_register] << " " << this->registers[y_register] << std::endl;
            this->graphics->draw(this->registers[x_register], this->registers[y_register]);
            break;
        case Instruction::SkipNextInstructionKeyXPressed:
            break;
        case Instruction::SkipNextInstructionKeyXNotPressed:
            break;
        case Instruction::PlaceIntoXDelayTimer:
            break;
        case Instruction::WaitAndPlaceKeyIntoX:
            break;
        case Instruction::SetDelayTimerToX:
            break;
        case Instruction::SetSoundTimerToX:
            break;
        case Instruction::AddXToI:
            break;
        case Instruction::SetIToSpriteAtDigitX:
            break;
        case Instruction::StoreBCDOfXAtI:
            break;
        case Instruction::StoreRegistersStartingFromXAtI:
            break;
        case Instruction::ReadIIntoRegistersStartingFromXAtI:
            break;
        default:
            return -1;
    }
    return 0;
}

/** Given a uint, assemble it into an instruction
 *
 * @return
 */
Instruction Cpu::decode(uint16_t instruction) {
    return InstructionFactory::create(instruction);
}
/** Load the rom into memory
 *
 */
void Cpu::load_rom() {
    std::ifstream f1 ("rom.ch8", std::ios::binary);

    // zero out residual mem (do i even have to do this?)
    for (i = 0; i < 512; ++i){
        this->memory[i] = 0x00;
    }
    int index = 0;

    // rom loading.
    for (auto start = std::istreambuf_iterator<char>{ f1 }, end = std::istreambuf_iterator<char>{}; start != end; ++start) {
        this->memory[index] = (uint8_t) *start;
        index+=1;
    }

    for (i = 0; i < 512; i+=1) {
        //std::cout << std::hex << (int) this->memory[i] << ' ' << i << '\n';
    }

    f1.close();
}

