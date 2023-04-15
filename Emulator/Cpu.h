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
    uint16_t pc = 0;
    GraphicsAdapter *graphics;

    Cpu(GraphicsAdapter *graphics);
    void load_rom();
    void test_decode();
    void start();
    Instruction decode(uint16_t instruction);
    void execute(Instruction instruction, uint8_t x_register, uint8_t y_register, uint16_t mem_addr, uint8_t nth_sprite);
    uint16_t load(uint16_t);
};



#endif //UNTITLED1_CPU_H
