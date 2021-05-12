

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Menu.h"
using namespace std;

namespace sdds {

	Menu::Menu() {
		title = nullptr;
		
		indentation = 0;
		itemCount = 0;


	}
	Menu::Menu(const char* newTitle, int indent) {
		
		if (newTitle[0] != '\0' && newTitle != nullptr) {
			title = new char[strlen(newTitle) + 1];
			strncpy(title, newTitle, strlen(newTitle)+1);
		}
		else {
			title = nullptr;
		}
		indentation = 0;
		if (indent > 0) {
			indentation = indent;
		}
		
		itemCount = 0;
		
	}
	
	bool Menu::isEmpty() const {
		bool check = false;
		if (!*this) {
			check = true;
		}
		return check;
	}


	Menu::Menu(const Menu& menu) {

		for (int i = 0; i < menu.itemCount; i++) {
			menuItems[i].name = new char [strlen(menu.menuItems[i].name)+1];
			strncpy(menuItems[i].name, menu.menuItems[i].name, strlen(menu.menuItems[i].name)+1);
		}
		itemCount = menu.itemCount;
		title = new char[strlen(menu.title)+1];
		strncpy(title, menu.title, strlen(menu.title)+1);
		indentation = menu.indentation;

	}
	Menu& Menu::operator=(const Menu& menu) {
		if(menu){
			for (int i = 0; i < menu.itemCount; i++) {
				
				delete[] menuItems[i].name;
				
				menuItems[i].name = new char [strlen(menu.menuItems[i].name)+1];
				strncpy(menuItems[i].name, menu.menuItems[i].name, strlen(menu.menuItems[i].name)+1);
			}
			itemCount = menu.itemCount;
			delete [] title;
			title = new char[strlen(menu.title)+1];
			strncpy(title, menu.title, strlen(menu.title)+1);
			indentation = menu.indentation;
			}
		else {
			
			delete[] title;
			title = nullptr;
			indentation = 0;
			itemCount = 0;
			
			
		}
		return *this;
	}

	void Menu::add(const char* item) {

		if (item != nullptr && item[0] != '\0') {
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

				if (menuItems[i].name == nullptr || menuItems[i].name[0] == '\0') {
					if (menuItems[i].name != nullptr) {
						delete[] menuItems[i].name;
					}
					menuItems[i].name = new char[strlen(item)+1];
					strncpy(menuItems[i].name, item, strlen(item)+1);
					
					itemCount++;
					break;
				}
			}
			
		}
		else
		{
			if (title != nullptr && title[0] != '\0') {
				delete[] title;
			}
			title = nullptr;
			itemCount = 0;
			indentation = 0;
			
		}
		
	}
	

	void Menu::display() const {
		int leap = 0;
		if (*this) {
			
				for (int i = 0; i < indentation; i++) {
					leap += 4;
				}
				cout << string(leap, ' ') << title << endl;
				if (itemCount == 0) {
					cout << "No Items to display!" << endl;
				}
				else
				{
					
					for (int i = 0; i < itemCount; i++) {
						cout << string(leap, ' ') << i + 1 << "- " << menuItems[i].name << endl;
					}
					cout << string(leap, ' ') << "> ";
				}
			
		} 
		else {
			cout << "Invalid Menu!" << endl;
		}
		
	}

	Menu& Menu::operator<<(const char* item){
		if (*this) {
			if (item != nullptr && item[0] != '\0') {
				add(item);
			}
			else {
				if (title != nullptr && title[0] != '\0') {
					delete[] title;
					title = nullptr;
					itemCount = 0;
				}
			}
		}
		
		return *this;
			
	}
	int Menu::run() const{
		int num = 0;
		display();
		if (*this) {
			if (itemCount == 0) {
				num = 0;
			}
			else
			{
				do {

					cin >> num;

					if (!cin) {
						cout << "Invalid Integer, try again: ";
					}
					else if (num < 1 || num > itemCount) {
						cout << "Invalid selection, try again: ";
					}
					cin.clear();
					cin.ignore(1000, '\n');

				} while (num < 1 || num > itemCount);
			}
		}
		
		
		return num;
	}
	Menu::operator int() const {
		 int num = run();
		 return num;
	}
	Menu& Menu::operator=(const char* newTitle) {
		if (newTitle[0] != '\0' && newTitle != nullptr) {
			delete[] title;
			title = new char[strlen(newTitle) + 1];
			strncpy(title, newTitle, strlen(newTitle) + 1);
		}
		else
		{

			if (title != nullptr && title[0] != '\0') {
				delete[] title;
				title = nullptr;
			}
			itemCount = 0;
		}
		return *this;
		
	}

	Menu::~Menu() {
		if (title != nullptr && title[0] != '\0') {
			delete[] title;
		}
		
	}
	MenuItem::~MenuItem() {
	
		if (name != nullptr && name[0] != '\0') {
			delete[] name;
		}

	}

	MenuItem::MenuItem(const char* newName) {
		if (newName != nullptr && newName[0] != '\0') {
			name = new char[strlen(newName) + 1];
			strncpy(name, newName, strlen(newName) + 1);
		}
		else
		{
			name = nullptr;
		}
	}
	MenuItem::MenuItem() {
		name = nullptr;
	}
}

