/* Citation and Sources...
Final Project Milestone 6
Module: Menu
Filename: Menu.h
Version 1.0
Author Ivan Anferov
Revision History
-----------------------------------------------------------
Date Reason
2020/07/08 Preliminary release
2020/07/08 Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

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