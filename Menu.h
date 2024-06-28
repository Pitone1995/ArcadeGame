#ifndef Menu_H
#define Menu_H

#include <vector>
#include <string>

/*
cannot use here using namespace std because of the following compilation error:
	C:/msys64/ucrt64/include/rpcndr.h:64:11: error: reference to 'byte' is ambiguous
   	64 |   typedef byte cs_byte;
*/

class Menu {

public:

	Menu(std::vector<std::string> &options);
	~Menu();

	int run();
	void showOpt();
	void clear();

private:

	std::vector<std::string> m_options;
	int m_selIndex = 0;
};

#endif
