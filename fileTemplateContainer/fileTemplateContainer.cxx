#include "fileTemplateContainer.h"


//#define SLEEP
#define COMMENT '#'

#if 0
fileTemplateContainer::fileTemplateContainer()
{
	filename = "";
}
#endif

template <typename T, typename Iterator>
fileTemplateContainer<T, Iterator>::fileTemplateContainer(const std::string filename)
{
	this->filename = filename;
}

template <typename T, typename Iterator>
fileTemplateContainer<T, Iterator>::fileTemplateContainer(const fileTemplateContainer &file)
{
	filename = file.filename;	
}

template <typename T, typename Iterator>
fileTemplateContainer<T, Iterator>::~fileTemplateContainer() {}


template <typename T, typename Iterator>
void fileTemplateContainer<T, Iterator>::parse(std::string tableName/*, std::string find*/)
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
			param.insert(std::make_pair(templateMember + templateName, templateVal));
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

template <typename T, typename Iterator>
bool fileTemplateContainer<T, Iterator>::find(const std::string &key, std::string &value)
{
	Iterator it;

	for(it = param.begin(); it != param.end(); ++it)
	{
		if(it->first == key)
		{
			value = it->second;
			return true;
		}
	}
	return false;
}

template <typename T, typename Iterator>
void fileTemplateContainer<T, Iterator>::show()
{
	Iterator it;

	for(it = param.begin(); it != param.end(); ++it)
		std::cout << it->first << " "  << it->second << std::endl;

	return;
}

template <typename T, typename Iterator>
bool fileTemplateContainer<T, Iterator>::isAlpha(const std::string &input)
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

template <typename T, typename Iterator>
bool fileTemplateContainer<T, Iterator>::isComment(const std::string &input)
{
	std::string::const_iterator it;
	for(it = input.begin(); it != input.end(); ++it)
	{
		if( *it == COMMENT)
			return true;
	}
	
	return false;
}





int main(int argc, char **argv)
{
	std::string value = "";
	//fileTemplateContainer <umap, iter> p("/home/skye/repository/jamesjallorina/FinTech-Util/fileTemplateContainer/param_template.dat");
	//fileTemplateContainer <umap, iter> p("/home/skye/repository/FinTech-Util/fileTemplateContainer/param_template.dat");
	//p.parse("shcextbindb", "MC");
	if(argc < 2)
	{
		std::cout << "usage: " << std::endl;

		std::cout << "fileTemplateContainer [filename]" << std::endl;
		return EXIT_FAILURE;
	}

	fileTemplateContainer <umap, iter> p(argv[1]);
	p.parse("shcextbindb");
	p.show();

	std::cout << "test find key" << std::endl;

	//test find key
	if( p.find("MClowbin", value))
		std::cout << "found MClowbin : " << value << std::endl;
	else
		std::cout << " can't find MClowbin" << std::endl;

	if( p.find("MChighbin", value))
		std::cout << "found MChighbin : " << value << std::endl;
	else
		std::cout << "can't find MChighbin" << std::endl;

	if( p.find("MCcardproduct", value))
		std::cout << "found MCcardproduct : " << value << std::endl;
	else
		std::cout << "can't find MCcardproduct" << std::endl;

	std::cout << "test cannot find key" << std::endl;

	//test if cannot find key
	if( p.find("randomkey", value))
		std::cout << "found randomkey : " << value << std::endl;
	else
		std::cout << "can't find randomkey" << std::endl;



	return 0;
}
