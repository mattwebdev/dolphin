// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>
#include <string>

// Forward declarations
namespace Core
{
class System;
}

namespace N64
{
class N64System;

/**
 * Main N64 Extension Interface
 *
 * This class provides the primary integration point between the N64 extension
 * and the existing Dolphin emulator. It handles initialization, system creation,
 * and registration with the main Dolphin codebase.
 */
class N64Extension
{
public:
    /**
     * Initialize the N64 extension
     *
     * This function should be called during Dolphin startup to initialize
     * all N64-specific components and register them with the main system.
     *
     * @return true if initialization was successful, false otherwise
     */
    static bool Initialize();

    /**
     * Check if the N64 extension is available
     *
     * This function checks if the N64 extension was compiled and is
     * available for use. This is useful for conditional compilation.
     *
     * @return true if N64 extension is available, false otherwise
     */
    static bool IsAvailable();

    /**
     * Create an N64 system instance
     *
     * Creates a new N64 system instance that can be used to emulate
     * Nintendo 64 games. This system is separate from the GameCube/Wii
     * system and provides N64-specific functionality.
     *
     * @return Unique pointer to the N64 system instance
     */
    static std::unique_ptr<Core::System> CreateN64System();

    /**
     * Register N64 components with main Dolphin
     *
     * This function registers all N64-specific components (video backends,
     * audio interfaces, input systems, etc.) with the main Dolphin system
     * so they can be used alongside existing GameCube/Wii components.
     */
    static void RegisterWithDolphin();

    /**
     * Cleanup N64 extension
     *
     * This function should be called during Dolphin shutdown to properly
     * cleanup all N64-specific resources and unregister components.
     */
    static void Shutdown();

    /**
     * Get N64 extension version
     *
     * @return String containing the N64 extension version
     */
    static std::string GetVersion();

    /**
     * Get N64 extension build information
     *
     * @return String containing build date and other information
     */
    static std::string GetBuildInfo();

private:
    // Prevent instantiation
    N64Extension() = delete;
    ~N64Extension() = delete;
    N64Extension(const N64Extension&) = delete;
    N64Extension& operator=(const N64Extension&) = delete;

    // Internal state
    static bool s_initialized;
    static bool s_registered;
};

} // namespace N64
