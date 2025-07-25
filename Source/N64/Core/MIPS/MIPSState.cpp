// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MIPSState.h"

namespace N64
{

MIPSState::MIPSState()
{
    Reset();
}

MIPSState::~MIPSState() = default;

void MIPSState::Reset()
{
    gpr.fill(0);
    pc = 0;
    hi = 0;
    lo = 0;
    cp0.fill(0);
    fpr.fill(0);
    fcr.fill(0);
    // TODO: Reset additional state as needed
}

} // namespace N64
