# N64 MIPS Tests CMakeLists.txt

# Add memory manager test
if(ENABLE_TESTS)
    add_executable(dolphin-n64-memory-test
        N64MemoryManagerTest.cpp
    )

    target_include_directories(dolphin-n64-memory-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Source/N64/Core
        ${CMAKE_SOURCE_DIR}/Source/Core
        ${CMAKE_SOURCE_DIR}/Source/Common
    )

    target_link_libraries(dolphin-n64-memory-test
        dolphin-core
        dolphin-common
        dolphin-n64
    )

    target_compile_features(dolphin-n64-memory-test PRIVATE cxx_std_20)
endif()

# TODO: Add MIPS CPU tests here
# if(ENABLE_TESTS)
#     add_executable(dolphin-n64-mips-tests
#         MIPSInstructionTests.cpp
#         MIPSJitTests.cpp
#     )
#
#     target_include_directories(dolphin-n64-mips-tests PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}
#         ${CMAKE_SOURCE_DIR}/Source/Core
#         ${CMAKE_SOURCE_DIR}/Source/Common
#     )
#
#     target_link_libraries(dolphin-n64-mips-tests
#         dolphin-core
#         dolphin-common
#         dolphin-n64
#         gtest
#         gtest_main
#     )
#
#     target_compile_features(dolphin-n64-mips-tests PRIVATE cxx_std_20)
# endif()