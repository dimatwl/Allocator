#include "main.h"

void printResult(bool result, const string& name)
{
    if (result)
    {
        cout << name << " Passed" << endl;
    }
    else
    {
        cout << name << " Failed" << endl;
    }
}

void test1()
{
    string name = "Test1";
    buffer_allocator<int> allocator(100);
    int* address1 = allocator.new_element();
    int* address2 = allocator.new_element();
    printResult(address1 != address2, name);
}

void test2()
{
    string name = "Test2";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    printResult(addr_set.size() == 100 && addr_set.count(static_cast<int*>(0)) == 0, name);
}

void test3()
{
    string name = "Test3";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 101; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    printResult(addr_set.size() == 101 && addr_set.count(static_cast<int*>(0)) == 1 && allocator.new_element() == 0, name);
}

void test4()
{
    string name = "Test4";
    buffer_allocator<int> allocator(100);
    int* address = allocator.new_element();
    int magic_value = 123;
    allocator.construct(address, magic_value);
    printResult(*address == magic_value, name);
}

void test5()
{
    string name = "Test5";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    int* freed_address = *iter;
    allocator.delete_element(*iter);

    printResult(allocator.new_element() == freed_address, name);
}

void test6()
{
    string name = "Test6";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    advance(iter, 20);
    int* freed_address = *iter;
    allocator.delete_element(*iter);

    printResult(allocator.new_element() == freed_address, name);
}

int main (int argc, char** argv) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}
