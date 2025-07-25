// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <cstdint>

namespace N64
{

class MIPSCore;
class MIPSState;

/**
 * MIPSJitInterface
 *
 * Interface for JIT compilation of MIPS R4300i instructions.
 */
class MIPSJitInterface
{
public:
    explicit MIPSJitInterface(MIPSCore* core);
    virtual ~MIPSJitInterface();

    // Compile and execute a single instruction
    virtual void ExecuteInstruction(uint32_t instruction) = 0;

    // Compile and execute multiple instructions
    virtual void ExecuteInstructions(int count) = 0;

    // Get the core this JIT belongs to
    MIPSCore* GetCore() const { return m_core; }

protected:
    MIPSCore* m_core;
    MIPSState* m_state;
};

} // namespace N64
