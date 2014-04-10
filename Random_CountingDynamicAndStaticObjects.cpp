// count the number of alive and created objects of a class A
// that are created by dynamic allocation and non-dynamic/static allocate
// TODO: I havent figured out how to handle dynamic array allocation
#include <iostream>
#include <cassert>

class A {
public:
	static int numObjsAlive;
	static int numObjsCreated;
	static int numDynamicObjsAlive;
	static int numDynamicObjsCreated;

	A() {
		++numObjsAlive;
		++numObjsCreated;
	}

	~A() {
		--numObjsAlive;
		assert(numObjsAlive >= 0);
	}

	void* operator new(size_t size);
	void operator delete(void* p);
	/*
	void* operator new[](size_t size);
	void operator delete[](void* p);
	*/

};

int A::numObjsAlive = 0;
int A::numObjsCreated = 0;
int A::numDynamicObjsAlive = 0;
int A::numDynamicObjsCreated = 0;

void* A::operator new(size_t size){
	void* p = std::malloc(size);
	assert(p != NULL);
	A::numDynamicObjsAlive++;
	A::numDynamicObjsCreated++;
	return p;
}

void A::operator delete(void* p) {
	assert(p!= NULL);
	free(p);
	A::numDynamicObjsAlive--;
}

/*
void* A::operator new[](size_t size){
	void* p = std::malloc(size);
	assert(p != NULL);
	A::numDynamicObjsAlive += (size/sizeof(A));
	A::numDynamicObjsCreated += (size / sizeof(A));
	return p;
}

void A::operator delete[](void* p) {
	assert(p != NULL);
	free(p);
	A::numDynamicObjsAlive--;
}
*/


void printMem() {
	std::cout << A::numDynamicObjsAlive << " " << A::numDynamicObjsCreated << " "
		<< A::numObjsAlive << " " << A::numObjsCreated << std::endl;
}

int mainCountDynamicAllocated() {
	A a[100];
	A* aDyn = new A();
	//A* aDynArr = new A[100](); // Dont know how to do it for dynamic allocated arrays
	printMem();
	delete aDyn;
	//delete[] aDynArr; // Dont know how to do it for dynamic allocated arrays
	printMem();
	return 0;
}

