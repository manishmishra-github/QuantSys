add_library(memory_allocator INTERFACE)

# Include plain "include/" instead of "include/memory_allocator"
target_include_directories(memory_allocator INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(memory_allocator_test
    src/test_memory_allocator.cpp
)
target_link_libraries(memory_allocator_test PRIVATE memory_allocator)
