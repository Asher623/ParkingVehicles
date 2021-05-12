/* Citation and Sources...
Final Project Milestone 3
Module: ReadWritable
Filename: ReadWritable.h
Version 1.0
Author Ivan Anferov
Revision History
-----------------------------------------------------------
Date Reason
2020/07/08 Preliminary release
2020/07/22 Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "ReadWritable.h"
using namespace std;

namespace sdds {

	
	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw) {
		rw.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, ReadWritable& rw) {
		rw.read(is);
		return is;
	}
	ReadWritable::~ReadWritable() {
		
	}
}