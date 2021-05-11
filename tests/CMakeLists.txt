enable_testing()
include(GoogleTest)

set(BINARY ${CMAKE_PROJECT_NAME}_tst)
add_executable(${BINARY} main.cpp ../src/StatToolImpl.cpp ../src/StatToolImpl.hpp ../src/StatTool.cpp ../src/StatTool.hpp StatToolImplTests.cpp StatToolTests.cpp)
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} gtest gtest_main)
gtest_discover_tests(${BINARY})