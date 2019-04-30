#ifndef FILE_TEMPLATE_CONTAINER_H
#define FILE_TEMPLATE_CONTAINER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include <string>
#include <string.h>
#include <stdlib.h>
#include <cctype>

//for sleep function call
#include <unistd.h>

#if 0
struct shcextbindb{
	std::string member;
	std::string name;
	std::string value;
};

template <class T>
class data{
public:
	const std::string &getMember(){
		return _data.member;
	}

	const std::string &getName(){
		return _data.name;
	}

	const std::string &getValue(){
		return _data.value;
	}

	const std::string &get_Value(){
		return _data._value;
	}

private:
	T _data;
};
#endif

//typedef std::pair<std::string, std::string> PAIR;
typedef std::unordered_map<std::string, std::string> umap;
typedef std::unordered_map<std::string, std::string>::const_iterator iter;

template <typename T, typename Iterator>
class fileTemplateContainer
{
public:
	fileTemplateContainer(const std::string filename);
	fileTemplateContainer(const fileTemplateContainer &file);
	~fileTemplateContainer();

	void parse(std::string tableName/*, std::string find*/);
	bool find(const std::string &key, std::string &value);
	void show();

private:
	fileTemplateContainer(); //we dont want a default ctor 
	
	std::string filename;
	std::ifstream filestream;
	//std::vector<PAIR> tcontainer;
	//std::multimap<std::string, name_value> mmap;
	//std::multimap<std::string, std::pair<std::string, std::string>> mmap;
	//std::vector<data<shcextbindb>> container;
	//std::unordered_map<std::string, std::string> param;
	T param;

	bool isAlpha(const std::string &input);
	bool isComment(const std::string &input);
};

#endif //FILE_TEMPLATE_CONTAINER_H
