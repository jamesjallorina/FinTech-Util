#include "filehandler.h"


#define SLEEP

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


void filehandler::parse(std::string tableName, std::string find)
{
	size_t found = 0;
	bool isStart = false;
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

			/*
			*	search for table name and start hint
			*/
			if(line.find(tableName) != std::string::npos && line.find("start") != std::string::npos && isStart == false)
			{
				std::cout << "found tableName : " << tableName << " start" << std::endl;
				isStart = true;
				continue; 	//continue to the next line
			}
			else
			{
				std::cout << "looping through file " << std::endl;
			}

			if(line.find(tableName) != std::string::npos && line.find("end") != std::string::npos)
			{
				std::cout << "found tableName : " << tableName << " end" << std::endl;
				std::cout << "stop parsing" << std::endl;
				break;
			}

			std::cout << "line : " << line << std::endl;
			std::cout << "finding : " << find << " inside the template" << std::endl;
			found = line.find(find);
			if(found != std::string::npos)
			{
				std::cout << "found key at : " << found << std::endl;
				//size_t ctr = 0;
				size_t pos = 0;
				std::string token = "";
				while((pos = line.find(" ")) != std::string::npos)
				{
					std::cout << "current line : " << line << std::endl;
					//std::cout << "ctr : " << ctr << std::endl;
					//ctr++;
					token = line.substr(0, pos);
					if(token == find)
					{
						std::cout << "skip MC value" << std::endl;
						line.erase(0, pos + 1);	//erase + 1 since it is only space
						continue;
					}
					else
					{
						std::cout << "token : " << token << std::endl;
					//	if(ctr == 2)
					//		templateName = token;
					//	else if(ctr == 3)
					//		templateVal = token;
						templateName = token;
						token = line.erase(0, pos + 1);
						templateVal = token;
					}
#if defined(SLEEP)
					sleep(1);
#endif
				}
				std::cout << "templateName : " << templateName << std::endl;
				std::cout << "templateVal : " << templateVal << std::endl;
			}
#if defined(SLEEP)
			sleep(1);
#endif
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
	p.parse("shcextbindb", "MC");

	return 0;
}