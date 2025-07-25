// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <iostream>
#include <memory>
#include <vector>

#include "N64Extension.h"
#include "Core/Memory/N64MemoryManager.h"

int main()
{
    std::cout << "N64 Extension Demo" << std::endl;
    std::cout << "==================" << std::endl;

    // Check if N64 extension is available
    if (!N64::N64Extension::IsAvailable())
    {
        std::cout << "N64 Extension is not available!" << std::endl;
        return 1;
    }

    std::cout << "N64 Extension Version: " << N64::N64Extension::GetVersion() << std::endl;
    std::cout << "N64 Extension Build Info: " << N64::N64Extension::GetBuildInfo() << std::endl;

    // Initialize the N64 extension
    if (!N64::N64Extension::Initialize())
    {
        std::cout << "Failed to initialize N64 Extension!" << std::endl;
        return 1;
    }

    std::cout << "N64 Extension initialized successfully!" << std::endl;

    // Register with main Dolphin
    N64::N64Extension::RegisterWithDolphin();
    std::cout << "N64 Extension registered with Dolphin!" << std::endl;

    // Demonstrate memory manager functionality
    std::cout << std::endl;
    std::cout << "Memory Manager Demo:" << std::endl;
    std::cout << "-------------------" << std::endl;

    auto memory_manager = std::make_unique<N64::N64MemoryManager>();
    if (!memory_manager->Initialize())
    {
        std::cout << "Failed to initialize memory manager!" << std::endl;
        return 1;
    }

    // Test RDRAM access
    std::cout << "Testing RDRAM access..." << std::endl;
    memory_manager->Write32(0x00001000, 0x12345678);
    uint32_t value = memory_manager->Read32(0x00001000);
    std::cout << "RDRAM read/write test: 0x" << std::hex << value << std::endl;

    // Test SRAM access
    std::cout << "Testing SRAM access..." << std::endl;
    memory_manager->Write16(0x04000000, 0xABCD);
    uint16_t sram_value = memory_manager->Read16(0x04000000);
    std::cout << "SRAM read/write test: 0x" << std::hex << sram_value << std::endl;

    // Test ROM loading
    std::cout << "Testing ROM loading..." << std::endl;
    std::vector<uint8_t> test_rom(1024, 0xAA); // 1KB test ROM
    test_rom[0] = 0x80; // N64 ROM header
    test_rom[1] = 0x37;
    test_rom[2] = 0x12;
    test_rom[3] = 0x40;

    if (memory_manager->LoadROM(test_rom))
    {
        std::cout << "ROM loaded successfully!" << std::endl;
        uint8_t rom_header = memory_manager->Read8(0x10000000);
        std::cout << "ROM header byte: 0x" << std::hex << static_cast<int>(rom_header) << std::endl;
    }
    else
    {
        std::cout << "Failed to load ROM!" << std::endl;
    }

    // Test memory mapping
    std::cout << "Testing memory mapping..." << std::endl;
    if (memory_manager->MapMemory(0x20000000, 0x00002000, 1024))
    {
        memory_manager->Write32(0x20000000, 0xDEADBEEF);
        uint32_t mapped_value = memory_manager->Read32(0x00002000);
        std::cout << "Memory mapping test: 0x" << std::hex << mapped_value << std::endl;
    }

    // Show statistics
    std::cout << "Memory access statistics:" << std::endl;
    std::cout << "  Reads: " << memory_manager->GetReadCount() << std::endl;
    std::cout << "  Writes: " << memory_manager->GetWriteCount() << std::endl;

    // Test MMIO
    std::cout << "Testing MMIO access..." << std::endl;
    uint8_t mmio_value = memory_manager->Read8(0x80000000);
    std::cout << "MMIO read: 0x" << std::hex << static_cast<int>(mmio_value) << std::endl;

    memory_manager->Write8(0x80000010, 0x42);
    std::cout << "MMIO write completed" << std::endl;

    // Cleanup
    memory_manager->Shutdown();

    // Shutdown N64 extension
    N64::N64Extension::Shutdown();

    std::cout << std::endl;
    std::cout << "N64 Extension demo completed successfully!" << std::endl;
    return 0;
}
