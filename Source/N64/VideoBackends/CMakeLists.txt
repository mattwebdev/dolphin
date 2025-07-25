# N64 VideoBackends CMakeLists.txt

# Add subdirectories for different video backends
add_subdirectory(OGL)
add_subdirectory(Vulkan)
add_subdirectory(Software)
add_subdirectory(Null)

# Create N64 VideoBackends library
add_library(dolphin-n64-video STATIC
    N64VideoBackend.h
    N64VideoBackend.cpp
)

# Set include directories
target_include_directories(dolphin-n64-video PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Source/Core
    ${CMAKE_SOURCE_DIR}/Source/Common
    ${CMAKE_SOURCE_DIR}/Source/Core/VideoCommon
)

# Link with existing Dolphin libraries
target_link_libraries(dolphin-n64-video
    dolphin-core
    dolphin-common
    dolphin-video-common
)

# Set compile options
target_compile_features(dolphin-n64-video PRIVATE cxx_std_20)