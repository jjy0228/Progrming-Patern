#include "MObject.h"
#include <iostream>

MObject::MObject()
{
	std::cout << "생성되었다" << std::endl;
}

MObject::~MObject()
{
	std::cout << "소멸되었다" << std::endl;

}

void MObject::print()
{
	std::cout << "화가난다" << std::endl;
}