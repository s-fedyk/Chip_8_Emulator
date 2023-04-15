//
// Created by Stanislav Fedyk on 2023-04-13.
//

#include "InstructionFactory.h"

Instruction InstructionFactory::create(uint16_t instruction) {
    if (instruction == Instruction::ClearScreen)
    {
        return Instruction::ClearScreen;
    }
    else if (instruction == Instruction::Return) {
        return Instruction::Return;
    }
    else if ((instruction & 0xF000) == Instruction::JumpToAddressAt) {
        return Instruction::JumpToAddressAt;
    }
    else if ((instruction & 0xF000) == Instruction::CallAddressAt) {
        return Instruction::CallAddressAt;
    }
    else if ((instruction & 0xF000) == Instruction::SkipNextXEqualsConstant) {
        return Instruction::SkipNextXEqualsConstant;
    }
    else if ((instruction & 0xF000) == Instruction::SkipNextXNotEqualsConstant) {
        return Instruction::SkipNextXNotEqualsConstant;
    }
    else if ((instruction & 0xF00F) == Instruction::SkipNextXEqualsY) {
        return Instruction::SkipNextXEqualsY;
    }
    else if ((instruction & 0xF000) == Instruction::LoadXWithValue) {
        return Instruction::LoadXWithValue;
    }
    else if ((instruction & 0xF000) == Instruction::AddXWithValue) {
        return Instruction::AddXWithValue;
    }
    else if ((instruction & 0xF00F) == Instruction::LoadXWithValueInY) {
        return Instruction::LoadXWithValueInY;
    }
    else if ((instruction & 0xF00F) == Instruction::OrXWithY) {
        return Instruction::OrXWithY;
    }
    else if ((instruction & 0xF00F) == Instruction::AndXWithY) {
        return Instruction::AndXWithY;
    }
    else if ((instruction & 0xF00F) == Instruction::XORXWithY) {
        return Instruction::XORXWithY;
    }
    else if ((instruction & 0xF00F) == Instruction::AddXWithYSetCarry) {
        return Instruction::AddXWithYSetCarry;
    }
    else if ((instruction & 0xF00F) == Instruction::SubXWithYSetBorrow) {
        return Instruction::SubXWithYSetBorrow;
    }
    else if ((instruction & 0xF00F) == Instruction::DivideByTwoSetCarry) {
        return Instruction::DivideByTwoSetCarry;
    }
    else if ((instruction & 0xF00F) == Instruction::SubYWithXSetBorrow) {
        return Instruction::SubYWithXSetBorrow;
    }
    else if ((instruction & 0xF00F) == Instruction::MultiplyXByTwoSetCarry) {
        return Instruction::MultiplyXByTwoSetCarry;
    }
    else if ((instruction & 0xF00F) == Instruction::SkipNextInstructionXNotEqualY) {
        return Instruction::SkipNextInstructionXNotEqualY;
    }
    else if ((instruction & 0xF000) == Instruction::LoadIWithAddress) {
        return Instruction::LoadIWithAddress;
    }
    else if ((instruction & 0xF000) == Instruction::JumpLocationPlusV0) {
        return Instruction::JumpLocationPlusV0;
    }
    else if ((instruction & 0xF000) == Instruction::SetXRandomByteANDKK) {
        return Instruction::SetXRandomByteANDKK;
    }
    else if ((instruction & 0xF000) == Instruction::DrawNthSpriteAtXYSetCollision) {
        return Instruction::DrawNthSpriteAtXYSetCollision;
    }
    else if ((instruction & 0xF0FF) == Instruction::SkipNextInstructionKeyXPressed) {
        return Instruction::SkipNextInstructionKeyXPressed;
    }
    else if ((instruction & 0xF0FF) == Instruction::SkipNextInstructionKeyXNotPressed) {
        return Instruction::SkipNextInstructionKeyXNotPressed;
    }
    else if ((instruction & 0xF0FF) == Instruction::PlaceIntoXDelayTimer) {
        return Instruction::PlaceIntoXDelayTimer;
    }
    else if ((instruction & 0xF0FF) == Instruction::WaitAndPlaceKeyIntoX) {
        return Instruction::WaitAndPlaceKeyIntoX;
    }
    else if ((instruction & 0xF0FF) == Instruction::SetDelayTimerToX) {
        return Instruction::SetDelayTimerToX;
    }
    else if ((instruction & 0xF0FF) == Instruction::SetSoundTimerToX) {
        return Instruction::SetSoundTimerToX;
    }
    else if ((instruction & 0xF0FF) == Instruction::AddXToI) {
        return Instruction::AddXToI;
    }
    else if ((instruction & 0xF0FF) == Instruction::SetIToSpriteAtDigitX) {
        return Instruction::SetIToSpriteAtDigitX;
    }
    else if ((instruction & 0xF0FF) == Instruction::StoreBCDOfXAtI) {
        return Instruction::StoreBCDOfXAtI;
    }
    else if ((instruction & 0xF0FF) == Instruction::StoreRegistersStartingFromXAtI) {
        return Instruction::StoreRegistersStartingFromXAtI;
    }
    else if ((instruction & 0xF0FF) == Instruction::ReadIIntoRegistersStartingFromXAtI) {
        return Instruction::ReadIIntoRegistersStartingFromXAtI;
    }
}
