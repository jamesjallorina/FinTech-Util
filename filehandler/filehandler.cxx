#include "filehandler.h"

#include <iostream>
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


void filehandler::open(const char *file)
{
	filename = file;

}

void filehandler::load()
{


}

void filehandler::show()
{


}



int main(int argc, char **argv)
{


}