/*
 * baseClass.hpp
 *
 *  Created on: 25 авг. 2019 г.
 *      Author: blabu
 */

#ifndef BASECLASS_HPP_
#define BASECLASS_HPP_

#include <string>


class baseTest {
public:
	virtual int PrintThis(const std::string& message)=0;
	virtual int sum(int a, int b)=0;
	virtual ~baseTest(){}
};


#endif /* BASECLASS_HPP_ */
