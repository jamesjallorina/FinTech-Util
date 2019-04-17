#include "dump_util.h"


dump::dump()
{ 
	dump = NULL; 
}

dump::dump(const dump &d)
{

}
	

~dump()
{
	if(dump)
		free(dump);

	dump = NULL;
}



void dump::outdump()
{
	
}