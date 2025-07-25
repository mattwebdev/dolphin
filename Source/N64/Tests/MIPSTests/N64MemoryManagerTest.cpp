// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <iostream>
#include <memory>
#include <vector>

// Include the memory manager directly
#include "../../Core/Memory/N64MemoryManager.h"

using namespace N64;

int main()
{
    std::cout << "N64 Memory Manager Test" << std::endl;
    std::cout << "=======================" << std::endl;

    auto memory_manager = std::make_unique<N64MemoryManager>();

    // Test 1: Initialize
    std::cout << "Test 1: Initialize..." << std::endl;
    if (!memory_manager->Initialize())
    {
        std::cout << "FAILED: Initialize failed" << std::endl;
        return 1;
    }
    std::cout << "PASSED: Initialize" << std::endl;

    // Test 2: RDRAM read/write
    std::cout << "Test 2: RDRAM read/write..." << std::endl;
    uint32_t test_address = 0x00001000;
    uint8_t test_value = 0x42;

    memory_manager->Write8(test_address, test_value);
    uint8_t read_value = memory_manager->Read8(test_address);

    if (read_value != test_value)
    {
        std::cout << "FAILED: RDRAM read/write (expected 0x" << std::hex << static_cast<int>(test_value)
                  << ", got 0x" << std::hex << static_cast<int>(read_value) << ")" << std::endl;
        return 1;
    }
    std::cout << "PASSED: RDRAM read/write" << std::endl;

    // Test 3: SRAM read/write
    std::cout << "Test 3: SRAM read/write..." << std::endl;
    uint32_t sram_address = 0x04000000;
    uint16_t sram_value = 0x1234;

    memory_manager->Write16(sram_address, sram_value);
    uint16_t sram_read = memory_manager->Read16(sram_address);

    if (sram_read != sram_value)
    {
        std::cout << "FAILED: SRAM read/write (expected 0x" << std::hex << sram_value
                  << ", got 0x" << std::hex << sram_read << ")" << std::endl;
        return 1;
    }
    std::cout << "PASSED: SRAM read/write" << std::endl;

    // Test 4: ROM loading
    std::cout << "Test 4: ROM loading..." << std::endl;
    std::vector<uint8_t> test_rom = {0x80, 0x37, 0x12, 0x40}; // N64 ROM header

    if (!memory_manager->LoadROM(test_rom))
    {
        std::cout << "FAILED: ROM loading failed" << std::endl;
        return 1;
    }

    if (!memory_manager->IsROMLoaded())
    {
        std::cout << "FAILED: ROM not marked as loaded" << std::endl;
        return 1;
    }

    // Test reading from ROM
    uint8_t rom_read = memory_manager->Read8(0x10000000);
    if (rom_read != 0x80)
    {
        std::cout << "FAILED: ROM read (expected 0x80, got 0x" << std::hex << static_cast<int>(rom_read) << ")" << std::endl;
        return 1;
    }
    std::cout << "PASSED: ROM loading" << std::endl;

    // Test 5: Memory mapping
    std::cout << "Test 5: Memory mapping..." << std::endl;
    uint32_t virtual_addr = 0x20000000;
    uint32_t physical_addr = 0x00002000;
    uint32_t size = 1024;

    if (!memory_manager->MapMemory(virtual_addr, physical_addr, size))
    {
        std::cout << "FAILED: Memory mapping failed" << std::endl;
        return 1;
    }

    // Write to virtual address
    memory_manager->Write32(virtual_addr, 0x12345678);

    // Read from physical address
    uint32_t mapped_read = memory_manager->Read32(physical_addr);
    if (mapped_read != 0x12345678)
    {
        std::cout << "FAILED: Memory mapping read (expected 0x12345678, got 0x" << std::hex << mapped_read << ")" << std::endl;
        return 1;
    }
    std::cout << "PASSED: Memory mapping" << std::endl;

    // Test 6: Big-endian
    std::cout << "Test 6: Big-endian..." << std::endl;
    uint32_t be_address = 0x00001000;
    uint32_t be_value = 0x12345678;

    memory_manager->Write32(be_address, be_value);

    // Read as bytes to verify big-endian order
    uint8_t byte0 = memory_manager->Read8(be_address);
    uint8_t byte1 = memory_manager->Read8(be_address + 1);
    uint8_t byte2 = memory_manager->Read8(be_address + 2);
    uint8_t byte3 = memory_manager->Read8(be_address + 3);

    if (byte0 != 0x12 || byte1 != 0x34 || byte2 != 0x56 || byte3 != 0x78)
    {
        std::cout << "FAILED: Big-endian (expected 0x12,0x34,0x56,0x78, got 0x"
                  << std::hex << static_cast<int>(byte0) << ",0x" << std::hex << static_cast<int>(byte1)
                  << ",0x" << std::hex << static_cast<int>(byte2) << ",0x" << std::hex << static_cast<int>(byte3) << ")" << std::endl;
        return 1;
    }
    std::cout << "PASSED: Big-endian" << std::endl;

    // Test 7: Statistics
    std::cout << "Test 7: Statistics..." << std::endl;
    uint64_t initial_reads = memory_manager->GetReadCount();
    uint64_t initial_writes = memory_manager->GetWriteCount();

    memory_manager->Read8(0x00001000);
    memory_manager->Write8(0x00001000, 0x42);

    if (memory_manager->GetReadCount() != initial_reads + 1)
    {
        std::cout << "FAILED: Read count not incremented" << std::endl;
        return 1;
    }

    if (memory_manager->GetWriteCount() != initial_writes + 1)
    {
        std::cout << "FAILED: Write count not incremented" << std::endl;
        return 1;
    }

    memory_manager->ResetStatistics();
    if (memory_manager->GetReadCount() != 0 || memory_manager->GetWriteCount() != 0)
    {
        std::cout << "FAILED: Statistics not reset" << std::endl;
        return 1;
    }
    std::cout << "PASSED: Statistics" << std::endl;

    // Test 8: Invalid address handling
    std::cout << "Test 8: Invalid address handling..." << std::endl;
    uint32_t invalid_address = 0xFFFFFFFF;

    // Should not crash and should return 0xFF for reads
    uint8_t invalid_read = memory_manager->Read8(invalid_address);
    if (invalid_read != 0xFF)
    {
        std::cout << "FAILED: Invalid address read (expected 0xFF, got 0x" << std::hex << static_cast<int>(invalid_read) << ")" << std::endl;
        return 1;
    }

    // Should not crash for writes to invalid addresses
    memory_manager->Write8(invalid_address, 0x42);
    std::cout << "PASSED: Invalid address handling" << std::endl;

    // Cleanup
    memory_manager->Shutdown();

    std::cout << std::endl;
    std::cout << "All tests PASSED!" << std::endl;
    return 0;
}
