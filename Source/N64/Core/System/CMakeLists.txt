# N64 System CMakeLists.txt

# Create N64 System library
add_library(dolphin-n64-system STATIC
    N64System.h
    N64System.cpp
)

# Set include directories
target_include_directories(dolphin-n64-system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64-system
    dolphin-core
    dolphin-common
)

# Set compile options
target_compile_features(dolphin-n64-system PRIVATE cxx_std_20)