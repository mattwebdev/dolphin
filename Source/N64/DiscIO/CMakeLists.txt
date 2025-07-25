# N64 DiscIO CMakeLists.txt

# TODO: Add N64 ROM support files here
# add_library(dolphin-n64-disc-io STATIC
#     N64Volume.h
#     N64Volume.cpp
#     N64Blob.h
#     N64Blob.cpp
#     N64Formats.h
#     N64Formats.cpp
#     N64SaveTypes.h
#     N64SaveTypes.cpp
#     N64SRAM.h
#     N64SRAM.cpp
#     N64EEPROM.h
#     N64EEPROM.cpp
#     N64FlashRAM.h
#     N64FlashRAM.cpp
# )

# Set include directories
# target_include_directories(dolphin-n64-disc-io PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}/Source/Core
#     ${CMAKE_SOURCE_DIR}/Source/Common
#     ${CMAKE_SOURCE_DIR}/Source/Core/DiscIO
# )

# Link with existing Dolphin libraries
# target_link_libraries(dolphin-n64-disc-io
#     dolphin-core
#     dolphin-common
#     dolphin-disc-io
# )

# Set compile options
# target_compile_features(dolphin-n64-disc-io PRIVATE cxx_std_20)