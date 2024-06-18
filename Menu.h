#ifndef Menu_H
#define Menu_H

#include <vector>
#include <string>

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
