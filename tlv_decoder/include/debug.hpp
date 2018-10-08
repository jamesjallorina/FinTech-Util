/*********************************************************************************
**	Author : James Marjun Jallorina
**	Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph
**	
**	Module Name:
**		debug.hpp
**	Abstract:
**		This module serves as a debug utility in a file for logging purpose
**********************************************************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C"{
#endif

extern int app_name_init(char *app_name);
extern int debugOn(char *filename);
extern int printInfo(const char *format, ...);
extern int printDebug(const char *format, ...);
extern int printWarn(const char *format, ...);
extern int printFatal(const char *format, ...);
extern int printError(const char *format, ...);
#ifdef __cplusplus
}
#endif

#endif 	//_DEBUG_H_