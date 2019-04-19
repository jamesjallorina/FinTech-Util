#include "dump_util.h"


dump::dump()
{ 
	dump = NULL; 
}

dump::dump(const dump &d)
{
	dump = malloc(sizeof(char) * d.size);
	mempcy(dump, d.dump, d.size);
	size = d.size;
}
	

~dump()
{
	if(dump)
		free(dump);

	dump = NULL;
}

void dump::outdump(const char *dump, size_t size)
{
	if(this->dump)
		free(this->dump)
	else
	{
		this->dump = malloc(sizeof(char) * size)
		this->size = size;
	}

	outdump();
}

void dump::outdump()
{
	size_t line = 0;

	for(int i=0; i < size; i=+10)
		//printf("%-08s | %-20s | %-.10s ", );
}