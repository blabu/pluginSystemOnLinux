#ifndef TEST_H
#define TEST_H

#include "baseClass.hpp"

class Test : public baseTest {
public:
    Test();
    virtual ~Test();
    virtual int PrintThis(const std::string& message);
    virtual int sum(int a, int b);
};

typedef baseTest* createTest_t();
typedef void deleteTest_T(baseTest *ptr);

#endif // TEST_H
