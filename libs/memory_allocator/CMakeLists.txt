include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(memory_allocator STATIC src/memory_allocator.cpp)
target_include_directories(memory_allocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
