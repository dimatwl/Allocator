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
    printResult(address1 != address2 && allocator.get_number_of_descriptors() == 1, name);
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
    printResult(addr_set.size() == 100 && addr_set.count(static_cast<int*>(0)) == 0 && allocator.get_number_of_descriptors() == 0, name);
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
    printResult(addr_set.size() == 101 && addr_set.count(static_cast<int*>(0)) == 1 && allocator.new_element() == 0 && allocator.get_number_of_descriptors() == 0, name);
}

void test4()
{
    string name = "Test4";
    buffer_allocator<int> allocator(100);
    int* address = allocator.new_element();
    int magic_value = 123;
    allocator.construct(address, magic_value);
    printResult(*address == magic_value && allocator.get_number_of_descriptors() == 1, name);
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

void test7()
{
    string name = "Test7";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    advance(iter, 99);
    int* freed_address = *iter;
    allocator.delete_element(*iter);

    printResult(allocator.new_element() == freed_address, name);
}

void test8()
{
    string name = "Test8";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    advance(iter, 100);
    allocator.delete_element(*iter);

    printResult(allocator.new_element() == 0, name);
}

void test9()
{
    string name = "Test9";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    advance(iter, 99);
    int* freed_address = (*iter) + 1;
    allocator.delete_element(freed_address);
    printResult(allocator.new_element() == 0, name);
}

void test10()
{
    string name = "Test10";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    int* freed_address = (*iter) - 1;
    allocator.delete_element(freed_address);
    printResult(allocator.new_element() == 0, name);
}

void test11()
{
    string name = "Test11";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.begin(); iter != addr_set.end(); ++iter)
    {
        allocator.delete_element(*iter);
    }
    printResult(allocator.new_element() != 0  && allocator.get_number_of_descriptors() == 1, name);
}

void test12()
{
    string name = "Test12";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.begin(); iter != addr_set.end(); advance(iter, 2))
    {
        allocator.delete_element(*iter);
    }
    set<int*> addr_set2;
    for (size_t i = 0; i < 50; ++i)
    {
        addr_set2.insert(allocator.new_element());
    }
    printResult
    (
        allocator.new_element() == 0 
        && 
        addr_set2.size() == 50
        && 
        addr_set.count(static_cast<int*>(0)) == 0
        && 
        includes(addr_set.begin(), addr_set.end(), addr_set2.begin(), addr_set2.end())
        &&
        allocator.get_number_of_descriptors() == 0
        , 
        name
    );
}

void test13()
{
    string name = "Test13";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.begin(); iter != addr_set.end(); advance(iter, 2))
    {
        allocator.delete_element(*iter);
    }
    set<int*> addr_set2;
    for (size_t i = 0; i < 51; ++i)
    {
        addr_set2.insert(allocator.new_element());
    }
    printResult
    (
        allocator.new_element() == 0 
        && 
        addr_set2.size() == 51
        && 
        addr_set2.count(static_cast<int*>(0)) == 1
        && 
        !includes(addr_set.begin(), addr_set.end(), addr_set2.begin(), addr_set2.end())
        &&
        allocator.get_number_of_descriptors() == 0
        , 
        name
    );
}

void test14()
{
    string name = "Test14";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.begin(); iter != addr_set.end(); advance(iter, 2))
    {
        allocator.delete_element(*iter);
    }
    printResult
    (
        allocator.get_number_of_descriptors() == 50
        , 
        name
    );
}

void test15()
{
    string name = "Test15";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.rbegin(); iter != addr_set.rend(); advance(iter, 2))
    {
        allocator.delete_element(*iter);
    }
    set<int*> addr_set2;
    for (size_t i = 0; i < 50; ++i)
    {
        addr_set2.insert(allocator.new_element());
    }
    printResult
    (
        allocator.new_element() == 0 
        && 
        addr_set2.size() == 50
        && 
        addr_set.count(static_cast<int*>(0)) == 0
        && 
        includes(addr_set.begin(), addr_set.end(), addr_set2.begin(), addr_set2.end())
        &&
        allocator.get_number_of_descriptors() == 0
        , 
        name
    );
}

void test16()
{
    string name = "Test16";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    for (auto iter = addr_set.rbegin(); iter != addr_set.rend(); advance(iter, 2))
    {
        allocator.delete_element(*iter);
    }
    printResult
    (
        allocator.get_number_of_descriptors() == 50
        , 
        name
    );
}

void test17()
{
    string name = "Test17";
    buffer_allocator<int> allocator(100);
    set<int*> addr_set;
    for (size_t i = 0; i < 100; ++i)
    {
        addr_set.insert(allocator.new_element());
    }
    auto iter = addr_set.begin();
    advance(iter, 50);
    allocator.delete_element(*iter);
    size_t descr_count1 = allocator.get_number_of_descriptors();
    advance(iter, 2);
    allocator.delete_element(*iter);
    size_t descr_count2 = allocator.get_number_of_descriptors();
    advance(iter, -1);
    allocator.delete_element(*iter);
    size_t descr_count3 = allocator.get_number_of_descriptors();
    printResult
    (
        descr_count1 == 1
        &&
        descr_count2 == 2
        &&
        descr_count3 == 1
        , 
        name
    );
}

int main (int argc, char** argv) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    return 0;
}
