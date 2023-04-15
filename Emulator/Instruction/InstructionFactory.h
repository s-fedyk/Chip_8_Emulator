//
// Created by Stanislav Fedyk on 2023-04-13.
//

#ifndef UNTITLED1_INSTRUCTIONFACTORY_H
#define UNTITLED1_INSTRUCTIONFACTORY_H
#include <cstdint>
enum Instruction {
    Undecoded,
    ClearScreen = 0x00E0,
    Return = 0x00EE,
    JumpToAddressAt = 0x1000, //1nnn
    CallAddressAt = 0x2000,//2nnn
    SkipNextXEqualsConstant = 0x3000,//3xkk
    SkipNextXNotEqualsConstant = 0x4000, //4xkk
    SkipNextXEqualsY = 0x5000,//5xy0
    LoadXWithValue = 0x6000, //6xkk
    AddXWithValue = 0x7000,//7xkk
    LoadXWithValueInY= 0x8000,//8xy0
    OrXWithY = 0x8001,//8xy1
    AndXWithY = 0x8002,//8xy2
    XORXWithY = 0x8003,//8xy3
    AddXWithYSetCarry = 0x8004,//8xy4
    SubXWithYSetBorrow= 0x8005,//8xy5
    DivideByTwoSetCarry = 0x8006,//8xy6
    SubYWithXSetBorrow = 0x8007,//8xy7
    MultiplyXByTwoSetCarry = 0x800E,//8xyE
    SkipNextInstructionXNotEqualY = 0x9000,//9xy0
    LoadIWithAddress = 0xA000,//Annn
    JumpLocationPlusV0 = 0xB000,//Bnnn
    SetXRandomByteANDKK = 0xC000,//Cxkk
    DrawNthSpriteAtXYSetCollision = 0xD000,//Dxyn
    SkipNextInstructionKeyXPressed = 0xE09E,//Ex9E
    SkipNextInstructionKeyXNotPressed = 0xE0A1,//ExA1
    PlaceIntoXDelayTimer = 0xF007,//Fx07
    WaitAndPlaceKeyIntoX = 0xF00A,//Fx0A
    SetDelayTimerToX = 0xF015,//Fx15
    SetSoundTimerToX = 0xF018,//Fx18
    AddXToI = 0xF01E,//Fx1E
    SetIToSpriteAtDigitX = 0xF029,//Fx29
    StoreBCDOfXAtI = 0xF033,//Fx33
    StoreRegistersStartingFromXAtI = 0xF055,//Fx55
    ReadIIntoRegistersStartingFromXAtI = 0xF065//Fx65
};

class InstructionFactory {
public:
    static Instruction create(uint16_t instruction);
};




#endif //UNTITLED1_INSTRUCTIONFACTORY_H
