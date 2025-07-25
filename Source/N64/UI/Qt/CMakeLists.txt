# N64 Qt UI CMakeLists.txt

# TODO: Add N64 Qt UI files here
# add_library(dolphin-n64-ui-qt STATIC
#     N64QtMainWindow.h
#     N64QtMainWindow.cpp
#     N64QtSettings.h
#     N64QtSettings.cpp
#     N64QtControllerConfig.h
#     N64QtControllerConfig.cpp
#     N64QtGameList.h
#     N64QtGameList.cpp
#     N64QtDebugger.h
#     N64QtDebugger.cpp
# )

# Set include directories
# target_include_directories(dolphin-n64-ui-qt PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}/Source/Core
#     ${CMAKE_SOURCE_DIR}/Source/Common
#     ${CMAKE_SOURCE_DIR}/Source/Core/UICommon
#     ${CMAKE_SOURCE_DIR}/Source/Core/DolphinQt
# )

# Link with existing Dolphin libraries
# target_link_libraries(dolphin-n64-ui-qt
#     dolphin-core
#     dolphin-common
#     dolphin-ui-common
#     dolphin-qt
#     Qt6::Core
#     Qt6::Widgets
# )

# Set compile options
# target_compile_features(dolphin-n64-ui-qt PRIVATE cxx_std_20)