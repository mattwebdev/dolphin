// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <cstdint>

namespace N64
{

class MIPSCore;
class MIPSState;

/**
 * MIPSCachedInterpreter
 *
 * Implements a cached interpreter for the MIPS R4300i, providing a balance
 * between pure interpretation and JIT compilation.
 */
class MIPSCachedInterpreter
{
public:
    explicit MIPSCachedInterpreter(MIPSCore* core);
    ~MIPSCachedInterpreter();

    // Execute a single instruction (cached)
    void ExecuteInstruction(uint32_t instruction);

    // Execute multiple instructions
    void ExecuteInstructions(int count);

    // Get the core this cached interpreter belongs to
    MIPSCore* GetCore() const { return m_core; }

private:
    MIPSCore* m_core;
    MIPSState* m_state;

    // TODO: Add cache structures and logic
};

} // namespace N64
