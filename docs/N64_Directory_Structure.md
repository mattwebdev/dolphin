# N64 Extension Directory Structure

## Overview

This document outlines the directory structure for the N64 extension to Dolphin. The design principle is **complete separation** - the N64 extension will be a standalone module that **does not modify any existing Dolphin files**. This ensures:

- **Zero impact** on existing GameCube/Wii functionality
- **Easy maintenance** and testing
- **Potential for separate distribution** as a module
- **Clean integration** through well-defined interfaces

## Root Directory Structure

```
Dolphin/
├── Source/
│   ├── Core/           # Existing GameCube/Wii core
│   ├── N64/           # NEW: N64 extension (completely separate)
│   └── ...
├── docs/
│   ├── N64_Support_Extension.md
│   └── N64_Directory_Structure.md  # This document
└── ...
```

## N64 Extension Structure

```
Source/N64/
├── CMakeLists.txt                    # N64-specific build configuration
├── N64Extension.h                    # Main extension interface
├── N64Extension.cpp                  # Extension implementation
├── Core/                             # N64 core emulation
│   ├── CMakeLists.txt
│   ├── MIPS/                        # MIPS CPU emulation
│   │   ├── CMakeLists.txt
│   │   ├── MIPSCore.h
│   │   ├── MIPSCore.cpp
│   │   ├── MIPSJitInterface.h
│   │   ├── MIPSJitInterface.cpp
│   │   ├── MIPSInterpreter.h
│   │   ├── MIPSInterpreter.cpp
│   │   ├── MIPSCachedInterpreter.h
│   │   ├── MIPSCachedInterpreter.cpp
│   │   ├── MIPSState.h
│   │   ├── MIPSState.cpp
│   │   ├── MIPSRegisters.h
│   │   ├── MIPSCop0.h
│   │   ├── MIPSCop0.cpp
│   │   └── JitCommon/               # Shared JIT components
│   │       ├── CMakeLists.txt
│   │       ├── JitBase.h
│   │       ├── JitBase.cpp
│   │       └── ...
│   ├── Memory/                      # N64 memory management
│   │   ├── CMakeLists.txt
│   │   ├── N64MemoryManager.h
│   │   ├── N64MemoryManager.cpp
│   │   ├── N64MemoryMap.h
│   │   ├── N64MemoryMap.cpp
│   │   ├── N64DMA.h
│   │   ├── N64DMA.cpp
│   │   ├── N64RDRAM.h
│   │   ├── N64RDRAM.cpp
│   │   ├── N64SRAM.h
│   │   ├── N64SRAM.cpp
│   │   └── MMIO/                    # Memory-mapped I/O
│   │       ├── CMakeLists.txt
│   │       ├── N64MMIO.h
│   │       ├── N64MMIO.cpp
│   │       └── ...
│   ├── Graphics/                    # N64 graphics system
│   │   ├── CMakeLists.txt
│   │   ├── RCP/                     # Reality Coprocessor
│   │   │   ├── CMakeLists.txt
│   │   │   ├── RealityCoprocessor.h
│   │   │   ├── RealityCoprocessor.cpp
│   │   │   ├── RSP/                 # Reality Signal Processor
│   │   │   │   ├── CMakeLists.txt
│   │   │   │   ├── RSP.h
│   │   │   │   ├── RSP.cpp
│   │   │   │   ├── RSPState.h
│   │   │   │   ├── RSPState.cpp
│   │   │   │   ├── Microcode/       # Microcode implementations
│   │   │   │   │   ├── CMakeLists.txt
│   │   │   │   │   ├── F3DEX.h
│   │   │   │   │   ├── F3DEX.cpp
│   │   │   │   │   ├── F3DEX2.h
│   │   │   │   │   ├── F3DEX2.cpp
│   │   │   │   │   ├── S2DEX.h
│   │   │   │   │   ├── S2DEX.cpp
│   │   │   │   │   └── ...
│   │   │   │   └── DisplayList/     # Display list processing
│   │   │   │       ├── CMakeLists.txt
│   │   │   │       ├── DisplayListProcessor.h
│   │   │   │       ├── DisplayListProcessor.cpp
│   │   │   │       └── ...
│   │   │   └── Audio/               # RSP audio processing
│   │   │       ├── CMakeLists.txt
│   │   │       ├── N64AudioRSP.h
│   │   │       ├── N64AudioRSP.cpp
│   │   │       ├── N64ADPCM.h
│   │   │       ├── N64ADPCM.cpp
│   │   │       └── ...
│   │   └── RDP/                     # Reality Display Processor
│   │       ├── CMakeLists.txt
│   │       ├── RDP.h
│   │       ├── RDP.cpp
│   │       ├── RDPState.h
│   │       ├── RDPState.cpp
│   │       ├── Rasterizer/          # Triangle rasterization
│   │       │   ├── CMakeLists.txt
│   │       │   ├── TriangleRasterizer.h
│   │       │   ├── TriangleRasterizer.cpp
│   │       │   └── ...
│   │       ├── Texture/             # Texture processing
│   │       │   ├── CMakeLists.txt
│   │       │   ├── N64TextureCache.h
│   │       │   ├── N64TextureCache.cpp
│   │       │   ├── N64TextureFormats.h
│   │       │   ├── N64TextureFormats.cpp
│   │       │   └── ...
│   │       └── Framebuffer/         # Frame buffer management
│   │           ├── CMakeLists.txt
│   │           ├── N64Framebuffer.h
│   │           ├── N64Framebuffer.cpp
│   │           └── ...
│   ├── Audio/                       # N64 audio system
│   │   ├── CMakeLists.txt
│   │   ├── N64AudioInterface.h
│   │   ├── N64AudioInterface.cpp
│   │   ├── N64AudioMixer.h
│   │   ├── N64AudioMixer.cpp
│   │   ├── N64AudioBackend.h
│   │   ├── N64AudioBackend.cpp
│   │   └── ...
│   ├── Input/                       # N64 input system
│   │   ├── CMakeLists.txt
│   │   ├── N64Controller.h
│   │   ├── N64Controller.cpp
│   │   ├── N64ControllerState.h
│   │   ├── N64ControllerState.cpp
│   │   ├── N64InputConfig.h
│   │   ├── N64InputConfig.cpp
│   │   ├── N64RumblePak.h
│   │   ├── N64RumblePak.cpp
│   │   └── ...
│   └── System/                      # N64 system management
│       ├── CMakeLists.txt
│       ├── N64System.h
│       ├── N64System.cpp
│       ├── N64Boot.h
│       ├── N64Boot.cpp
│       ├── N64State.h
│       ├── N64State.cpp
│       └── ...
├── DiscIO/                          # N64 ROM support
│   ├── CMakeLists.txt
│   ├── N64Volume.h
│   ├── N64Volume.cpp
│   ├── N64Blob.h
│   ├── N64Blob.cpp
│   ├── N64Formats.h
│   ├── N64Formats.cpp
│   ├── N64SaveTypes.h
│   ├── N64SaveTypes.cpp
│   ├── N64SRAM.h
│   ├── N64SRAM.cpp
│   ├── N64EEPROM.h
│   ├── N64EEPROM.cpp
│   ├── N64FlashRAM.h
│   ├── N64FlashRAM.cpp
│   └── ...
├── VideoBackends/                   # N64 video backends
│   ├── CMakeLists.txt
│   ├── N64VideoBackend.h
│   ├── N64VideoBackend.cpp
│   ├── N64VideoBackendBase.h
│   ├── N64VideoBackendBase.cpp
│   ├── OGL/                         # OpenGL backend for N64
│   │   ├── CMakeLists.txt
│   │   ├── N64OGLVideoBackend.h
│   │   ├── N64OGLVideoBackend.cpp
│   │   ├── N64OGLTextureCache.h
│   │   ├── N64OGLTextureCache.cpp
│   │   └── ...
│   ├── Vulkan/                      # Vulkan backend for N64
│   │   ├── CMakeLists.txt
│   │   ├── N64VulkanVideoBackend.h
│   │   ├── N64VulkanVideoBackend.cpp
│   │   └── ...
│   ├── Software/                    # Software renderer for N64
│   │   ├── CMakeLists.txt
│   │   ├── N64SoftwareVideoBackend.h
│   │   ├── N64SoftwareVideoBackend.cpp
│   │   └── ...
│   └── Null/                        # Null renderer for N64
│       ├── CMakeLists.txt
│       ├── N64NullVideoBackend.h
│       ├── N64NullVideoBackend.cpp
│       └── ...
├── UI/                              # N64 UI extensions
│   ├── CMakeLists.txt
│   ├── N64UICommon.h
│   ├── N64UICommon.cpp
│   ├── Qt/                          # Qt UI extensions
│   │   ├── CMakeLists.txt
│   │   ├── N64QtMainWindow.h
│   │   ├── N64QtMainWindow.cpp
│   │   ├── N64QtSettings.h
│   │   ├── N64QtSettings.cpp
│   │   ├── N64QtControllerConfig.h
│   │   ├── N64QtControllerConfig.cpp
│   │   ├── N64QtGameList.h
│   │   ├── N64QtGameList.cpp
│   │   ├── N64QtDebugger.h
│   │   ├── N64QtDebugger.cpp
│   │   └── ...
│   └── NoGUI/                       # NoGUI extensions
│       ├── CMakeLists.txt
│       ├── N64NoGUIMain.h
│       ├── N64NoGUIMain.cpp
│       └── ...
├── Tools/                           # N64-specific tools
│   ├── CMakeLists.txt
│   ├── N64Tool.h
│   ├── N64Tool.cpp
│   ├── N64ROMInfo.h
│   ├── N64ROMInfo.cpp
│   ├── N64ROMConverter.h
│   ├── N64ROMConverter.cpp
│   └── ...
├── Tests/                           # N64 unit tests
│   ├── CMakeLists.txt
│   ├── MIPSTests/                   # MIPS CPU tests
│   │   ├── CMakeLists.txt
│   │   ├── MIPSInstructionTests.cpp
│   │   ├── MIPSJitTests.cpp
│   │   └── ...
│   ├── RSPTests/                    # RSP tests
│   │   ├── CMakeLists.txt
│   │   ├── RSPMicrocodeTests.cpp
│   │   ├── RSPDisplayListTests.cpp
│   │   └── ...
│   ├── RDPTests/                    # RDP tests
│   │   ├── CMakeLists.txt
│   │   ├── RDPRasterizerTests.cpp
│   │   ├── RDPTextureTests.cpp
│   │   └── ...
│   ├── AudioTests/                  # Audio tests
│   │   ├── CMakeLists.txt
│   │   ├── N64ADPCMTests.cpp
│   │   └── ...
│   ├── InputTests/                  # Input tests
│   │   ├── CMakeLists.txt
│   │   ├── N64ControllerTests.cpp
│   │   └── ...
│   └── IntegrationTests/            # Integration tests
│       ├── CMakeLists.txt
│       ├── N64ROMLoadingTests.cpp
│       ├── N64SaveStateTests.cpp
│       └── ...
└── Config/                          # N64 configuration
    ├── CMakeLists.txt
    ├── N64Config.h
    ├── N64Config.cpp
    ├── N64Settings.h
    ├── N64Settings.cpp
    └── ...
```

## Integration Points

### 1. **Build System Integration**

```cmake
# Source/CMakeLists.txt - Add N64 option
option(ENABLE_N64 "Enable Nintendo 64 support" OFF)

# Add N64 subdirectory if enabled
if(ENABLE_N64)
  add_subdirectory(N64)
endif()
```

```cmake
# Source/N64/CMakeLists.txt - Main N64 build file
add_subdirectory(Core)
add_subdirectory(DiscIO)
add_subdirectory(VideoBackends)
add_subdirectory(UI)
add_subdirectory(Tools)
add_subdirectory(Tests)
add_subdirectory(Config)

# Create N64 library
add_library(dolphin-n64 STATIC
    N64Extension.h
    N64Extension.cpp
    # ... other source files
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64
    dolphin-core
    dolphin-common
    # ... other dependencies
)
```

### 2. **Extension Interface**

```cpp
// Source/N64/N64Extension.h
#pragma once

#include "Core/System.h"

namespace N64
{
class N64Extension
{
public:
    // Initialize N64 extension
    static bool Initialize();

    // Check if N64 extension is available
    static bool IsAvailable();

    // Create N64 system instance
    static std::unique_ptr<Core::System> CreateN64System();

    // Register N64 components with main Dolphin
    static void RegisterWithDolphin();

    // Cleanup N64 extension
    static void Shutdown();
};
}
```

### 3. **Conditional Compilation**

```cpp
// Source/Core/Core/Core.h - Add N64 support
enum class ConsoleType : u32
{
    // Existing types...
    GameCube,
    Wii,

    // New N64 types (only if ENABLE_N64)
#ifdef ENABLE_N64
    N64,
    N64DD,
#endif
};
```

```cpp
// Source/Core/Core/System.h - Add N64 system support
class System
{
public:
    // Existing methods...

#ifdef ENABLE_N64
    // N64-specific methods
    bool IsN64() const;
    N64::N64System& GetN64System() const;
#endif
};
```

### 4. **UI Integration**

```cpp
// Source/Core/DolphinQt/MainWindow.h - Add N64 support
class MainWindow : public QMainWindow
{
public:
    // Existing methods...

#ifdef ENABLE_N64
    // N64-specific UI methods
    void CreateN64Components();
    void ShowN64Settings();
    void ShowN64ControllerConfig();
#endif
};
```

## Key Design Principles

### 1. **Complete Separation**
- **No modifications** to existing Dolphin files
- **Conditional compilation** using `#ifdef ENABLE_N64`
- **Extension interface** for clean integration
- **Separate build targets** for N64 components

### 2. **Modular Architecture**
- **Self-contained** N64 implementation
- **Well-defined interfaces** with main Dolphin
- **Independent testing** of N64 components
- **Optional compilation** (can be disabled)

### 3. **Reuse Existing Infrastructure**
- **Extend existing classes** rather than replace
- **Leverage existing build system**
- **Use existing UI framework**
- **Reuse common utilities**

### 4. **Clean Integration**
- **Extension registration** at startup
- **Conditional feature detection**
- **Graceful fallback** when N64 is disabled
- **Consistent API** with existing Dolphin

## Build Configuration

### 1. **CMake Options**
```cmake
# Main CMakeLists.txt additions
option(ENABLE_N64 "Enable Nintendo 64 support" OFF)
option(ENABLE_N64_TESTS "Enable N64 unit tests" OFF)
option(ENABLE_N64_TOOLS "Enable N64 tools" OFF)
```

### 2. **Compiler Definitions**
```cmake
if(ENABLE_N64)
    add_definitions(-DENABLE_N64)
    add_definitions(-DN64_EXTENSION_VERSION="1.0.0")
endif()
```

### 3. **Dependencies**
```cmake
# N64-specific dependencies
if(ENABLE_N64)
    find_package(OpenGL REQUIRED)
    find_package(Vulkan QUIET)
    # ... other N64-specific dependencies
endif()
```

## Testing Strategy

### 1. **Unit Tests**
- **Independent test suite** for N64 components
- **Mock interfaces** for Dolphin dependencies
- **Comprehensive coverage** of N64-specific code
- **Performance benchmarks** for N64 emulation

### 2. **Integration Tests**
- **ROM loading** and validation
- **Save state** compatibility
- **Controller input** testing
- **Audio/video** synchronization

### 3. **Compatibility Tests**
- **Popular N64 games** testing
- **Different ROM formats** support
- **Region compatibility** verification
- **Save data** handling validation

## Distribution Strategy

### 1. **Optional Module**
- **Can be disabled** without affecting Dolphin
- **Separate compilation** and linking
- **Independent versioning** and releases
- **Optional dependency** for users

### 2. **Clean Integration**
- **Seamless UI** when enabled
- **Consistent user experience**
- **Shared configuration** system
- **Unified debugging** tools

### 3. **Maintenance Benefits**
- **Isolated development** and testing
- **Independent bug fixes** and updates
- **Separate performance** optimization
- **Modular documentation**

## Conclusion

This directory structure provides a **clean, modular approach** to adding N64 support to Dolphin while maintaining **complete separation** from existing code. The design ensures:

- **Zero impact** on existing GameCube/Wii functionality
- **Easy maintenance** and testing of N64 components
- **Flexible distribution** as an optional module
- **Clean integration** through well-defined interfaces
- **Future extensibility** for other console support

The structure leverages Dolphin's existing infrastructure while keeping N64-specific code completely isolated, making it an ideal foundation for the N64 extension project.