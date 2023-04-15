//
// Created by Stanislav Fedyk on 2023-04-12.
//
#ifndef UNTITLED1_CPU_H
#define UNTITLED1_CPU_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Instruction/InstructionFactory.h"
#include "Adapter/GraphicsAdapter.h"


class Cpu {
public:
    uint8_t memory[4096];
    uint16_t registers[16];
    uint16_t i;
    uint16_t stack[16];
    uint16_t pc = 0x200; // program starts at 200. store sprites and stuff before that
    GraphicsAdapter *graphics;

    Cpu(GraphicsAdapter *graphics);
    void load_rom();
    void test_decode();
    void start();
    Instruction decode(uint16_t instruction);
    int execute(Instruction instruction, uint8_t x_register, uint8_t y_register, uint16_t mem_addr, uint8_t nth_sprite, uint8_t constant);
    uint16_t load(uint16_t);

private:
    // chip8 has a base sprite set for hex chars
    const uint8_t FONTS[80] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                       0x20, 0x60, 0x20, 0x20, 0x70, // 1
                       0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                       0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                       0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                       0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                       0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                       0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                       0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                       0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                       0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                       0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                       0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                       0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                       0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                       0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
};



#endif //UNTITLED1_CPU_H
