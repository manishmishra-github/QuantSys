#include <typed_allocator.hpp>
#include <iostream>
#include <cassert>

struct Dummy 
{
    int id;
    double price;
    Dummy() : id(0), price(0.0){}
};

int main()
{
    QuantSys::TypedAllocator allocator; //intialise an object of the allocator

    Dummy* my_obj = allocator.mem_alloc<Dummy>();

    my_obj->id = 10;
    my_obj->price = 200.50;

    assert(my_obj->id == 10);
    assert(my_obj->price == 200.50);

    std::cout << "[PASS] Dummy allocated and values set\n";

    allocator.mem_free(my_obj);
    allocator.mem_free(my_obj);
    allocator.mem_free(my_obj);
    std::cout << "[PASS] Dummy deallocated successfully\n";
    return 0;
}
