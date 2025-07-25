# N64 MIPS CMakeLists.txt

add_library(dolphin-n64-mips STATIC
    MIPSCore.h
    MIPSCore.cpp
    MIPSState.h
    MIPSState.cpp
    MIPSInterpreter.h
    MIPSInterpreter.cpp
)

target_include_directories(dolphin-n64-mips PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

target_link_libraries(dolphin-n64-mips
    dolphin-core
    dolphin-common
)

target_compile_features(dolphin-n64-mips PRIVATE cxx_std_20)