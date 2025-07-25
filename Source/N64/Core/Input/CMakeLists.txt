# N64 Input CMakeLists.txt

# TODO: Add N64 input system files here
# add_library(dolphin-n64-input STATIC
#     N64Controller.h
#     N64Controller.cpp
#     N64ControllerState.h
#     N64ControllerState.cpp
#     N64InputConfig.h
#     N64InputConfig.cpp
#     N64RumblePak.h
#     N64RumblePak.cpp
# )

# Set include directories
# target_include_directories(dolphin-n64-input PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}/Source/Core
#     ${CMAKE_SOURCE_DIR}/Source/Common
#     ${CMAKE_SOURCE_DIR}/Source/Core/InputCommon
# )

# Link with existing Dolphin libraries
# target_link_libraries(dolphin-n64-input
#     dolphin-core
#     dolphin-common
#     dolphin-input-common
# )

# Set compile options
# target_compile_features(dolphin-n64-input PRIVATE cxx_std_20)