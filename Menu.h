

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
