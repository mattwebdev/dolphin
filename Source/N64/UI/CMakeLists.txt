# N64 UI CMakeLists.txt

# Add subdirectories
add_subdirectory(Qt)
add_subdirectory(NoGUI)

# TODO: Add N64 UI files here
# add_library(dolphin-n64-ui STATIC
#     N64UICommon.h
#     N64UICommon.cpp
# )

# Set include directories
# target_include_directories(dolphin-n64-ui PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}/Source/Core
#     ${CMAKE_SOURCE_DIR}/Source/Common
#     ${CMAKE_SOURCE_DIR}/Source/Core/UICommon
# )

# Link with existing Dolphin libraries
# target_link_libraries(dolphin-n64-ui
#     dolphin-core
#     dolphin-common
#     dolphin-ui-common
# )

# Set compile options
# target_compile_features(dolphin-n64-ui PRIVATE cxx_std_20)