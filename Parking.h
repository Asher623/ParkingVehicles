

#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"


namespace sdds {

	const int MAXNUMSPOTS = 100;

	class Parking {

		char* name;
		Menu menu;
		int numSpots;
		Vehicle* parkingSpots[MAXNUMSPOTS];
		int parkedVehicNum;


	public:
		Parking();
		Parking(const char* datafile, int noOfSpots);
		~Parking();
		int run();
		bool isEmpty() const;
		void parkingStatus() const;
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicles() const;
		bool closeParking();
		bool exitParkingApp() const;
		bool loadDataFile();
		void saveDataFile() const;

		explicit operator bool() const { return name != nullptr && name[0] != '\0'; }
	};

	
}

#endif
