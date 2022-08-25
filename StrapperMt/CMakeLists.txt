cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE INCL include/*.h)
file(GLOB_RECURSE SRCS lib/*.h lib/*.cpp)

# StrapperMt
add_library(StrapperMt STATIC
    ${INCL}
    ${SRCS}
)
target_include_directories(StrapperMt PUBLIC include/)
target_link_libraries(StrapperMt PUBLIC
    Threads::Threads
)
target_compile_options(StrapperMt PRIVATE ${WARNING_FLAGS})
