# N64 Core CMakeLists.txt

# Add subdirectories
add_subdirectory(MIPS)
add_subdirectory(Memory)
add_subdirectory(Graphics)
add_subdirectory(Audio)
add_subdirectory(Input)
add_subdirectory(System)

# Create N64 Core library
add_library(dolphin-n64-core STATIC
    # Core system files will be added here
)

# Set include directories
target_include_directories(dolphin-n64-core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64-core
    dolphin-core
    dolphin-common
)

# Set compile options
target_compile_features(dolphin-n64-core PRIVATE cxx_std_20)