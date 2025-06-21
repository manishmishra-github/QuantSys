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

}
