set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES hello.cpp hello.hpp main.cpp StatTool.cpp StatTool.hpp StatToolImpl.cpp StatToolImpl.hpp StatVector.hpp)
add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})