#include <memory_allocator.hpp>

namespace QuantSys 
{
    template <std::size_t BlockSize, std::size_t BlockCount>
    FixedBlockAllocator<BlockSize, BlockCount>::FixedBlockAllocator()
    {
        memory_pool_ = std::make_unique<std::byte[]>(BlockSize * BlockCount);
        free_list_.set(true);
    }

    template <std::size_t BlockSize, std::size_t BlockCount>
    FixedBlockAllocator<BlockSize, BlockCount>::~FixedBlockAllocator() = default;

    template <std::size_t BlockSize, std::size_t BlockCount>
    void* FixedBlockAllocator<BlockSize, BlockCount>::allocate()
    {
        for(size_t i = 0; i < BlockCount; i++)
        {
            if(free_list_[i] == true)
            {
                free_list_[i] = false;
                return memory_pool_.get() + i * BlockSize;
            }
        }
        return nullptr;
    }

    // Function to deallocate a ptr from the pool.
    // Algo:-
    // given a void * ptr; 
    // type cast it to std::byte * so that we can perform arithmetic ops on it.
    // get the ptr to the base(start) of the mem_pool by using .get of the std::unique_ptr<T> 
    // it is a continous block of memory so you should be able to subtract base_ptr from ptr and get the 
    // number of bytes the block is from the start.
    // check if the ptr belongs to our pool.
    // get the index of the block using bytes/sixe_per_block;
    // free that index;
    template <std::size_t BlockSize, std::size_t BlockCount>
    void FixedBlockAllocator<BlockSize, BlockCount>:: deallocate(void *ptr)
    {
        if (!ptr)
        {
            return;
        }
        std::byte* to_free_ptr = (std::byte*)ptr;

        std::byte* base_ptr = (std::byte*)memory_pool_.get();

        if(to_free_ptr < base_ptr || to_free_ptr >= (base_ptr +BlockSize * BlockCount))
        {
            return;
        }
        size_t offset = to_free_ptr - base_ptr;

        if (offset % BlockSize != 0) 
        {
            std::cerr << "Warning: Misaligned deallocation.\n";
            return;
        }
        size_t index = offset / BlockSize;

        if(free_list_[index])
        {
            std::cerr << "Warning: Double Free detected.\n";
            return;
        }

        free_list_[index] = true;
    }
}
