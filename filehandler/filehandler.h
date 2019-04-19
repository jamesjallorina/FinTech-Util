#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


typedef pair<string,string> PAIR;

class filehandler
{
public:
	filehandler();
	filehandler(const filehandler &file);
	~filehandler();

	void open();
	void load();
	void show();

private:
	std::string filename;
	std::ifstream 
	vector<PAIR> tcontainer;
}

#endif //FILE_HANDLER_H