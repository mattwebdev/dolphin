# N64 Config CMakeLists.txt

# Create N64 Config library
add_library(dolphin-n64-config STATIC
    N64Config.h
    N64Config.cpp
)

# Set include directories
target_include_directories(dolphin-n64-config PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64-config
    dolphin-core
    dolphin-common
)

# Set compile options
target_compile_features(dolphin-n64-config PRIVATE cxx_std_20)