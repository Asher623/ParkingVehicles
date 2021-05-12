
#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include <iostream>
#include "Vehicle.h"

namespace sdds {


	class Car:public Vehicle {

		bool carWash;

	public:
		Car();
		Car(const char* plate, const char* makeAndModel);
		Car(const char* plate, const char* makeAndModel, int wash);
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
		void writeF(FileName& f) const;

	};


	FileName& operator<<(FileName& os, const Car& c);


}
#endif
