#include "MObject.h"
#include <iostream>

MObject::MObject()
{
	std::cout << "�����Ǿ���" << std::endl;
}

MObject::~MObject()
{
	std::cout << "�Ҹ�Ǿ���" << std::endl;

}

void MObject::print()
{
	std::cout << "ȭ������" << std::endl;
}