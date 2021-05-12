/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.h
Version 1.0
Author Ivan Anferov
Revision History
-----------------------------------------------------------
Date Reason
2020/07/08 Preliminary release
2020/07/23 Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include <iostream>
#include "ReadWritable.h"
#include <fstream> 

namespace sdds {

	class FileName;

	class Vehicle :public ReadWritable {

		char licensePlate[9];
		char* makeModel;
		int parkingSpotNumber;

	protected:
		bool isEmpty() const;
		
		char* getMakeModel() const { return makeModel; };
		void setMakeModel(const char* makeAndModel);

	public:
		Vehicle();
		Vehicle(const char* plate, const char* makeAndModel);
		~Vehicle();
		void setEmpty();
		char* getLicensePlate() { return licensePlate; };
		int getParkingSpot() const { return parkingSpotNumber; };
		void setParkingSpot(int spot);
		bool operator==(const Vehicle& vehicle) const;
		bool operator==(const char* plate) const;
		std::ostream& write(std::ostream& ostr = std::cout)const;
		std::istream& read(std::istream& istr = std::cin);
		virtual void writeF(FileName& f) const;

		explicit operator bool() const { return licensePlate != nullptr && licensePlate[0] != '\0'; }


	};

	class FileName {
	public:
		std::ofstream f;
		FileName(const char*);
		FileName& operator<<(char);
		FileName& operator<<(const char*);
		FileName& operator<<(int);
		void close();
	};
	FileName& operator<<(FileName& os, const Vehicle& v);
}
#endif