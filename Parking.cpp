/* Citation and Sources...
Final Project Milestone 6
Module: Menu
Filename: Menu.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "Parking.h"
using namespace std;

namespace sdds {
	Parking::Parking() {
		name = nullptr;
		numSpots = 0;
		parkedVehicNum = 0;
		for (int i = 0; i < MAXNUMSPOTS; i++) {
			parkingSpots[i] = nullptr;
		}
	}
	Parking::Parking(const char* datafile, int noOfSpots) {
		if (datafile != nullptr && datafile[0] != '\0' && (noOfSpots > 10 || noOfSpots < MAXNUMSPOTS)) {
			numSpots = noOfSpots;
			parkedVehicNum = 0;
			name = new char[strlen(datafile) + 1];
			strncpy(name, datafile, strlen(datafile) + 1);
			menu = "Parking Menu, select an action:";
			menu.add("Park Vehicle");
			menu.add("Return Vehicle");
			menu.add("List Parked Vehicles");
			menu.add("Close Parking (End of day)");
			menu.add("Exit Program");

		}
		else {
			name = nullptr;
			numSpots = 0;
		}
		for (int i = 0; i < MAXNUMSPOTS; i++) {
			parkingSpots[i] = nullptr;
		}

		if (loadDataFile() == false) {
			cout << "Error in data file" << endl;
		}

	}
	Parking::~Parking() {
		for (int i = 0; i < MAXNUMSPOTS; i++) {
			if (parkingSpots[i] != nullptr) {
				delete parkingSpots[i];
			}
		}
		if (name != nullptr && name[0] != '\0') {
			delete[] name;
		}
	}

	int Parking::run() {
		int num = 1;
		if (*this) {
			do {
				parkingStatus();
				int choice = menu.run();
				if (choice == 1) {
					parkVehicle();
				}
				else if (choice == 2) {
					returnVehicle();
				}
				else if (choice == 3) {
					listParkedVehicles();
				}
				else if (choice == 4) {
					bool check = closeParking();

					if (check) {
						saveDataFile();
						num = 0;
					}
					else {
						cout << "Aborted!" << endl;
					}

				}
				else if (choice == 5) {
					if (exitParkingApp() == false) {
						num = 1;
					}
					else {
						cout << "Exiting program!" << endl;
						saveDataFile();
						num = 0;
					}
				}
			} while (num != 0);


		}
		else {

		}

		return num;

	}

	bool Parking::isEmpty() const {
		bool check = false;
		if (!*this) {
			check = true;
		}
		return check;
	}

	void Parking::parkingStatus() const {
		cout << "****** Seneca Valet Parking ******" << endl;
		int spots = numSpots - parkedVehicNum;
		if (spots < 10) {
			cout << "*****  Available spots: " << spots << "    *****" << endl;
		}
		else {
			cout << "*****  Available spots: " << spots << "   *****" << endl;
		}
		
	}
	void Parking::parkVehicle() {
		if (numSpots == parkedVehicNum) {
			cout << "Parking is full" << endl;
		}
		else {
			Menu innerMenu("Select type of the vehicle:", 1);
			innerMenu.add("Car");
			innerMenu.add("Motorcycle");
			innerMenu.add("Cancel");
			int choice = innerMenu.run();
			int j;
			if (choice == 1) {
				for (int i = 0; i < MAXNUMSPOTS; i++) {
					if (parkingSpots[i] == nullptr) {
						parkingSpots[i] = new Car();
						parkingSpots[i]->read();
						parkingSpots[i]->setParkingSpot(i + 1);
						j = i;
						parkedVehicNum++;
						break;
					}
				}
				cout << endl << "Parking Ticket" << endl;
				parkingSpots[j]->write();
				cout << endl;

			}
			else if (choice == 2) {

				for (int i = 0; i < MAXNUMSPOTS; i++) {
					if (parkingSpots[i] == nullptr) {
						parkingSpots[i] = new Motorcycle();
						parkingSpots[i]->read();
						parkingSpots[i]->setParkingSpot(i + 1);
						j = i;
						parkedVehicNum++;
						break;
					}
				}
				cout << endl << "Parking Ticket" << endl;
				parkingSpots[j]->write();
				cout << endl;
			}
			else if (choice == 3) {
				cout << "Parking cancelled" << endl;
			}
		
		}

	}
	void Parking::returnVehicle() {
		cout << "Return Vehicle" << endl;
		std::cout << "Enter Licence Plate Number: ";
		char plate[9];
		do {

			cin >> plate;

			if (strlen(plate) > 8) {
				cout << "Invalid Licence Plate, try again: ";
			}
			cin.clear();
			cin.ignore(1000, '\n');
		} while (strlen(plate) > 8);
		for (int i = 0; i < 9; i++) {
			if (plate[i] == '\0') {
				break;
			}
			else
			{
				plate[i] = toupper(plate[i]);
			}
		}

		for (int i = 0; i < numSpots; i++) {
			if (parkingSpots[i] != nullptr) {
				if (strcmp(parkingSpots[i]->getLicensePlate(), plate) == 0) {
					cout << endl << "Returning: " << endl;
					parkingSpots[i]->write();
					parkingSpots[i]->setEmpty();
					delete parkingSpots[i];
					parkingSpots[i] = nullptr;
					parkedVehicNum--;
					break;

				}

			}
			if (i == MAXNUMSPOTS - 1) {
				cout << plate << " Not found";
			}

		}
		cout << endl;
	}
	void Parking::listParkedVehicles() const {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < numSpots; i++) {
			if (parkingSpots[i] != nullptr) {
				parkingSpots[i]->write();
				cout << "-------------------------------" << endl;
			}

		}
	}
	bool Parking::closeParking() {
		int count = 0;
		bool closing = false;
		for (int i = 0; i < parkedVehicNum; i++) {
			if (parkingSpots[i] != nullptr) {
				count = 1;
				break;
			}
		}
		if (count == 1) {
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			char input[5];

			do {
				cin >> input;
				cin.clear();
				cin.ignore(1000, '\n');
				if (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N') {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (input[1] == 'e' || input[1] == 'o' || input[1] == 'E' || input[1] == 'O') {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					input[0] = 'u';
				}

			} while (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N');

			if (input[0] == 'y' || input[0] == 'Y') {
				closing = true;
			}
			if (closing == true) {
				cout << "Closing Parking" << endl;
				for (int i = 0; i < parkedVehicNum; i++) {
					cout << endl << "Towing request" << endl;
					cout << "*********************" << endl;
					parkingSpots[i]->write();
					parkingSpots[i]->setEmpty();
					delete parkingSpots[i];					
					parkingSpots[i] = nullptr;
				}
				for (int i = 0; i < MAXNUMSPOTS; i++) {
					if (parkingSpots[i] != nullptr) {
						delete parkingSpots[i];
					}
				}

			}

		}
		return closing;
	}
	bool Parking::exitParkingApp() const {
		cout << "This will terminate the program!" << endl << "Are you sure? (Y)es/(N)o: ";
		char input[5];
		do {
			cin >> input;
			cin.clear();
			cin.ignore(1000, '\n');
			if (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N') {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
			else if (input[1] == 'e' || input[1] == 'o' || input[1] == 'E' || input[1] == 'O') {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				input[0] = 'u';
			}

		} while (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N');
		bool check = false;
		if (input[0] == 'y' || input[0] == 'Y') {
			check = true;
		}
		return check;

	}
	bool Parking::loadDataFile() {
		bool check = false;
		if (*this) {
			for (int i = 0; i < MAXNUMSPOTS; i++) {
				if (parkingSpots[i] != nullptr) {
					delete parkingSpots[i];
				}
			}

			ifstream file("ParkingData.csv");
			string line;
			int a = 0;
			while (getline(file, line)) {
				char plate[9] = "";
				char makeAndModel[61] = "";
				int commaCount = 0;
				char parkingspotNum[2] = "";
				int vehicleState = 0;
				int count = 0;
				int linelenght = line.length();
				for (int i = 0; i < linelenght; i++) {
					if (line[i] == ',') {
						commaCount++;
						count = 0;
					}
					else {

						if (commaCount == 1) {
							parkingspotNum[count] = line[i];
							count++;
						}
						else if (commaCount == 2) {
							plate[count] = line[i];
							count++;
						}
						else if (commaCount == 3) {
							makeAndModel[count] = line[i];
							count++;
						}
						else if (commaCount == 4) {
							vehicleState = (int)line[i] - 48;
						}
					}


				}
				if (parkingSpots[a] != nullptr) {
					delete parkingSpots[a];
				}
				if (line[0] == 'C') {

					parkingSpots[a] = new Car(plate, makeAndModel, vehicleState);

					if (parkingspotNum[1] != '\0') {
						parkingSpots[a]->setParkingSpot(((int)parkingspotNum[0] - 48) * 10 + ((int)parkingspotNum[1] - 48));
					}
					else {
						parkingSpots[a]->setParkingSpot((int)parkingspotNum[0] - 48);
					}

				}
				else {
					parkingSpots[a] = new Motorcycle(plate, makeAndModel, vehicleState);
					if (parkingspotNum[1] != '\0') {
						parkingSpots[a]->setParkingSpot(((int)parkingspotNum[0] - 48) * 10 + ((int)parkingspotNum[1] - 48));
					}
					else {
						parkingSpots[a]->setParkingSpot((int)parkingspotNum[0] - 48);
					}
				}
				a++;
				parkedVehicNum++;
			}
			line.clear();
			file.close();
			check = true;
		}

		return check;
	}
	void Parking::saveDataFile() const {
		if (*this) {

			FileName file("ParkingData.csv");
			for (int i = 0; i < numSpots; i++) {
				if (parkingSpots[i] != nullptr) {

					file << *parkingSpots[i];
				}

			}


			file.close();


		}

	}

}