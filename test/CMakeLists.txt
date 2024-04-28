project(cql-test LANGUAGES CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest gtest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} src/tokenizer.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main cql-lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
