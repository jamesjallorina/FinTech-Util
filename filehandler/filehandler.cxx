#include "filehandler.h"

#include <iostream>
#include <ifstream>
#include <string>
#include <string.h>
#include <stdlib.h>


filehandler::filehandler()
{
	filename = "";
	tcontainer.reserve(20);
}


filehandler::filehandler(const filehandler &file)
{
	filename = file.filename;	
}

filehandler::~filehandler() {}


void filehandler::readtofile(const char *file)
{
	std::string line = "";
	std::string templateName = "";
	std::string templateVal = "";

	filename = file;
	filestream.open(filename);

	if(filestream.is_open())
	{
		std::cout << "file is okay to read" << std::endl;
	}

	while( getline(filestream, ))



}

void filehandler::show()
{


}



int main(int argc, char **argv)
{


}