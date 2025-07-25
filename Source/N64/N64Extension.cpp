// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "N64Extension.h"

#include <iostream>
#include <sstream>

#include "Common/CommonTypes.h"
#include "Common/Logging/Log.h"
#include "Common/StringUtil.h"

#include "N64/Core/System/N64System.h"
#include "N64/Config/N64Config.h"
#include "N64/VideoBackends/N64VideoBackend.h"

namespace N64
{

// Static member initialization
bool N64Extension::s_initialized = false;
bool N64Extension::s_registered = false;

bool N64Extension::Initialize()
{
    if (s_initialized)
    {
        WARN_LOG(N64, "N64 Extension already initialized");
        return true;
    }

    INFO_LOG(N64, "Initializing N64 Extension v{}", GetVersion());

    try
    {
        // Initialize N64 configuration
        if (!N64Config::Initialize())
        {
            ERROR_LOG(N64, "Failed to initialize N64 configuration");
            return false;
        }

        // Initialize N64 system components
        if (!N64System::Initialize())
        {
            ERROR_LOG(N64, "Failed to initialize N64 system");
            return false;
        }

        // Initialize N64 video backends
        if (!N64VideoBackend::Initialize())
        {
            ERROR_LOG(N64, "Failed to initialize N64 video backends");
            return false;
        }

        s_initialized = true;
        INFO_LOG(N64, "N64 Extension initialized successfully");
        return true;
    }
    catch (const std::exception& e)
    {
        ERROR_LOG(N64, "Exception during N64 Extension initialization: {}", e.what());
        return false;
    }
}

bool N64Extension::IsAvailable()
{
#ifdef ENABLE_N64
    return true;
#else
    return false;
#endif
}

std::unique_ptr<Core::System> N64Extension::CreateN64System()
{
    if (!s_initialized)
    {
        ERROR_LOG(N64, "N64 Extension not initialized");
        return nullptr;
    }

    try
    {
        auto system = std::make_unique<N64System>();
        if (!system->Initialize())
        {
            ERROR_LOG(N64, "Failed to initialize N64 system instance");
            return nullptr;
        }

        INFO_LOG(N64, "Created N64 system instance");
        return system;
    }
    catch (const std::exception& e)
    {
        ERROR_LOG(N64, "Exception creating N64 system: {}", e.what());
        return nullptr;
    }
}

void N64Extension::RegisterWithDolphin()
{
    if (s_registered)
    {
        WARN_LOG(N64, "N64 Extension already registered with Dolphin");
        return;
    }

    if (!s_initialized)
    {
        ERROR_LOG(N64, "Cannot register N64 Extension - not initialized");
        return;
    }

    try
    {
        // Register N64 video backends with main Dolphin
        N64VideoBackend::RegisterWithDolphin();

        // Register N64 audio interfaces
        // TODO: Implement audio registration

        // Register N64 input systems
        // TODO: Implement input registration

        // Register N64 disc I/O systems
        // TODO: Implement disc I/O registration

        s_registered = true;
        INFO_LOG(N64, "N64 Extension registered with Dolphin");
    }
    catch (const std::exception& e)
    {
        ERROR_LOG(N64, "Exception registering N64 Extension: {}", e.what());
    }
}

void N64Extension::Shutdown()
{
    if (!s_initialized)
    {
        WARN_LOG(N64, "N64 Extension not initialized");
        return;
    }

    INFO_LOG(N64, "Shutting down N64 Extension");

    try
    {
        // Unregister from main Dolphin
        if (s_registered)
        {
            N64VideoBackend::UnregisterFromDolphin();
            // TODO: Unregister other components
            s_registered = false;
        }

        // Shutdown N64 system components
        N64System::Shutdown();

        // Shutdown N64 video backends
        N64VideoBackend::Shutdown();

        // Shutdown N64 configuration
        N64Config::Shutdown();

        s_initialized = false;
        INFO_LOG(N64, "N64 Extension shutdown complete");
    }
    catch (const std::exception& e)
    {
        ERROR_LOG(N64, "Exception during N64 Extension shutdown: {}", e.what());
    }
}

std::string N64Extension::GetVersion()
{
    return N64_EXTENSION_VERSION;
}

std::string N64Extension::GetBuildInfo()
{
    std::ostringstream oss;
    oss << "N64 Extension v" << GetVersion();
    oss << " (Build: " << N64_EXTENSION_BUILD_DATE << ")";
    return oss.str();
}

} // namespace N64
