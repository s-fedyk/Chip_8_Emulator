cmake_minimum_required(VERSION 3.23)
project(Chip_8_Emulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chip_8_Emulator ${MY_SOURCES} main.cpp Emulator/Cpu.cpp Emulator/Cpu.h Emulator/Instruction/InstructionFactory.cpp Emulator/Instruction/InstructionFactory.h)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

target_link_libraries(Chip_8_Emulator PRIVATE SDL2::SDL2)
include_directories(${SDL2_INCLUDE_DIR})
