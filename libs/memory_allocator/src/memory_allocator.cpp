#include <memory_allocator.hpp>

namespace QuantSys 
{
    template <std::size_t BlockSize, std::size_t BlockCount>
    FixedBlockAllocator<BlockSize, BlockCount>::FixedBlockAllocator()
    {
        memory_pool_ = std::make_unique<std::byte[]>(BlockSize * BlockCount);
        free_list_.set();
    }

    template <std::size_t BlockSize, std::size_t BlockCount>
    FixedBlockAllocator<BlockSize, BlockCount>::~FixedBlockAllocator() = default;
}
