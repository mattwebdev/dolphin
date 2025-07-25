# N64 Integration Tests CMakeLists.txt

# TODO: Add Integration tests here
# if(ENABLE_TESTS)
#     add_executable(dolphin-n64-integration-tests
#         N64SystemIntegrationTests.cpp
#         N64GameTests.cpp
#     )
#
#     target_include_directories(dolphin-n64-integration-tests PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}
#         ${CMAKE_SOURCE_DIR}/Source/Core
#         ${CMAKE_SOURCE_DIR}/Source/Common
#     )
#
#     target_link_libraries(dolphin-n64-integration-tests
#         dolphin-core
#         dolphin-common
#         dolphin-n64
#         gtest
#         gtest_main
#     )
#
#     target_compile_features(dolphin-n64-integration-tests PRIVATE cxx_std_20)
# endif()