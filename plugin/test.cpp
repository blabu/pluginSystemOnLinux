#include "test.h"
#include <iostream>

Test::Test() {
    std::cout<<"Create new object from library success\n";
}

Test::~Test() {
	std::cout<<"Destroy object from library success\n";
}

int Test::PrintThis(const std::string &message) {
    std::cout<<"Write new message " << message<<std::endl;
    return static_cast<int>(message.size());
}


int Test::sum(int a, int b) {
	return a*b;
}

extern "C" baseTest* createTest() {
    return new Test();
}

extern "C" void deleteTest(baseTest* ptr) {
    return delete ptr;
}
