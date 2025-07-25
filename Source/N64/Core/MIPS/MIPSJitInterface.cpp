// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MIPSJitInterface.h"
#include "MIPSCore.h"
#include "MIPSState.h"

namespace N64
{

MIPSJitInterface::MIPSJitInterface(MIPSCore* core)
    : m_core(core), m_state(nullptr)
{
}

MIPSJitInterface::~MIPSJitInterface() = default;

} // namespace N64
