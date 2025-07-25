// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <array>
#include <cstdint>

namespace N64
{

/**
 * MIPSState
 *
 * Represents the full state of the MIPS R4300i CPU, including general-purpose registers,
 * program counter, coprocessor registers, and FPU state.
 */
class MIPSState
{
public:
    static constexpr size_t NUM_GPR = 32;
    static constexpr size_t NUM_FPR = 32;
    static constexpr size_t NUM_CP0 = 32;
    static constexpr size_t NUM_CP1 = 32;

    MIPSState();
    ~MIPSState();

    void Reset();

    // General-purpose registers
    std::array<uint32_t, NUM_GPR> gpr{};
    uint32_t pc = 0;
    uint32_t hi = 0;
    uint32_t lo = 0;

    // Coprocessor 0 (System Control)
    std::array<uint32_t, NUM_CP0> cp0{};

    // Coprocessor 1 (FPU)
    std::array<uint64_t, NUM_FPR> fpr{};
    std::array<uint32_t, NUM_CP1> fcr{};

    // TODO: Add more state as needed (TLB, etc)
};

} // namespace N64
