

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Motorcycle.h"
using namespace std;

namespace sdds {

	Motorcycle::Motorcycle() {

		sideCar = false;

	}
	Motorcycle::Motorcycle(const char* plate, const char* makeAndModel) :Vehicle(plate, makeAndModel) {
		sideCar = false;
	}
	Motorcycle::Motorcycle(const char* plate, const char* makeAndModel, int side) :Vehicle(plate, makeAndModel) {
		if (side == 1) {
			sideCar = true;
		}
		else {
			sideCar = false;
		}
	}

	std::istream& Motorcycle::read(std::istream& istr) {
		if (!isCsv()) {
			cout <<endl << "Motorcycle information entry" << endl;
			Vehicle::read();
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			char input[5];
			do {
				cin >> input;
				
				if (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N') {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (input[1] == 'e' || input[1] == 'o' || input[1] == 'E' || input[1] == 'O') {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					input[0] = 'u';
				}

			} while (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N');

			if (input[0] == 'y' || input[0] == 'Y') {
				sideCar = true;
			}
		}
		else {
			Vehicle::read();
			int num;
			cin >> num;


			if (num == 1) {
				sideCar = true;
			}
			else {
				sideCar = false;
			}
			cin.clear();
			cin.ignore(1000, '\n');

		}
		return istr;
	}

	std::ostream& Motorcycle::write(std::ostream& ostr)const {
		if (*this) {
			if (isCsv()) {
				cout << "M,";
				Vehicle::write();
				if (sideCar == true) {
					cout << "1" << endl;
				}
				else {
					cout << "0" << endl;
				}

			}
			else {
				cout << "Vehicle type: Motorcycle" << endl;
				Vehicle::write();
				if (sideCar == true) {
					cout << "With Sidecar" << endl;
				}

			}
		}
		else
		{
			cout << "Invalid Motorcycle Object" << endl;
		}
		return ostr;
	}
	FileName& operator<<(FileName& f, const Motorcycle& m) {
		m.writeF(f);
		return f;
	}
	void Motorcycle::writeF(FileName& f) const {
		f << "M" << ",";
		Vehicle::writeF(f);
		if (sideCar == true) {
			f << "," << "1" << '\n';
		}
		else {
			f << "," << "0" << '\n';
		}
	}
}
