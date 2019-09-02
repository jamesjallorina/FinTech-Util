#ifndef FILE_TEMPLATE_CONTAINER_H
#define FILE_TEMPLATE_CONTAINER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#include <string>
#include <string.h>
#include <stdlib.h>
#include <cctype>

//for sleep function call
#include <unistd.h>

#define COMMENT '#'
#define UNDERSCORE '_'
//#define SLEEP
//#define DEBUG



//typedef std::pair<std::string, std::string> PAIR;
//typedef std::map<std::string, std::string> map;						//create a unordered_map stl container
//typedef std::map<std::string, std::string>::const_iterator iter;		//create a unordered_map stl container iterator


/*
*	class description: This class parses data from template.dat which contains a value needed for generating sql
*	based on routing configuration.
*	
*	This is a templated container since we can use any stl container we want and store the values accordingly. 
*/
template <typename T = std::string>
class fileTemplateContainer
{
public:
	fileTemplateContainer(); 
	fileTemplateContainer(const std::string &table_filename, const std::string &param_filename);
	fileTemplateContainer(const fileTemplateContainer &fcontainer);
	~fileTemplateContainer();

	bool findInTableContainer(const std::string &key, std::string &value);
	bool findInParamContainer(const std::string &key, std::string &value);

	bool parse_and_insert(const std::string &tableName, const std::string &paramName);

	std::vector<std::pair<T, T> > &copy_tableContainer() const
	{
		return tableContainer; 
	}

	std::vector<std::pair<T, T> > &copy_paramContainer() const
	{
		return paramContainer;
	}	

	void display_values() const;

private:
	enum eMEMBER_NAME
	{
		UNINCLUDE = 0,
		INCLUDE
	};
	std::string table_filename;
	std::string param_filename;
	std::string current_filename;

	std::ifstream filestream;

	std::vector<std::pair<T, T> > tableContainer;
	std::vector<std::pair<T, T> > paramContainer;


	bool isAlpha(const std::string &input) const;
	bool isComment(const std::string &input) const;

	bool parse(const std::string &filename, 
		const std::string &tableName,
		std::vector<std::pair<T, T> > &container,
		eMEMBER_NAME member_name = UNINCLUDE);
	void show_contents_helper(const std::vector<std::pair<T, T> > &container) const ;
	void setfile(const std::string &table_filename, const std::string &param_filename);
	bool openFile(const std::string &filename);
	void closeFile();
};

template <typename T>
fileTemplateContainer<T>::fileTemplateContainer()
{ 
	std::cout << " default constructor fileTemplateContainer \n";
	table_filename = "files/table_template.dat";
	param_filename = "files/param_template.dat";	
	current_filename = "";
	std::cout << "table path [" << u_constructfile(table_filename.c_str() << "]\n";
	std::cout << "param path [" << u_constructfile(param_filename.c_str() << "]\n";
}


template <typename T>
fileTemplateContainer<T>::fileTemplateContainer(const std::string &table_filename, const std::string &param_filename)
{
	this->table_filename = table_filename;
	this->param_filename = param_filename;
	current_filename = "";
}

template <typename T>
fileTemplateContainer<T>::fileTemplateContainer(const fileTemplateContainer &fcontainer)
{
	std::cout << "copy constructor fileTemplateContainer \n";
	table_filename = fcontainer.table_filename;
	param_filename = fcontainer.param_filename;
	current_filename = fcontainer.current_filename;
	tableContainer = fcontainer.tableContainer;
	paramContainer = fcontainer.paramContainer;
}

template <typename T>
fileTemplateContainer<T>::~fileTemplateContainer()
{
	std::cout << "destructor fileTemplateContainer \n";
}

template <typename T>
void fileTemplateContainer<T>::setfile(const std::string &table_filename, const std::string &param_filename)
{
	if (table_filename.empty() || param_filename.empty())
		std::cout << "not a valid filename \n";
	else
	{
		std::cout << "filename set to table_filename[" << table_filename << "] and param_filename[" << param_filename << "]\n";
		this->table_filename = table_filename;
		this->param_filename = param_filename;
	}
	return;
}


template <typename T>
bool fileTemplateContainer<T>::openFile(const std::string &filename)
{
	if (filename.empty())
	{
		std::cout << "filename is not valid \n";
		return false;
	}

	current_filename = filename;
	filestream.open(u_constructfile(current_filename.c_str()));

	if (filestream.is_open())
	{
		std::cout << "file is okay to read: [" << current_filename.c_str() << "]\n";
		return true;
	}
	else
		std::cout << "failed to open file: [" << current_filename.c_str() << "]\n";

	return false;
}


template <typename T>
void fileTemplateContainer<T>::closeFile()
{
	if (filestream.is_open())
	{
		std::cout << "closing file: [" << current_filename.c_str() << "]\n";
		filestream.close();
	}
	else
		std::cout << "filename already closed: [" << current_filename.c_str() << "]\n";

	return;
}


template <typename T>
bool fileTemplateContainer<T>::parse_and_insert(const std::string &tableName, const std::string &paramName)
{
	parse(table_filename, tableName, tableContainer);
	parse(param_filename, paramName, paramContainer);
	return true;
}

template <typename T>
bool fileTemplateContainer<T>::parse(const std::string &filename, 
			const std::string &tableName, 
			std::vector<std::pair<T, T> > &container,
			eMEMBER_NAME member_name) const
{
	std::string templateMember = "";
	std::string templateName = "";
	std::string templateVal = "";
	std::string token = "";
	std::string line = "";
	bool isStart = false;
	size_t found = 0;
	size_t pos = 0;


	std::cout << "FILENAME[" << filename.c_str() << "]\n";
	std::cout << "TABLENAME[" << tableName.c_str() << "]\n";
	std::cout << "searching for tableName [" << tableName.c_str() << "]\n";
	
	if (!openFile(filename))
		return false;

	while (std::getline(filestream, line))
	{

#if defined(DEBUG)
		std::cout << "current line [" << line.c_str() << "]\n";
#endif
		if (	!isAlpha(line) || isComment(line)	)
		{
#if defined(DEBUG)
			std::cout << "is a comment or not an alphanumeric and space \n";
#endif
			continue;
		}

		//file handling should start with table name and start
		/*
		*	search for table name and start hint
		*/
		if( !isStart)
		{	
			if (line.find(tableName) != std::string::npos && line.find("start") != std::string::npos && isStart == false)
			{
				std::cout << "found tableName : [" << tableName.c_str() << "] start \n";
				isStart = true;
				continue; 	//continue to the next line
			}
		}


		if (line.find(tableName) != std::string::npos && line.find("end") != std::string::npos)
		{
#if defined(DEBUG)
			std::cout << "found tableName : [" << tableName.c_str() << "] end\n";
			std::cout << "stop parsing \n";
#endif
			break;
		}
#if defined(DEBUG)
		std::cout << "looping through file \n";
#endif
		pos = line.find(" ");

		if (pos != std::string::npos)
			token = line.substr(0, pos);


		line.erase(0, pos + 1);
#if defined(DEBUG)
		std::cout << "first token : [" << token.c_str() << "]\n";
#endif
		templateMember = token;

		if ((pos = line.find(" ")) != std::string::npos)
			token = line.substr(0, pos);

		//line.erase(0, pos + 1);	//erase + 1 since it is only space
#if defined(DEBUG)
		std::cout << "second token : [" <<  token.c_str()<< "]\n";
#endif

		templateName = token;
		token = line.erase(0, pos + 1);	//erase + 1 since it is only space
#if defined(DEBUG)
		std::cout << "third token : [" << token.c_str() << "]\n";
#endif
		templateVal = token;
#if defined(SLEEP)
			sleep(1);
#endif
#if defined(DEBUG)
		std::cout << "templateMember : [" << templateMember.c_str() << "]\n";
		std::cout << "templateName : [" << templateName.c_str() << "]\n";
		std::cout << "templateVal : [" << templateVal.c_str() << "]\n";
#endif
		//container.insert(std::make_pair(templateMember + templateName, templateVal));
		if(member_name == UNINCLUDE)
		{		
			std::cout << "Inserting templateName [" << templateName.c_str() << "] templateVal [" << templateVal.c_str() << "]\n";
			container.push_back(std::make_pair<T, T>(templateName, templateVal));
		}
		else
		{
		std::cout << "Inserting templateMember [" << templateMember.c_str() << "] templateName [" << templateName.c_str() << "] templateVal [" << templateVal.c_str() << "]\n";
		container.push_back(std::make_pair<T, T>(templateMember + templateName, templateVal));
		}
#if defined(SLEEP)
			sleep(1);
#endif
	}
	closeFile();
	return true;
}

template <typename T>
bool fileTemplateContainer<T>::findInTableContainer(const std::string &key, std::string &value)
{
	std::vector<std::pair<T, T> >::iterator itBegin = tableContainer.begin();
	std::vector<std::pair<T, T> >::iterator itEnd = tableContainer.end();
	std::vector<std::pair<T, T> >::iterator res;

	std::cout << "finding [" << key.c_str() << "] in tableContainer\n";

	res = std::find(itBegin, itEnd, key);

	if (res != itEnd)
	{
		value = *res;
		return true;
	}
	return false;
}

template <typename T>
bool fileTemplateContainer<T>::findInParamContainer(const std::string &key, std::string &value)
{
	std::vector<std::pair<T, T> >::iterator itBegin = paramContainer.begin();
	std::vector<std::pair<T, T> >::iterator itEnd = paramContainer.end();
	std::vector<std::pair<T, T> >::iterator res;

	std::cout << "finding [" << key.c_str() << "] in paramContainer\n";

	res = std::find(itBegin, itEnd, key);

	if (res != itEnd)
	{
		value = *res;
		return true;
	}
	return false;
}

template <typename T>
void fileTemplateContainer<T>::show_contents_helper(const std::vector<std::pair<T, T> > &container) const
{
	std::vector<std::pair<T, T> >::const_iterator it;
	std::cout << "container size [" << container.size() << "]\n";
	
	for (it = container.begin(); it != container.end(); ++it)
		std::cout << "FIRST_VALUE[" << it->first.c_str() << "] SECOND_VALUE[" << it->second.c_str() << "]\n";

	return;
}

template <typename T>
void fileTemplateContainer<T>::display_values() const
{
	std::cout << "tableContainer contains \n";
	show_contents_helper(tableContainer);
	std::cout << "paramContainer contains \n";
	show_contents_helper(paramContainer);
	return;
}


template <typename T>
bool fileTemplateContainer<T>::isAlpha(const std::string &input) const
{
	std::string::const_iterator it;

	for (it = input.begin(); it != input.end(); ++it)
	{
		//std::cout << "it : " << *it << std::endl;
		if (!isalpha(*it) && !isdigit(*it) && !isspace(*it) && (*it) != UNDERSCORE)
		{
#if defined (DEBUG)
			std::cout << "not an alphanumeric and space \n";
#endif
			return false;
		}
	}
	return true;
}

template <typename T>
bool fileTemplateContainer<T>::isComment(const std::string &input) const
{
	std::string::const_iterator it;
	for (it = input.begin(); it != input.end(); ++it)
	{
		if (*it == COMMENT)
			return true;
	}

	return false;
}

#endif //FILE_TEMPLATE_CONTAINER_H
