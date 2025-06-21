#pragma once

#include <iostream>
#include <cstddef>
#include <bitset>
#include <memory>

namespace QuantSys 
{
	//Non Type template, can be used when you want to make classes/functions with different compile time values
	//Usage:- FixedBlockAllocator<64,1024> newPool;
	template <std::size_t BlockSize = 64, std::size_t BlockCount = 1024>
		class FixedBlockAllocator
		{
			public :
				FixedBlockAllocator();  // Constructor
				~FixedBlockAllocator(); // Destructor

				void *allocate(); // call this funciton to allocate a block;
				void deallocate(void*);	// call this function to deallocate a block;	

			private :
				std::unique_ptr<std::byte[]> memory_pool_; // a unique ptr that will point to the memory pool
									   // will have ownership of the mem_pool
									   // deallocate when goes out of scope
									   //
				std::bitset<BlockCount> free_list_;        // a bit array of BlockCount elements to keep
									   // track of the Blocks and set bit to 1 or 0
									   // based on its avilibility.

		};

	////Implementtaion of template class members

	// constructor
	// intialises the unique_ptr that points to a byte[] of pool size.
	// Here we resrve the memory at once.
	// also sets the tracking pools to true as they are free now.
	template <std::size_t BlockSize, std::size_t BlockCount>
		FixedBlockAllocator<BlockSize, BlockCount>::FixedBlockAllocator()
		{
			memory_pool_ = std::make_unique<std::byte[]>(BlockSize * BlockCount);
			free_list_.set(true);
		}

	//destructor
	template <std::size_t BlockSize, std::size_t BlockCount>
		FixedBlockAllocator<BlockSize, BlockCount>::~FixedBlockAllocator() = default;

	// allocate
	// Algo:
	// check the free list for the first fee block of memory in the pool
	// return it;
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
