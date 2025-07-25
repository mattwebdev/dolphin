// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <string>

namespace N64
{

/**
 * N64 Configuration Management
 *
 * This class handles N64-specific configuration settings and initialization.
 */
class N64Config
{
public:
    // Initialize N64 configuration
    static bool Initialize();

    // Shutdown N64 configuration
    static void Shutdown();

    // Load N64 settings
    static bool LoadSettings();

    // Save N64 settings
    static bool SaveSettings();

    // Get N64 configuration version
    static std::string GetVersion();

private:
    // Prevent instantiation
    N64Config() = delete;
    ~N64Config() = delete;
    N64Config(const N64Config&) = delete;
    N64Config& operator=(const N64Config&) = delete;
};

} // namespace N64
