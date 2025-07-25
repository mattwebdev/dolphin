// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "N64System.h"

#include "Common/Logging/Log.h"

namespace N64
{

N64System::N64System()
{
    INFO_LOG(N64, "Creating N64 System instance");
}

N64System::~N64System()
{
    INFO_LOG(N64, "Destroying N64 System instance");
}

bool N64System::Initialize()
{
    if (m_initialized)
    {
        WARN_LOG(N64, "N64 System already initialized");
        return true;
    }

    INFO_LOG(N64, "Initializing N64 System instance");
    m_initialized = true;
    return true;
}

bool N64System::Initialize()
{
    INFO_LOG(N64, "Initializing N64 System components");
    return true;
}

void N64System::Shutdown()
{
    INFO_LOG(N64, "Shutting down N64 System components");
}

} // namespace N64
