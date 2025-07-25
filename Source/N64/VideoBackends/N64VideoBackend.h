// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <string>

namespace N64
{

/**
 * N64 Video Backend Management
 *
 * This class handles N64-specific video backend initialization and registration
 * with the main Dolphin video system.
 */
class N64VideoBackend
{
public:
    // Initialize N64 video backends
    static bool Initialize();

    // Shutdown N64 video backends
    static void Shutdown();

    // Register N64 video backends with main Dolphin
    static void RegisterWithDolphin();

    // Unregister N64 video backends from main Dolphin
    static void UnregisterFromDolphin();

    // Get N64 video backend version
    static std::string GetVersion();

private:
    // Prevent instantiation
    N64VideoBackend() = delete;
    ~N64VideoBackend() = delete;
    N64VideoBackend(const N64VideoBackend&) = delete;
    N64VideoBackend& operator=(const N64VideoBackend&) = delete;
};

} // namespace N64
