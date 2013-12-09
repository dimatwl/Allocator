#include "main.h"

int main (int argc, char** argv) {
	cout << "HOLA" << endl;
	buffer_allocator<int> allocator(100);
	allocator.new_element();
	allocator.construct(0, 5);
    return 0;
}
