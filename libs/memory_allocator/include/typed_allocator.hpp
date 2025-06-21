#include <memory_allocator.hpp>

namespace QuantSys
{
    class TypedAllocator
    {
        public:
            template <typename T>
                T* mem_alloc(); // allocates memory and constructs T using placement new
                                // first allocate the pool based on the sizeof T (can be a struct)
                                // then use placement new to make an object of type T in pool
                                // T *obj = new (pool) T();

            template <typename T>
                void mem_free(T* ptr);

        private:
            FixedBlockAllocator<64, 1024> pool_64_;
            FixedBlockAllocator<128, 1024> pool_128_;
            FixedBlockAllocator<256, 1024> pool_256_;
            FixedBlockAllocator<512, 1024> pool_512_;
            FixedBlockAllocator<1024, 1024> pool_1024_;

            void* get_pool_from_size(std::size_t size);

            void release_to_pool(std::size_t size, void* ptr);
    };

    //Implementation

    inline void TypedAllocator::release_to_pool(std::size_t size, void *ptr)
    {
        if(size)
        {
            if(size <= 64)
            {
                return pool_64_.deallocate(ptr);
            }
            else if(size <=128)
            {
                return pool_128_.deallocate(ptr);
            }
            else if(size <=256)
            {
                return pool_256_.deallocate(ptr);
            }
            else if(size <=512)
            {
                return pool_512_.deallocate(ptr);
            }
            else if(size <=1024)
            {
                return pool_1024_.deallocate(ptr);
            }
        }
    }

    //Algo:-
    //input is thes size of type we want to allocate memory to
    //check if size is valid positive number non zero
    //if size <= 64 choose pool_64_
    //if size <= 128 choose pool_128_
    //if size <= 256 choose pool_256_
    //if size <= 512 choose pool_512_
    //if size <= 1024 choose pool_1024_
    //return the new block of memory from the corresponding pool
    inline void* TypedAllocator::get_pool_from_size(std::size_t size)
    {
        if(size)
        {
            if(size <= 64)
            {
                return pool_64_.allocate();
            }
            else if(size <=128)
            {
                return pool_128_.allocate();
            }
            else if(size <=256)
            {
                return pool_256_.allocate();
            }
            else if(size <=512)
            {
                return pool_512_.allocate();
            }
            else if(size <=1024)
            {
                return pool_1024_.allocate();
            }
        }
        return nullptr;
    }

    //Algo:-
    //Get size of type sent as input
    //send this size to get_pool_from_size and get a valid block of memory_pool
    //use this memory region to create a object of type using placement new.
    template <typename T>
        inline T* TypedAllocator::mem_alloc()
        {
            size_t size_of_type = sizeof(T);

            void* mem = get_pool_from_size(size_of_type);

            if(mem)
            {
                return new (mem) T();           
            }
            std::cout << "Memory exhausted"<< std::endl;
            return nullptr;
        }

    template <typename T>
        inline void TypedAllocator::mem_free(T* ptr)
        {
            size_t size_of_type = sizeof(T);
            ptr->~T();
            release_to_pool(size_of_type, (void*)ptr);
        }
} // namespace QuantSys
