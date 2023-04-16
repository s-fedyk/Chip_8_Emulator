//
// Created by Stanislav Fedyk on 2023-04-12.
//
#include "Cpu.h"
#include "Instruction/InstructionFactory.h"

Cpu::Cpu(GraphicsAdapter *graphics, InputAdapter *input)
{
    // zero out registers
    memset(this->registers, 0x00, sizeof(uint8_t) * 16);

    this->graphics = graphics;
    this->input = input;
    this->i = 0;

    this->load_rom();
    this->start();
}

void Cpu::start()
{
    // jump by twos since a single instruciton is 16-bit
    for (this->pc; this->pc < 1024; this->pc+=2) {
        uint8_t pressed_key = this->input->poll_for_input_no_blocking();

        if (pressed_key == 0xFF) {
            return;
        }

        uint16_t instruction = load(this->pc);
        // registers are uint_4
        uint8_t x_register = (instruction & 0x0F00) >> 8;
        uint8_t y_register = (instruction & 0x00F0) >> 4;
        // mem-addr is actually uint_12 but cpp doesnt have this
        uint16_t mem_addr = (instruction & 0x0FFF);
        // sprite number is  uint_4
        uint8_t nth_sprite = (instruction & 0x000F);
        uint8_t constant = (instruction & 0x00FF);

        Instruction result = decode(instruction);
        if (result == Instruction::Undecoded) {
            std::cout << "Decode failure, aborting\n";
            return;
        }

        if (execute(result, x_register, y_register, mem_addr, nth_sprite, constant, pressed_key) < 0) {
            std::cout << "Execute failure, aborting\n";
            return;
        }
    }
}
/** Fetches next instruction
 *
 * @param address
 * @return
 */
uint16_t Cpu::load(uint16_t address)
{
    uint16_t high = this->memory[address] << 8;
    uint16_t low = this->memory[address + 1];

    return high+low;
}

int Cpu::execute(Instruction instruction,
                 uint8_t x_register,
                 uint8_t y_register,
                 uint16_t mem_addr,
                 uint8_t nth_sprite,
                 uint8_t constant,
                 uint8_t key_press)
{
    switch (instruction) {
        case Instruction::ClearScreen:
            this->graphics->clear();
            std::cout << "clearing screen\n";
            break;
        case Instruction::Return:
            break;
        case Instruction::JumpToAddressAt:
            this->pc = mem_addr - 2; // minus two because we increment by two right after this function
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
            this->registers[x_register] += constant;
            break;
        case Instruction::LoadXWithValueInY:
            this->registers[x_register] = this->registers[y_register];
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
            break;
        case Instruction::JumpLocationPlusV0:
            break;
        case Instruction::SetXRandomByteANDKK:
            break;
        case Instruction::DrawNthSpriteAtXYSetCollision:
            this->graphics->draw_sprite(this->registers[x_register], this->registers[y_register],&this->memory[i],nth_sprite);
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
Instruction Cpu::decode(uint16_t instruction)
{
    return InstructionFactory::create(instruction);
}
/** Load the rom into memory
 *
 */
void Cpu::load_rom()
{
    std::ifstream f1 ("rom.ch8", std::ios::binary);

    // zero out residual mem
    memset(this->memory, 0, 1024*sizeof(uint8_t));
    // font copying
    memcpy(this->memory, this->FONTS, 80 * sizeof(uint8_t));

    int index = 0x200;

    // rom loading.
    for (auto start = std::istreambuf_iterator<char>{ f1 }, end = std::istreambuf_iterator<char>{}; start != end; ++start) {
        this->memory[index] = (uint8_t) *start;
        index+=1;
    }

    for (index = 0; index < 1024; index+=1) {
        std::cout << std::hex << (int) this->memory[i] << ' ' << i << '\n';
    }

    f1.close();
}

