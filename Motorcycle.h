
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
