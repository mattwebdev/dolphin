# N64 Extension CMakeLists.txt
# This file builds the N64 extension for Dolphin

# Add N64-specific compiler definitions
add_definitions(-DN64_EXTENSION_VERSION="1.0.0")
add_definitions(-DN64_EXTENSION_BUILD_DATE="${CMAKE_BUILD_DATE}")

# Add subdirectories
add_subdirectory(Core)
add_subdirectory(DiscIO)
add_subdirectory(VideoBackends)
add_subdirectory(UI)
add_subdirectory(Tools)
add_subdirectory(Tests)
add_subdirectory(Config)

# Create the main N64 extension library
add_library(dolphin-n64 STATIC
    N64Extension.h
    N64Extension.cpp
)

# Create N64 demo executable
add_executable(dolphin-n64-demo
    N64Demo.cpp
)

# Set include directories
target_include_directories(dolphin-n64 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

target_include_directories(dolphin-n64-demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64
    dolphin-core
    dolphin-common
    dolphin-audio-common
    dolphin-input-common
    dolphin-video-common
    dolphin-disc-io
    dolphin-ui-common
)

target_link_libraries(dolphin-n64-demo
    dolphin-n64
    dolphin-core
    dolphin-common
)

# Set compile options
target_compile_features(dolphin-n64 PRIVATE cxx_std_20)
target_compile_features(dolphin-n64-demo PRIVATE cxx_std_20)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(dolphin-n64 PRIVATE
        _WIN32_WINNT=0x0601
        WIN32_LEAN_AND_MEAN
    )
    target_compile_definitions(dolphin-n64-demo PRIVATE
        _WIN32_WINNT=0x0601
        WIN32_LEAN_AND_MEAN
    )
endif()

# Install the N64 extension library
install(TARGETS dolphin-n64
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(TARGETS dolphin-n64-demo
    RUNTIME DESTINATION bin
)

# Print build information
message(STATUS "N64 Extension: Building version ${N64_EXTENSION_VERSION}")
message(STATUS "N64 Extension: Build date ${CMAKE_BUILD_DATE}")