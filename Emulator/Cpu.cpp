//
// Created by Stanislav Fedyk on 2023-04-12.
//
#include "Cpu.h"

Cpu::Cpu(GraphicsAdapter *graphics, InputAdapter *input)
{
    // zero out registers
    memset(this->registers, 0x00, sizeof(uint8_t) * 16);

    this->graphics = graphics;
    this->input = input;

    this->load_rom();
    this->start();
}

void Cpu::start()
{
    memset(this->keyboard,0, 16*sizeof(bool));
    // jump by twos since a single instruciton is 16-bit
    for (this->pc; this->pc < 4096; this->pc+=2) {
        if (this->input->poll_for_input_no_blocking(this->keyboard) < 0) {
            break;
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

        if (execute(result, x_register, y_register, mem_addr, nth_sprite, constant) < 0) {
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
                 uint8_t constant)
{
    switch (instruction) {
        case Instruction::ClearScreen:
            this->graphics->clear();
            break;
        case Instruction::Return:
            this->pc = this->stack[this->sp - 1];
            this->sp -= 1;
            break;
        case Instruction::JumpToAddressAt:
            this->pc = mem_addr - 2; // minus two because we increment by two right after this function
            break;
        case Instruction::CallAddressAt:
            this->stack[this->sp] = this->pc;
            this->sp += 1;
            this->pc = mem_addr - 2;
            break;
        case Instruction::SkipNextXEqualsConstant:
            if (this->registers[x_register] == constant) {
                this->pc += 2;
            }
            break;
        case Instruction::SkipNextXNotEqualsConstant:
            if (this->registers[x_register] != constant) {
                this->pc += 2;
            }
            break;
        case Instruction::SkipNextXEqualsY:
            if (this->registers[x_register] == this->registers[y_register]) {
                this->pc += 2;
            }
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
            this->registers[x_register] = this->registers[x_register] | this->registers[y_register];
            break;
        case Instruction::AndXWithY:
            this->registers[x_register] = this->registers[x_register] & this->registers[y_register];
            break;
        case Instruction::XORXWithY:
            this->registers[x_register] = this->registers[x_register] ^ this->registers[y_register];
            break;
        case Instruction::AddXWithYSetCarry:
            this->fc = (uint16_t(this->registers[x_register] + this->registers[y_register]) > 255) ? 0x01 : 0x00;
            this->registers[x_register] = (this->registers[x_register] + this->registers[y_register]);
            this->registers[15] = this->fc;
            break;
        case Instruction::SubXWithYSetBorrow:
            this->fc = (this->registers[x_register] > this->registers[y_register]) ? 0x01 : 0x00;
            this->registers[x_register] = this->registers[x_register] - this->registers[y_register];
            this->registers[15] = this->fc;
            break;
        case Instruction::DivideByTwoSetCarry:
            this->fc = ((bool)(this->registers[x_register] & 0x01)) ? 0x01 : 0x00;
            this->registers[x_register] = this->registers[x_register] >> 1;
            this->registers[15] = this->fc;
            break;
        case Instruction::SubYWithXSetBorrow:
            this->fc = (this->registers[y_register] > this->registers[x_register]) ? 0x01 : 0x00;
            this->registers[x_register] = this->registers[y_register] - this->registers[x_register];
            this->registers[15] = this->fc;
            break;
        case Instruction::MultiplyXByTwoSetCarry:
            this->fc = ((this->registers[x_register] & 0x80) > 0x00) ? 0x01 : 0x00;
            this->registers[x_register] = this->registers[x_register] << 1;
            this->registers[15] = this->fc;
            break;
        case Instruction::SkipNextInstructionXNotEqualY:
            if (this->registers[x_register] != this->registers[y_register]) {
                this->pc += 2;
            }
            break;
        case Instruction::LoadIWithAddress:
            this->i = mem_addr;
            break;
        case Instruction::JumpLocationPlusV0:
            this->pc = this->registers[0] + mem_addr - 2;
            break;
        case Instruction::SetXRandomByteANDKK:
            break;
        case Instruction::DrawNthSpriteAtXYSetCollision:
            if(this->graphics->draw_sprite(this->registers[x_register],
                                        this->registers[y_register],
                                        &this->memory[i],
                                        nth_sprite)) {
                this->registers[15] = 0x01;
            }
            break;
        case Instruction::SkipNextInstructionKeyXPressed:
            if (this->keyboard[this->registers[x_register]]) {
                this->pc += 2;
            }
            break;
        case Instruction::SkipNextInstructionKeyXNotPressed:
            if (!this->keyboard[this->registers[x_register]]) {
                this->pc += 2;
            }
            break;
        case Instruction::PlaceIntoXDelayTimer:
            break;
        case Instruction::WaitAndPlaceKeyIntoX:
            this->registers[x_register] = this->input->poll_for_input_blocking();
            break;
        case Instruction::SetDelayTimerToX:
            break;
        case Instruction::SetSoundTimerToX:
            break;
        case Instruction::AddXToI:
            this->i += this->registers[x_register];
            break;
        case Instruction::SetIToSpriteAtDigitX:
            break;
        case Instruction::StoreBCDOfXAtI:
            this->memory[i] = (this->registers[x_register] / 100);
            this->memory[i+1] = ((this->registers[x_register] % 100) / 10);
            this->memory[i+2] = (this->registers[x_register] % 100) % 10;
            break;
        case Instruction::StoreRegistersStartingFromXAtI:
            for (uint8_t register_index = 0 ; register_index <= x_register; ++register_index) {

                this->memory[this->i+register_index] = this->registers[register_index];
            }
            break;
        case Instruction::ReadIIntoRegistersStartingFromXAtI:
            for (uint8_t register_index = 0; register_index <= x_register; ++register_index) {
                this->registers[register_index] = this->memory[this->i+register_index];
            }
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
    memset(this->memory, 0, 4096*sizeof(uint8_t));
    // font copying
    memcpy(this->memory, this->FONTS, 80 * sizeof(uint8_t));

    int index = 0x200;

    // rom loading.
    for (auto start = std::istreambuf_iterator<char>{ f1 }, end = std::istreambuf_iterator<char>{}; start != end; ++start) {
        this->memory[index] = (uint8_t) *start;
        index+=1;
    }

    f1.close();
}

