// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "N64VideoBackend.h"

#include "Common/Logging/Log.h"

namespace N64
{

bool N64VideoBackend::Initialize()
{
    INFO_LOG(N64, "Initializing N64 Video Backends");
    return true;
}

void N64VideoBackend::Shutdown()
{
    INFO_LOG(N64, "Shutting down N64 Video Backends");
}

void N64VideoBackend::RegisterWithDolphin()
{
    INFO_LOG(N64, "Registering N64 Video Backends with Dolphin");
}

void N64VideoBackend::UnregisterFromDolphin()
{
    INFO_LOG(N64, "Unregistering N64 Video Backends from Dolphin");
}

std::string N64VideoBackend::GetVersion()
{
    return "1.0.0";
}

} // namespace N64
