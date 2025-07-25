// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "N64MemoryManager.h"
#include <cstring>
#include <iostream>

namespace N64
{

N64MemoryManager::N64MemoryManager() = default;
N64MemoryManager::~N64MemoryManager() = default;

bool N64MemoryManager::Initialize()
{
    m_rdram.fill(0);
    m_sram.fill(0);
    m_rom.clear();
    m_rom_loaded = false;
    m_read_count = 0;
    m_write_count = 0;
    m_mappings.clear();

    // Initialize default memory mappings for N64
    InitializeDefaultMappings();

    std::cout << "N64 Memory Manager initialized" << std::endl;
    return true;
}

void N64MemoryManager::Shutdown()
{
    m_rom.clear();
    m_rom_loaded = false;
    m_mappings.clear();
    std::cout << "N64 Memory Manager shutdown" << std::endl;
}

void N64MemoryManager::InitializeDefaultMappings()
{
    // N64 uses a unified memory space with different regions
    // Map the standard N64 memory layout

    // RDRAM is mapped at multiple locations for different access patterns
    MapMemory(0x00000000, 0x00000000, RDRAM_SIZE);  // KUSEG (user segment)
    MapMemory(0x80000000, 0x00000000, RDRAM_SIZE);  // KSEG0 (kernel segment 0)
    MapMemory(0xA0000000, 0x00000000, RDRAM_SIZE);  // KSEG1 (kernel segment 1)

    // SRAM mapping
    MapMemory(0x04000000, 0x04000000, SRAM_SIZE);

    // ROM mapping (when loaded)
    if (m_rom_loaded)
    {
        MapMemory(0x10000000, 0x10000000, static_cast<uint32_t>(m_rom.size()));
    }
}

uint8_t N64MemoryManager::Read8(uint32_t address)
{
    m_read_count++;

    // Handle MMIO reads first
    if (address >= MMIO_BASE)
    {
        uint32_t value;
        HandleMMIORead(address, value);
        return static_cast<uint8_t>(value & 0xFF);
    }

    // Convert virtual address to physical
    uint32_t physical_address = VirtualToPhysical(address);

    // RDRAM
    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE)
        return m_rdram[physical_address - RDRAM_BASE];

    // SRAM
    if (physical_address >= SRAM_BASE && physical_address < SRAM_BASE + SRAM_SIZE)
        return m_sram[physical_address - SRAM_BASE];

    // ROM
    if (physical_address >= ROM_BASE && physical_address < ROM_BASE + m_rom.size())
        return m_rom[physical_address - ROM_BASE];

    // Unmapped memory - return 0xFF (typical for N64)
    std::cout << "Read8 from unmapped address: 0x" << std::hex << address << std::endl;
    return 0xFF;
}

uint16_t N64MemoryManager::Read16(uint32_t address)
{
    // Handle unaligned reads (N64 allows this)
    if (address & 1)
    {
        uint8_t low = Read8(address);
        uint8_t high = Read8(address + 1);
        return (static_cast<uint16_t>(high) << 8) | low;
    }

    // Aligned read - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 1)
    {
        uint16_t* ptr = reinterpret_cast<uint16_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        uint16_t value = *ptr;
        return ((value & 0xFF) << 8) | ((value >> 8) & 0xFF);
    }

    // Fallback to byte reads
    return (static_cast<uint16_t>(Read8(address)) << 8) | Read8(address + 1);
}

uint32_t N64MemoryManager::Read32(uint32_t address)
{
    // Handle unaligned reads
    if (address & 3)
    {
        uint16_t low = Read16(address);
        uint16_t high = Read16(address + 2);
        return (static_cast<uint32_t>(high) << 16) | low;
    }

    // Aligned read - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 3)
    {
        uint32_t* ptr = reinterpret_cast<uint32_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        uint32_t value = *ptr;
        return ((value & 0xFF) << 24) | (((value >> 8) & 0xFF) << 16) |
               (((value >> 16) & 0xFF) << 8) | ((value >> 24) & 0xFF);
    }

    // Fallback to byte reads
    return (static_cast<uint32_t>(Read8(address)) << 24) |
           (static_cast<uint32_t>(Read8(address + 1)) << 16) |
           (static_cast<uint32_t>(Read8(address + 2)) << 8) |
           Read8(address + 3);
}

uint64_t N64MemoryManager::Read64(uint32_t address)
{
    // Handle unaligned reads
    if (address & 7)
    {
        uint32_t low = Read32(address);
        uint32_t high = Read32(address + 4);
        return (static_cast<uint64_t>(high) << 32) | low;
    }

    // Aligned read - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 7)
    {
        uint64_t* ptr = reinterpret_cast<uint64_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        uint64_t value = *ptr;
        return ((value & 0xFF) << 56) | (((value >> 8) & 0xFF) << 48) |
               (((value >> 16) & 0xFF) << 40) | (((value >> 24) & 0xFF) << 32) |
               (((value >> 32) & 0xFF) << 24) | (((value >> 40) & 0xFF) << 16) |
               (((value >> 48) & 0xFF) << 8) | ((value >> 56) & 0xFF);
    }

    // Fallback to 32-bit reads
    return (static_cast<uint64_t>(Read32(address)) << 32) | Read32(address + 4);
}

void N64MemoryManager::Write8(uint32_t address, uint8_t value)
{
    m_write_count++;

    // Handle MMIO writes first
    if (address >= MMIO_BASE)
    {
        HandleMMIOWrite(address, value);
        return;
    }

    // Convert virtual address to physical
    uint32_t physical_address = VirtualToPhysical(address);

    // RDRAM
    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE)
    {
        m_rdram[physical_address - RDRAM_BASE] = value;
        return;
    }

    // SRAM
    if (physical_address >= SRAM_BASE && physical_address < SRAM_BASE + SRAM_SIZE)
    {
        m_sram[physical_address - SRAM_BASE] = value;
        return;
    }

    // ROM is read-only
    if (physical_address >= ROM_BASE && physical_address < ROM_BASE + m_rom.size())
    {
        std::cout << "Write8 to ROM address: 0x" << std::hex << address << " = 0x" << std::hex << static_cast<int>(value) << std::endl;
        return;
    }

    // Unmapped memory
    std::cout << "Write8 to unmapped address: 0x" << std::hex << address << " = 0x" << std::hex << static_cast<int>(value) << std::endl;
}

void N64MemoryManager::Write16(uint32_t address, uint16_t value)
{
    // Handle unaligned writes
    if (address & 1)
    {
        Write8(address, static_cast<uint8_t>(value & 0xFF));
        Write8(address + 1, static_cast<uint8_t>(value >> 8));
        return;
    }

    // Aligned write - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 1)
    {
        uint16_t* ptr = reinterpret_cast<uint16_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        *ptr = ((value & 0xFF) << 8) | ((value >> 8) & 0xFF);
        return;
    }

    // Fallback to byte writes
    Write8(address, static_cast<uint8_t>(value >> 8));
    Write8(address + 1, static_cast<uint8_t>(value & 0xFF));
}

void N64MemoryManager::Write32(uint32_t address, uint32_t value)
{
    // Handle unaligned writes
    if (address & 3)
    {
        Write16(address, static_cast<uint16_t>(value >> 16));
        Write16(address + 2, static_cast<uint16_t>(value & 0xFFFF));
        return;
    }

    // Aligned write - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 3)
    {
        uint32_t* ptr = reinterpret_cast<uint32_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        *ptr = ((value & 0xFF) << 24) | (((value >> 8) & 0xFF) << 16) |
               (((value >> 16) & 0xFF) << 8) | ((value >> 24) & 0xFF);
        return;
    }

    // Fallback to byte writes
    Write8(address, static_cast<uint8_t>((value >> 24) & 0xFF));
    Write8(address + 1, static_cast<uint8_t>((value >> 16) & 0xFF));
    Write8(address + 2, static_cast<uint8_t>((value >> 8) & 0xFF));
    Write8(address + 3, static_cast<uint8_t>(value & 0xFF));
}

void N64MemoryManager::Write64(uint32_t address, uint64_t value)
{
    // Handle unaligned writes
    if (address & 7)
    {
        Write32(address, static_cast<uint32_t>(value >> 32));
        Write32(address + 4, static_cast<uint32_t>(value & 0xFFFFFFFF));
        return;
    }

    // Aligned write - more efficient
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE - 7)
    {
        uint64_t* ptr = reinterpret_cast<uint64_t*>(&m_rdram[physical_address - RDRAM_BASE]);
        // N64 is big-endian, so we need to swap bytes
        *ptr = ((value & 0xFF) << 56) | (((value >> 8) & 0xFF) << 48) |
               (((value >> 16) & 0xFF) << 40) | (((value >> 24) & 0xFF) << 32) |
               (((value >> 32) & 0xFF) << 24) | (((value >> 40) & 0xFF) << 16) |
               (((value >> 48) & 0xFF) << 8) | ((value >> 56) & 0xFF);
        return;
    }

    // Fallback to 32-bit writes
    Write32(address, static_cast<uint32_t>(value >> 32));
    Write32(address + 4, static_cast<uint32_t>(value & 0xFFFFFFFF));
}

bool N64MemoryManager::MapMemory(uint32_t virtual_address, uint32_t physical_address, uint32_t size)
{
    // Check for overlapping mappings
    for (const auto& mapping : m_mappings)
    {
        if ((virtual_address < mapping.virtual_address + mapping.size) &&
            (virtual_address + size > mapping.virtual_address))
        {
            std::cout << "Memory mapping conflict: 0x" << std::hex << virtual_address
                      << "-0x" << std::hex << (virtual_address + size) << " overlaps with existing mapping" << std::endl;
            return false;
        }
    }

    m_mappings.push_back({virtual_address, physical_address, size});
    std::cout << "Mapped memory: 0x" << std::hex << virtual_address << " -> 0x" << std::hex << physical_address
              << " (size: 0x" << std::hex << size << ")" << std::endl;
    return true;
}

bool N64MemoryManager::UnmapMemory(uint32_t virtual_address)
{
    for (auto it = m_mappings.begin(); it != m_mappings.end(); ++it)
    {
        if (it->virtual_address == virtual_address)
        {
            std::cout << "Unmapped memory: 0x" << std::hex << virtual_address << std::endl;
            m_mappings.erase(it);
            return true;
        }
    }
    return false;
}

uint32_t N64MemoryManager::VirtualToPhysical(uint32_t virtual_address) const
{
    for (const auto& mapping : m_mappings)
    {
        if (virtual_address >= mapping.virtual_address &&
            virtual_address < mapping.virtual_address + mapping.size)
        {
            return mapping.physical_address + (virtual_address - mapping.virtual_address);
        }
    }
    return virtual_address; // Identity mapping if no specific mapping found
}

uint32_t N64MemoryManager::PhysicalToVirtual(uint32_t physical_address) const
{
    for (const auto& mapping : m_mappings)
    {
        if (physical_address >= mapping.physical_address &&
            physical_address < mapping.physical_address + mapping.size)
        {
            return mapping.virtual_address + (physical_address - mapping.physical_address);
        }
    }
    return physical_address; // Identity mapping if no specific mapping found
}

bool N64MemoryManager::LoadROM(const std::vector<uint8_t>& rom_data)
{
    if (rom_data.empty())
    {
        std::cout << "Attempted to load empty ROM" << std::endl;
        return false;
    }

    if (rom_data.size() > ROM_SIZE)
    {
        std::cout << "ROM too large: " << rom_data.size() << " bytes (max: " << ROM_SIZE << " bytes)" << std::endl;
        return false;
    }

    m_rom = rom_data;
    m_rom_loaded = true;

    // Update memory mappings to include ROM
    MapMemory(0x10000000, 0x10000000, static_cast<uint32_t>(m_rom.size()));

    std::cout << "Loaded ROM: " << rom_data.size() << " bytes" << std::endl;
    return true;
}

void N64MemoryManager::ResetStatistics()
{
    m_read_count = 0;
    m_write_count = 0;
    std::cout << "Memory statistics reset" << std::endl;
}

bool N64MemoryManager::IsValidAddress(uint32_t address) const
{
    uint32_t physical_address = VirtualToPhysical(address);

    return (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE) ||
           (physical_address >= SRAM_BASE && physical_address < SRAM_BASE + SRAM_SIZE) ||
           (physical_address >= ROM_BASE && physical_address < ROM_BASE + m_rom.size()) ||
           (address >= MMIO_BASE);
}

uint32_t N64MemoryManager::GetMemoryRegion(uint32_t address) const
{
    uint32_t physical_address = VirtualToPhysical(address);

    if (physical_address >= RDRAM_BASE && physical_address < RDRAM_BASE + RDRAM_SIZE)
        return RDRAM_BASE;
    if (physical_address >= SRAM_BASE && physical_address < SRAM_BASE + SRAM_SIZE)
        return SRAM_BASE;
    if (physical_address >= ROM_BASE && physical_address < ROM_BASE + m_rom.size())
        return ROM_BASE;
    if (address >= MMIO_BASE)
        return MMIO_BASE;
    return 0xFFFFFFFF;
}

void N64MemoryManager::HandleMMIORead(uint32_t address, uint32_t& value)
{
    // N64 MMIO addresses are in the 0x80000000+ range
    switch (address & 0xFFFFFFF0) // Align to 16-byte boundary
    {
        case 0x80000000: // RDRAM Interface
            value = 0x00000000; // RDRAM_ID
            break;

        case 0x80000010: // RDRAM Interface
            value = 0x00000000; // RDRAM_MODE
            break;

        case 0x80000020: // RDRAM Interface
            value = 0x00000000; // RDRAM_REF_INTERVAL
            break;

        case 0x80000030: // RDRAM Interface
            value = 0x00000000; // RDRAM_REF_ROW
            break;

        case 0x80000040: // RDRAM Interface
            value = 0x00000000; // RDRAM_RAS_INTERVAL
            break;

        case 0x80000050: // RDRAM Interface
            value = 0x00000000; // RDRAM_MIN_INTERVAL
            break;

        case 0x80000060: // RDRAM Interface
            value = 0x00000000; // RDRAM_ADDR_SELECT
            break;

        case 0x80000070: // RDRAM Interface
            value = 0x00000000; // RDRAM_DEVICE_MANUF
            break;

        default:
            std::cout << "MMIO Read from unknown address: 0x" << std::hex << address << std::endl;
            value = 0xFFFFFFFF;
            break;
    }
}

void N64MemoryManager::HandleMMIOWrite(uint32_t address, uint32_t value)
{
    // N64 MMIO addresses are in the 0x80000000+ range
    switch (address & 0xFFFFFFF0) // Align to 16-byte boundary
    {
        case 0x80000000: // RDRAM Interface
            // RDRAM_ID - read-only
            break;

        case 0x80000010: // RDRAM Interface
            // RDRAM_MODE
            std::cout << "RDRAM_MODE write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000020: // RDRAM Interface
            // RDRAM_REF_INTERVAL
            std::cout << "RDRAM_REF_INTERVAL write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000030: // RDRAM Interface
            // RDRAM_REF_ROW
            std::cout << "RDRAM_REF_ROW write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000040: // RDRAM Interface
            // RDRAM_RAS_INTERVAL
            std::cout << "RDRAM_RAS_INTERVAL write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000050: // RDRAM Interface
            // RDRAM_MIN_INTERVAL
            std::cout << "RDRAM_MIN_INTERVAL write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000060: // RDRAM Interface
            // RDRAM_ADDR_SELECT
            std::cout << "RDRAM_ADDR_SELECT write: 0x" << std::hex << value << std::endl;
            break;

        case 0x80000070: // RDRAM Interface
            // RDRAM_DEVICE_MANUF - read-only
            break;

        default:
            std::cout << "MMIO Write to unknown address: 0x" << std::hex << address << " = 0x" << std::hex << value << std::endl;
            break;
    }
}

} // namespace N64
