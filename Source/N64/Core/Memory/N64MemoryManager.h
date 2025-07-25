// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace N64
{

/**
 * N64MemoryManager
 *
 * Manages the Nintendo 64's memory layout including RDRAM, SRAM,
 * and various memory-mapped I/O regions.
 */
class N64MemoryManager
{
public:
    // Memory regions
    static constexpr uint32_t RDRAM_SIZE = 8 * 1024 * 1024;  // 8MB RDRAM
    static constexpr uint32_t SRAM_SIZE = 32 * 1024;          // 32KB SRAM
    static constexpr uint32_t ROM_SIZE = 64 * 1024 * 1024;    // 64MB ROM space

    // Memory addresses
    static constexpr uint32_t RDRAM_BASE = 0x00000000;
    static constexpr uint32_t SRAM_BASE = 0x04000000;
    static constexpr uint32_t ROM_BASE = 0x10000000;
    static constexpr uint32_t MMIO_BASE = 0x80000000;

    N64MemoryManager();
    ~N64MemoryManager();

    // Initialize memory
    bool Initialize();
    void Shutdown();

    // Memory access
    uint8_t Read8(uint32_t address);
    uint16_t Read16(uint32_t address);
    uint32_t Read32(uint32_t address);
    uint64_t Read64(uint32_t address);

    void Write8(uint32_t address, uint8_t value);
    void Write16(uint32_t address, uint16_t value);
    void Write32(uint32_t address, uint32_t value);
    void Write64(uint32_t address, uint64_t value);

    // Memory mapping
    bool MapMemory(uint32_t virtual_address, uint32_t physical_address, uint32_t size);
    bool UnmapMemory(uint32_t virtual_address);
    uint32_t VirtualToPhysical(uint32_t virtual_address) const;
    uint32_t PhysicalToVirtual(uint32_t physical_address) const;

    // ROM loading
    bool LoadROM(const std::vector<uint8_t>& rom_data);
    bool IsROMLoaded() const { return m_rom_loaded; }

    // Memory statistics
    uint64_t GetReadCount() const { return m_read_count; }
    uint64_t GetWriteCount() const { return m_write_count; }
    void ResetStatistics();

private:
    // Memory regions
    std::array<uint8_t, RDRAM_SIZE> m_rdram{};
    std::array<uint8_t, SRAM_SIZE> m_sram{};
    std::vector<uint8_t> m_rom;

    // Memory state
    bool m_rom_loaded = false;
    uint64_t m_read_count = 0;
    uint64_t m_write_count = 0;

    // Memory mapping
    struct MemoryMapping
    {
        uint32_t virtual_address;
        uint32_t physical_address;
        uint32_t size;
    };
    std::vector<MemoryMapping> m_mappings;

    // Helper methods
    void InitializeDefaultMappings();
    bool IsValidAddress(uint32_t address) const;
    uint32_t GetMemoryRegion(uint32_t address) const;
    void HandleMMIORead(uint32_t address, uint32_t& value);
    void HandleMMIOWrite(uint32_t address, uint32_t value);
};

} // namespace N64
