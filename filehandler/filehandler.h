#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <string>
#include <string.h>
#include <stdlib.h>

//for sleep function call
#include <unistd.h>


typedef std::pair<std::string, std::string> PAIR;

class filehandler
{
public:
	filehandler(const std::string filename);
	filehandler(const filehandler &file);
	~filehandler();

	void parse(std::string tableName, std::string find);
	void show();

private:
	filehandler(); //we dont want a default ctor 
	
	std::string filename;
	std::ifstream filestream;
	//std::vector<PAIR> tcontainer;
	std::multimap<std::string, PAIR> mmap;
};

#endif //FILE_HANDLER_H