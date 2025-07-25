// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <cstdint>

namespace N64
{

// Forward declarations
class MIPSState;
class MIPSCore;

/**
 * MIPSInterpreter
 *
 * Pure interpreter for MIPS R4300i instructions. This class handles
 * instruction decoding and execution in a straightforward manner.
 */
class MIPSInterpreter
{
public:
    explicit MIPSInterpreter(MIPSCore* core);
    ~MIPSInterpreter();

    // Execute a single instruction
    void ExecuteInstruction(uint32_t instruction);

    // Execute multiple instructions
    void ExecuteInstructions(int count);

    // Get the core this interpreter belongs to
    MIPSCore* GetCore() const { return m_core; }

private:
    MIPSCore* m_core;
    MIPSState* m_state;

    // Instruction execution methods
    void ExecuteRType(uint32_t instruction);
    void ExecuteIType(uint32_t instruction);
    void ExecuteJType(uint32_t instruction);
    void ExecuteCoprocessor(uint32_t instruction);

    // R-Type instruction handlers
    void ADD(uint32_t rs, uint32_t rt, uint32_t rd);
    void ADDU(uint32_t rs, uint32_t rt, uint32_t rd);
    void SUB(uint32_t rs, uint32_t rt, uint32_t rd);
    void SUBU(uint32_t rs, uint32_t rt, uint32_t rd);
    void AND(uint32_t rs, uint32_t rt, uint32_t rd);
    void OR(uint32_t rs, uint32_t rt, uint32_t rd);
    void XOR(uint32_t rs, uint32_t rt, uint32_t rd);
    void NOR(uint32_t rs, uint32_t rt, uint32_t rd);
    void SLT(uint32_t rs, uint32_t rt, uint32_t rd);
    void SLTU(uint32_t rs, uint32_t rt, uint32_t rd);
    void SLL(uint32_t rt, uint32_t rd, uint32_t shamt);
    void SRL(uint32_t rt, uint32_t rd, uint32_t shamt);
    void SRA(uint32_t rt, uint32_t rd, uint32_t shamt);
    void SLLV(uint32_t rs, uint32_t rt, uint32_t rd);
    void SRLV(uint32_t rs, uint32_t rt, uint32_t rd);
    void SRAV(uint32_t rs, uint32_t rt, uint32_t rd);
    void JR(uint32_t rs);
    void JALR(uint32_t rs, uint32_t rd);
    void SYSCALL();
    void BREAK();
    void MFHI(uint32_t rd);
    void MTHI(uint32_t rs);
    void MFLO(uint32_t rd);
    void MTLO(uint32_t rs);
    void MULT(uint32_t rs, uint32_t rt);
    void MULTU(uint32_t rs, uint32_t rt);
    void DIV(uint32_t rs, uint32_t rt);
    void DIVU(uint32_t rs, uint32_t rt);

    // I-Type instruction handlers
    void ADDI(uint32_t rs, uint32_t rt, uint16_t immediate);
    void ADDIU(uint32_t rs, uint32_t rt, uint16_t immediate);
    void SLTI(uint32_t rs, uint32_t rt, uint16_t immediate);
    void SLTIU(uint32_t rs, uint32_t rt, uint16_t immediate);
    void ANDI(uint32_t rs, uint32_t rt, uint16_t immediate);
    void ORI(uint32_t rs, uint32_t rt, uint16_t immediate);
    void XORI(uint32_t rs, uint32_t rt, uint16_t immediate);
    void LUI(uint32_t rt, uint16_t immediate);
    void LB(uint32_t rs, uint32_t rt, uint16_t offset);
    void LH(uint32_t rs, uint32_t rt, uint16_t offset);
    void LW(uint32_t rs, uint32_t rt, uint16_t offset);
    void LBU(uint32_t rs, uint32_t rt, uint16_t offset);
    void LHU(uint32_t rs, uint32_t rt, uint16_t offset);
    void SB(uint32_t rs, uint32_t rt, uint16_t offset);
    void SH(uint32_t rs, uint32_t rt, uint16_t offset);
    void SW(uint32_t rs, uint32_t rt, uint16_t offset);
    void BEQ(uint32_t rs, uint32_t rt, uint16_t offset);
    void BNE(uint32_t rs, uint32_t rt, uint16_t offset);
    void BLEZ(uint32_t rs, uint16_t offset);
    void BGTZ(uint32_t rs, uint16_t offset);
    void BLTZ(uint32_t rs, uint16_t offset);
    void BGEZ(uint32_t rs, uint16_t offset);
    void BLTZAL(uint32_t rs, uint16_t offset);
    void BGEZAL(uint32_t rs, uint16_t offset);

    // J-Type instruction handlers
    void J(uint32_t target);
    void JAL(uint32_t target);

    // Helper methods
    uint32_t SignExtend16(uint16_t value) const;
    uint32_t SignExtend8(uint8_t value) const;
    bool IsBranchTaken(uint32_t rs, uint32_t rt, uint32_t opcode) const;
    void UpdatePC(uint32_t new_pc);
};

} // namespace N64
