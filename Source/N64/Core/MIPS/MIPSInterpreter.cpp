// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MIPSInterpreter.h"
#include "MIPSCore.h"
#include "MIPSState.h"

namespace N64
{

MIPSInterpreter::MIPSInterpreter(MIPSCore* core)
    : m_core(core), m_state(nullptr) // Will be set up in Initialize
{
}

MIPSInterpreter::~MIPSInterpreter() = default;

void MIPSInterpreter::ExecuteInstruction(uint32_t instruction)
{
    // TODO: Decode and execute a single instruction
}

void MIPSInterpreter::ExecuteInstructions(int count)
{
    // TODO: Loop and execute multiple instructions
}

void MIPSInterpreter::ExecuteRType(uint32_t instruction) { /* TODO */ }
void MIPSInterpreter::ExecuteIType(uint32_t instruction) { /* TODO */ }
void MIPSInterpreter::ExecuteJType(uint32_t instruction) { /* TODO */ }
void MIPSInterpreter::ExecuteCoprocessor(uint32_t instruction) { /* TODO */ }

// R-Type instruction handlers (stubs)
void MIPSInterpreter::ADD(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::ADDU(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SUB(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SUBU(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::AND(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::OR(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::XOR(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::NOR(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SLT(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SLTU(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SLL(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SRL(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SRA(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SLLV(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SRLV(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::SRAV(uint32_t, uint32_t, uint32_t) {}
void MIPSInterpreter::JR(uint32_t) {}
void MIPSInterpreter::JALR(uint32_t, uint32_t) {}
void MIPSInterpreter::SYSCALL() {}
void MIPSInterpreter::BREAK() {}
void MIPSInterpreter::MFHI(uint32_t) {}
void MIPSInterpreter::MTHI(uint32_t) {}
void MIPSInterpreter::MFLO(uint32_t) {}
void MIPSInterpreter::MTLO(uint32_t) {}
void MIPSInterpreter::MULT(uint32_t, uint32_t) {}
void MIPSInterpreter::MULTU(uint32_t, uint32_t) {}
void MIPSInterpreter::DIV(uint32_t, uint32_t) {}
void MIPSInterpreter::DIVU(uint32_t, uint32_t) {}

// I-Type instruction handlers (stubs)
void MIPSInterpreter::ADDI(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::ADDIU(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::SLTI(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::SLTIU(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::ANDI(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::ORI(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::XORI(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::LUI(uint32_t, uint16_t) {}
void MIPSInterpreter::LB(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::LH(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::LW(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::LBU(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::LHU(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::SB(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::SH(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::SW(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::BEQ(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::BNE(uint32_t, uint32_t, uint16_t) {}
void MIPSInterpreter::BLEZ(uint32_t, uint16_t) {}
void MIPSInterpreter::BGTZ(uint32_t, uint16_t) {}
void MIPSInterpreter::BLTZ(uint32_t, uint16_t) {}
void MIPSInterpreter::BGEZ(uint32_t, uint16_t) {}
void MIPSInterpreter::BLTZAL(uint32_t, uint16_t) {}
void MIPSInterpreter::BGEZAL(uint32_t, uint16_t) {}

// J-Type instruction handlers (stubs)
void MIPSInterpreter::J(uint32_t) {}
void MIPSInterpreter::JAL(uint32_t) {}

// Helper methods (stubs)
uint32_t MIPSInterpreter::SignExtend16(uint16_t value) const { return static_cast<int16_t>(value); }
uint32_t MIPSInterpreter::SignExtend8(uint8_t value) const { return static_cast<int8_t>(value); }
bool MIPSInterpreter::IsBranchTaken(uint32_t, uint32_t, uint32_t) const { return false; }
void MIPSInterpreter::UpdatePC(uint32_t) {}

} // namespace N64
