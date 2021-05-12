/* Citation and Sources...
Final Project Milestone 5
Module: Car
Filename: Car.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Car.h"
using namespace std;

namespace sdds {
	Car::Car() {
		
		carWash = false;
		
	}
	Car::Car(const char* plate, const char* makeAndModel) :Vehicle(plate, makeAndModel) {
		carWash = false;
	}
	Car::Car(const char* plate, const char* makeAndModel, int wash) : Vehicle(plate, makeAndModel) {
		if (wash == 1) {
			carWash = true;
		}
		else {
			carWash = false;
		}
	}
	std::istream& Car::read(std::istream& istr) {
		if (!isCsv()) {
			cout <<endl << "Car information entry" << endl;
			Vehicle::read();
			cout << "Carwash while parked? (Y)es/(N)o: ";
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
				carWash = true;
			}
		}
		else {
			Vehicle::read();
			
			int num;
			cin >> num;
			
			if (num == 1) {
				carWash = true;
			}
			else {
				carWash = false;
			}
			cin.clear();
			cin.ignore(1000, '\n');

		}
		return istr;
	}
	std::ostream& Car::write(std::ostream& ostr)const {
		if (*this) {
			if (isCsv()) {
				cout << "C,";
				Vehicle::write();
				if (carWash == true) {
					cout << "1" << endl;
				}
				else {
					cout << "0" << endl;
				}
				
			}
			else {
				cout << "Vehicle type: Car" << endl;
				Vehicle::write();
				if (carWash == true) {
					cout << "With Carwash" << endl;
				}
				else {
					cout << "Without Carwash" << endl ;
				}

			}
		}
		else
		{
			cout << "Invalid Car Object" << endl;
		}
		return ostr;
	}
	FileName& operator<<(FileName& f, const Car& c) {
		c.writeF(f);
		return f;
	}
	void Car::writeF(FileName& f) const {
		f << "C" << ",";
		Vehicle::writeF(f);
		if (carWash == true) {
			f << "," << "1" << '\n';
		}
		else {
			f << "," << "0" << '\n';
		}
	}
}