/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Vehicle.h"
#include <fstream>
using namespace std;

namespace sdds {

	Vehicle::Vehicle() {
		licensePlate[0] = '\0';
		makeModel = nullptr;
		parkingSpotNumber = 0;
	}
	Vehicle::Vehicle(const char* plate, const char* makeAndModel) {
		if (plate != nullptr && plate[0] != '\0' && makeAndModel != nullptr && makeAndModel[0] != '\0' && strlen(plate) <= 8 && strlen(makeAndModel) > 1) {
			strcpy(licensePlate, plate);
			makeModel = new char[strlen(makeAndModel) + 1];
			strncpy(makeModel, makeAndModel, strlen(makeAndModel) + 1);

		}
		else {
			licensePlate[0] = '\0';
			makeModel = nullptr;
		}
		parkingSpotNumber = 0;
	}
	void Vehicle::setEmpty() {
		if (makeModel != nullptr && makeModel[0] != '\0') {
			delete[] makeModel;
			makeModel = nullptr;
		}
		licensePlate[0] = '\0';
		parkingSpotNumber = 0;
	}
	bool Vehicle::isEmpty() const {
		bool check = false;
		if (*this) {
			check = true;
		}
		return check;
	}
	void Vehicle::setMakeModel(const char* makeAndModel) {
		delete[] makeModel;
		makeModel = nullptr;
		if (makeAndModel != nullptr && makeAndModel[0] != '\0') {
			
			makeModel = new char[strlen(makeAndModel) + 1];
			strncpy(makeModel, makeAndModel, strlen(makeAndModel) + 1);
		}
		else {
			
			setEmpty();
		}
	}

	void Vehicle::setParkingSpot(int spot) {
		if (spot < 0) {

			setEmpty();
			
		}
		else
		{
			parkingSpotNumber = spot;
		}
	}
	bool Vehicle::operator==(const Vehicle& vehicle) const {
		char plate[9] = "";

		char plateTwo[9] = "";
		
		bool check = false;
		for (int i = 0; i < 9; i++) {
			if (plate[i] != '\0') {
				plate[i] = toupper(licensePlate[i]);
			}
			if (plateTwo[i] != '\0') {
				plateTwo[i] = toupper(vehicle.licensePlate[i]);
			}
			
			
		}
		if (strcmp(plate, plateTwo) == 0) {
			check = true;
		}
		return check;
		
	}
	bool Vehicle::operator==(const char* plate) const {
		char plateOne[9] = "";
		strcpy(plateOne, licensePlate);
		char plateTwo[9] = "";
		strcpy(plateTwo, plate);
		bool check = false;
		for (int i = 0; i < 9; i++) {
			if (plateOne[i] != '\0') {
				plateOne[i] = toupper(plateOne[i]);
			}
			if (plateTwo[i] != '\0') {
				plateTwo[i] = toupper(plateTwo[i]);
			}

		}
		if (strcmp(plateOne,plateTwo) == 0) {
			check = true;
		}
		return check;
	}
	Vehicle::~Vehicle() {
		if (makeModel != nullptr && makeModel[0] != '\0') {
			delete[] makeModel;
		}
		
	}
	std::ostream& Vehicle::write(std::ostream& ostr)const {
		if (*this) {
			if (isCsv() == true) {
				ostr << parkingSpotNumber << ',' << licensePlate << "," << makeModel << ",";
			}
			else
			{
				if (parkingSpotNumber == 0) {
					ostr << "Parking Spot Number: N/A" << endl;
				}
				else
				{
					ostr << "Parking Spot Number: " << getParkingSpot() << endl;
				}
				
				ostr << "Licence Plate: " << licensePlate << endl;
				ostr << "Make and Model: " << getMakeModel() << endl;
			}

		}
		else
		{
			ostr << "Invalid Vehicle Object" << endl;
		}
			
		return ostr;
		
	}

	std::istream& Vehicle::read(std::istream& istr) {
		if (!isCsv() == true) {
			char makeAndModel[61] = "abc";
			std::cout << "Enter Licence Plate Number: ";
			do {
				
				istr.getline(licensePlate, 20);

				if (strlen(licensePlate) > 8 || licensePlate[0] == '\0' || licensePlate[0] == '\n')  {
					cout << "Invalid Licence Plate, try again: ";
				}
				cin.clear();
			} while (strlen(licensePlate) > 8 || licensePlate[0] == '\0' || licensePlate[0] == '\n');

			for (int i = 0; i < 9; i++) {
				if (licensePlate[i] == '\0') {
					break;
				}
				else
				{
					licensePlate[i] = toupper(licensePlate[i]);
				}
			}
			
			std::cout << "Enter Make and Model: ";
			do {

				istr.getline(makeAndModel, 61);

				if (strlen(makeAndModel) < 2  || makeAndModel[0] == '\0' || makeAndModel[0] == '\n') {
					cout << "Invalid Make and model, try again: ";	
				}
				cin.clear();
				//cin.ignore(1000, '\n');
				
			} while (strlen(makeAndModel) < 2 || makeAndModel[0] == '\0' || makeAndModel[0] == '\n');
			setMakeModel(makeAndModel);

		}
		else {
			char makeChar[61] = "";
			cin >> parkingSpotNumber;
			cin.ignore(1, ',');
			cin.getline(licensePlate, 9, ',');
			cin.getline(makeChar, 60, ',');
			
			delete[] makeModel;
			makeModel = nullptr;
			makeModel = new char[strlen(makeChar) + 1];
			strncpy(makeModel, makeChar, strlen(makeChar) + 1);

			

		}
		return istr;
	}

	FileName& operator<<(FileName& f, const Vehicle& v) {
		v.writeF(f);
		return f;
	}
	FileName::FileName(const char* c):f(c) {
	}
	void Vehicle::writeF(FileName& f) const {
		f << getParkingSpot() << "," << licensePlate << "," << getMakeModel();

	}
	FileName& FileName::operator<<(char c) {
		f << c;
		return *this;
	}
	FileName& FileName::operator << (const char* c) {
		f << c;
		return *this;
	}
	FileName& FileName::operator<<(int i) {
		f << i;
		return *this;
	}
	void FileName::close() {
		f.close();
	}


}