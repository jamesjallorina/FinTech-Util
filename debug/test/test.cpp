#includ <stdio.h>
#include "debug.hpp"

int main(int argc, char **argv)
{
  char appname[50+1];
  char filename[100+1];
  
  memset(appname, 0x00, sizeof(appname));
  memset(filename, 0x00, sizeof(filename));
  
  strcpy(appname, *argv);
  srcpy(filename, "test.debug");
  
  app_name_init(appname);
  debugOn(filename);
  
  printDebug("check/test debug logging\n");
  return 0;
}
