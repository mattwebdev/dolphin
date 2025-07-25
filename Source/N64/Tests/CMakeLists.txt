# N64 Tests CMakeLists.txt

# Add subdirectories
add_subdirectory(MIPSTests)
add_subdirectory(RSPTests)
add_subdirectory(RDPTests)
add_subdirectory(AudioTests)
add_subdirectory(InputTests)
add_subdirectory(IntegrationTests)

# TODO: Add N64 tests here
# if(ENABLE_TESTS)
#     add_library(dolphin-n64-tests STATIC
#         # Test files will be added here
#     )
#
#     target_include_directories(dolphin-n64-tests PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}
#         ${CMAKE_SOURCE_DIR}/Source/Core
#         ${CMAKE_SOURCE_DIR}/Source/Common
#     )
#
#     target_link_libraries(dolphin-n64-tests
#         dolphin-core
#         dolphin-common
#         dolphin-n64
#         gtest
#         gtest_main
#     )
#
#     target_compile_features(dolphin-n64-tests PRIVATE cxx_std_20)
# endif()