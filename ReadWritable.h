
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>

namespace sdds {

	class ReadWritable {

		bool commaSeparated;

	public:
		ReadWritable() { commaSeparated = false; };
		virtual ~ReadWritable();
		bool isCsv()const { return commaSeparated; };
		void setCsv(bool value) { commaSeparated = value; };
		virtual std::ostream& write(std::ostream& ostr = std::cout)const = 0;
		virtual std::istream& read(std::istream& istr = std::cin) = 0 ;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);

}
#endif
