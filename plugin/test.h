#ifndef TEST_H
#define TEST_H

#include "../project/baseClass.hpp"

class Test : public baseTest {
public:
    Test();
    virtual ~Test();
    virtual int PrintThis(const std::string& message);
    virtual int sum(int a, int b);
};

#endif // TEST_H
