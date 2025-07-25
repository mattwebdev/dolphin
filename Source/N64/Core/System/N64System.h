// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>
#include <string>

#include "Core/System.h"

namespace N64
{

/**
 * N64 System Implementation
 *
 * This class provides the main system interface for N64 emulation,
 * extending the base Core::System class with N64-specific functionality.
 */
class N64System : public Core::System
{
public:
    N64System();
    ~N64System() override;

    // Initialize the N64 system
    bool Initialize();

    // Static initialization for the N64 system components
    static bool Initialize();
    static void Shutdown();

    // N64-specific system methods
    bool IsN64() const override { return true; }
    std::string GetConsoleType() const override { return "N64"; }

private:
    // N64-specific system state
    bool m_initialized = false;
};

} // namespace N64
