// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "N64Config.h"

#include "Common/Logging/Log.h"

namespace N64
{

bool N64Config::Initialize()
{
    INFO_LOG(N64, "Initializing N64 Configuration");
    return true;
}

void N64Config::Shutdown()
{
    INFO_LOG(N64, "Shutting down N64 Configuration");
}

bool N64Config::LoadSettings()
{
    INFO_LOG(N64, "Loading N64 settings");
    return true;
}

bool N64Config::SaveSettings()
{
    INFO_LOG(N64, "Saving N64 settings");
    return true;
}

std::string N64Config::GetVersion()
{
    return "1.0.0";
}

} // namespace N64
