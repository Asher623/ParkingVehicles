/* Citation and Sources...
Final Project Milestone 1
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

#ifndef SDDS_ENGINE_H
#define SDDS_ENGINE_H
#include <iostream>

namespace sdds {

	const int MAX_NO_OF_ITEMS = 10;

	class MenuItem {
		char* name;
		friend class Menu;
	public:
		MenuItem();
		MenuItem(const char* newName);
		~MenuItem();
	};
	class Menu {
		char* title;
		MenuItem menuItems[MAX_NO_OF_ITEMS];
		int indentation;
		int itemCount = 0;

	public:
		Menu();
		
		Menu(const char* newTitle, int indent = 0);
		
		Menu(const Menu& menu);
		bool isEmpty() const;
		void display() const;
		void add(const char* item);
		Menu& operator<<(const char* item);
		Menu& operator=(const char* newTitle);
		Menu& operator=(const Menu& menu);
		operator int() const;
		int run() const;
		~Menu();
		
		explicit operator bool() const { return title != nullptr && title[0] != '\0';}

		
	};
}
#endif