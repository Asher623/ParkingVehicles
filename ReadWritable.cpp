
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
