/* Citation and Sources...
Final Project Milestone 5
Module: Motorcycle
Filename: Motorcycle.h
Version 1.0
Author Ivan Anferov
Revision History
-----------------------------------------------------------
Date Reason
2020/07/30 Preliminary release
2020/07/30 Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_H
#include <iostream>
#include "Vehicle.h"

namespace sdds {

	class Motorcycle : public Vehicle {

		bool sideCar;

	public:
		Motorcycle();
		Motorcycle(const char* plate, const char* makeAndModel);
		Motorcycle(const char* plate, const char* makeAndModel, int side);
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
		void writeF(FileName& f) const;
	};
	FileName& operator<<(FileName& os, const Motorcycle& m);
}
#endif