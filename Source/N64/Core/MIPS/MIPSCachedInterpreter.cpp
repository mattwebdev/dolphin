// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MIPSCachedInterpreter.h"
#include "MIPSCore.h"
#include "MIPSState.h"

namespace N64
{

MIPSCachedInterpreter::MIPSCachedInterpreter(MIPSCore* core)
    : m_core(core), m_state(nullptr)
{
}

MIPSCachedInterpreter::~MIPSCachedInterpreter() = default;

void MIPSCachedInterpreter::ExecuteInstruction(uint32_t instruction)
{
    // TODO: Decode and execute a single instruction using cache
}

void MIPSCachedInterpreter::ExecuteInstructions(int count)
{
    // TODO: Loop and execute multiple instructions using cache
}

} // namespace N64
