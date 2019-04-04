#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdio.h>

using namespace std;
//#define DEBUG_BNC
//#define DEBUG_MC

#define MATCHIT

string split(const string &s, char delim); 
string getDate(const string &s); 
string getTrace(const string &s);

string split(const string &s, char delim) 
{
	stringstream ss(s.c_str());
	string item = "";
	while (std::getline(ss, item, delim)){} 
			
	return item;
}

string getDate(const string &s)
{
	int i = 0;
	stringstream ss(s.c_str());
	string item = "";
	while (std::getline(ss, item,' ')) {
	if(i == 1)
          break; 
	i++;
	}
	return item;
}
string getTrace(const string &s)
{
	size_t found = s.find('t');
	if(found != string::npos)	
		return ""; 
	else
		return s.substr(found,7);
}

typedef pair<string, string> Pair;

int main(int argc, char **argv)
{
	int total = 0;
	string line = "";
	string date = "";
	string trace = "";
	ifstream fp1(argv[1]);
	ifstream fp2(argv[2]);

	vector<Pair> bancnet;
	vector<Pair> mastercard;

	while(getline(fp1,line))
	{
		date = getDate(line);
		trace = getTrace(line);
		bancnet.push_back(make_pair(date, trace));
	}

	while(getline(fp2,line))
	{
		date = getDate(line);
		trace = getTrace(line);
		mastercard.push_back(make_pair(date, trace));
	}

#if defined(DEBUG_BNC)
	cout << "BANCNET" << endl;
	for(vector<Pair>::const_iterator p=bancnet.begin(); p!=bancnet.end(); p++){
		cout << p->first << " " << p->second << endl;	
	}
#endif	

#if defined(DEBUG_MC)
	cout << "MASTERCARD" << endl;
	for(vector<Pair>::const_iterator p=mastercard.begin(); p!=mastercard.end(); p++){
		cout << p->first << " " << p->second << endl;	
	}
#endif

#if defined(MATCHIT)
	cout << "start matching" << endl;
	for(vector<Pair>::const_iterator p=bancnet.begin(); p!=bancnet.end(); p++)
	{
	//	cout << p->first << " " << p->second << endl;
		for(vector<Pair>::const_iterator m=mastercard.begin(); m!=mastercard.end(); m++)
		{
	//		cout << m->first << " " << m->second << endl;
			if((p->first == m->first) && (p->second == m->second)){
				total++;
			}
			else
				continue; 
		}
	}
	cout << "total rejected transactions: " << total << endl;
#endif

	return 0;

}

