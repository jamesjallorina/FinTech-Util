#include "filehandler.h"


#if 0
filehandler::filehandler()
{
	filename = "";
}
#endif

filehandler::filehandler(const std::string filename)
{
	this->filename = filename;
}

filehandler::filehandler(const filehandler &file)
{
	filename = file.filename;	
}

filehandler::~filehandler() {}


void filehandler::readtofile(std::string tableName, std::string find)
{
	size_t found = 0;
	std::string line = "";
	std::string templateName = "";
	std::string templateVal = "";


	std::cout << "table name : " << tableName << std::endl;
	std::cout << "find : " << find << std::endl;

	filestream.open(filename);

	if(filestream.is_open())
	{
		std::cout << "file is okay to read" << std::endl;

		while( getline(filestream, line))
		{
			//file handling should start with table name and start
			if(line.find(tableName) != std::string::npos && line.find("start") != std::string::npos)
			{
				std::cout << "start parsing values for table : " << tableName << std::endl;
			}
			else
			{
				
			}

			std::cout << "line : " << line << std::endl;
			std::cout << "finding : " << find << " inside the template" << std::endl;
			found = line.find(find);
			if(found != std::string::npos)
			{
				std::cout << "found key at : " << found << std::endl;
			}
		}
	}
	else
	{
		std::cout << "failed to open file" << std::endl;
	}

}

void filehandler::show()
{

}



int main(int argc, char **argv)
{
	filehandler p("/home/skye/repository/jamesjallorina/FinTech-Util/filehandler/template.dat");
	p.readtofile("shcextbindb", "MC");

	return 0;
}