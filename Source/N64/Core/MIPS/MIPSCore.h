// Copyright 2024 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>

#include "Common/CommonTypes.h"

namespace N64
{

// Forward declarations
class MIPSState;
class MIPSInterpreter;
class MIPSCachedInterpreter;
class MIPSJitInterface;

/**
 * MIPS R4300i CPU Core
 *
 * This class implements the Nintendo 64's MIPS R4300i processor.
 * It provides the main CPU emulation interface and manages different
 * execution modes (interpreter, cached interpreter, JIT).
 */
class MIPSCore
{
public:
    // CPU execution modes
    enum class ExecutionMode
    {
        Interpreter,           // Pure interpreter
        CachedInterpreter,     // Cached interpreter
        JIT,                   // Just-In-Time compilation
        Count
    };

    // CPU state
    enum class State
    {
        Stopped,
        Running,
        Paused,
        Stepping
    };

    MIPSCore();
    ~MIPSCore();

    // Core initialization and shutdown
    bool Initialize();
    void Shutdown();

    // CPU execution control
    void Run();
    void Pause();
    void Stop();
    void Step();

    // State management
    State GetState() const { return m_state; }
    void SetState(State state) { m_state = state; }

    // Execution mode management
    ExecutionMode GetExecutionMode() const { return m_execution_mode; }
    void SetExecutionMode(ExecutionMode mode);
    bool IsJITEnabled() const { return m_execution_mode == ExecutionMode::JIT; }

    // CPU state access
    MIPSState* GetState() { return m_state.get(); }
    const MIPSState* GetState() const { return m_state.get(); }

    // Memory access
    u32 ReadMemory32(u32 address);
    void WriteMemory32(u32 address, u32 value);
    u16 ReadMemory16(u32 address);
    void WriteMemory16(u32 address, u16 value);
    u8 ReadMemory8(u32 address);
    void WriteMemory8(u32 address, u8 value);

    // CPU statistics
    u64 GetCycles() const { return m_cycles; }
    u64 GetInstructions() const { return m_instructions; }
    void ResetStatistics();

    // Debugging
    void SetBreakpoint(u32 address);
    void ClearBreakpoint(u32 address);
    void ClearAllBreakpoints();
    bool HasBreakpoint(u32 address) const;

    // Exception handling
    void RaiseException(u32 exception_code, u32 coprocessor = 0);
    void HandleException(u32 exception_code, u32 coprocessor = 0);

    // Coprocessor 0 (System Control)
    u32 ReadCP0(u32 reg) const;
    void WriteCP0(u32 reg, u32 value);

    // Coprocessor 1 (FPU)
    u32 ReadCP1(u32 reg) const;
    void WriteCP1(u32 reg, u32 value);

    // Performance monitoring
    void StartPerformanceCounter();
    void StopPerformanceCounter();
    double GetPerformanceCounter() const;

private:
    // CPU state
    std::unique_ptr<MIPSState> m_state;
    State m_state = State::Stopped;
    ExecutionMode m_execution_mode = ExecutionMode::Interpreter;

    // Execution engines
    std::unique_ptr<MIPSInterpreter> m_interpreter;
    std::unique_ptr<MIPSCachedInterpreter> m_cached_interpreter;
    std::unique_ptr<MIPSJitInterface> m_jit_interface;

    // Statistics
    u64 m_cycles = 0;
    u64 m_instructions = 0;
    u64 m_performance_start = 0;
    u64 m_performance_end = 0;

    // Breakpoints
    std::array<bool, 0x1000000> m_breakpoints{}; // 16MB address space

    // Internal methods
    void InitializeExecutionEngines();
    void ShutdownExecutionEngines();
    void ExecuteInstruction();
    void HandleBreakpoint(u32 address);
    void UpdateStatistics();
};

} // namespace N64
