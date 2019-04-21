#include "filehandler.h"


#define SLEEP
#define COMMENT '#'

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


void filehandler::parse(std::string tableName/*, std::string find*/)
{
	size_t found = 0;
	size_t pos = 0;
	bool isStart = false;
	std::string token = "";
	std::string line = "";
	std::string templateMember = "";
	std::string templateName = "";
	std::string templateVal = "";


	std::cout << "table name : " << tableName << std::endl;
	//std::cout << "find : " << find << std::endl;

	filestream.open(filename);

	if(filestream.is_open())
	{
		std::cout << "file is okay to read" << std::endl;

		while( getline(filestream, line))
		{
			//check line 
			std::cout << "line : " << line << std::endl;
			if(!isAlpha(line) || isComment(line))
			{
				std::cout << "is a comment or not an alphanumeric and space" << std::endl;
				continue;
			}

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


			//std::cout << "finding : " << find << " inside the template" << std::endl;
			//found = line.find(find);
			//if(found != std::string::npos)
			//{
				//std::cout << "found key at : " << found << std::endl;

			

			std::cout << "current line : " << line << std::endl;
				//std::cout << "ctr : " << ctr << std::endl;
			pos = line.find(" ");

				if(pos != std::string::npos)
					token = line.substr(0, pos);

					
			line.erase(0, pos + 1);
			std::cout << "first token : " << token << std::endl;
			templateMember = token;

				if((pos = line.find(" ")) != std::string::npos)
					token = line.substr(0, pos);
					
					//line.erase(0, pos + 1);	//erase + 1 since it is only space
			std::cout << "second token : " << token << std::endl;
					//	if(ctr == 2)
					//		templateName = token;
					//	else if(ctr == 3)
					//		templateVal = token;
			templateName = token;
			token = line.erase(0, pos + 1);	//erase + 1 since it is only space
			std::cout << "third token : " << token << std::endl;
				templateVal = token;
#if defined(SLEEP)
					sleep(1);
#endif
				
			std::cout << "templateMember : " << templateMember << std::endl;
			std::cout << "templateName : " << templateName << std::endl;
			std::cout << "templateVal : " << templateVal << std::endl;
			mmap.insert(std::make_pair(templateMember + templateName, templateVal));
				//nv.name = templateName;
				//nv.value = templateVal;
				//mmap.insert(templateMember, std::pair<std::string, std::string>(templateName, templateVal));
			//}
#if defined(SLEEP)
			sleep(1);
#endif
		}
	}
	else
	{
		std::cout << "failed to open file" << std::endl;
	}

	filestream.close();
}

bool filehandler::isAlpha(const std::string &input)
{
	std::string::const_iterator it;

	for(it = input.begin(); it != input.end(); ++it)
	{
		//std::cout << "it : " << *it << std::endl;
		if(!isalpha(*it) && !isdigit(*it) && !isspace(*it))
		{
			std::cout << "not an alphanumeric and space" << std::endl;
			return false;
		}
	}
	return true;
}

bool filehandler::isComment(const std::string &input)
{
	std::string::const_iterator it;
	for(it = input.begin(); it != input.end(); ++it)
	{
		if( *it == COMMENT)
			return true;
	}
	
	return false;
}

void filehandler::show()
{
	std::multimap<std::string, std::string>::const_iterator it;

	for(it = mmap.begin(); it != mmap.end(); ++it)
		std::cout << it->first << " "  << it->second << std::endl;

	return;
}



int main(int argc, char **argv)
{
	filehandler p("/home/skye/repository/jamesjallorina/FinTech-Util/filehandler/template.dat");
	//p.parse("shcextbindb", "MC");
	p.parse("shcextbindb");
	p.show();

	return 0;
}