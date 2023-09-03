#ifndef COUNTY_H
#define COUNTY_H
#include <string>

class County {
	private:
    	std::string name;
	public:
		int population;
		std::string name;

		County::County(const std::string& _name) : name(_name) {}

		std::string getName() const;

};

#endif

