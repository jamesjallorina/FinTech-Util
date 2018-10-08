/**************************************************************************
**	Author : James Marjun Jallorina
**	Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph
**
**
**	Module Name:
**    macros.hpp
**	Abstract:
**		This module defines function macros
***************************************************************************/

#ifndef _MACRO_H_
#define _MACRO_H_

#define init_char(str) (memset(str,'\0',sizeof(str)))
#define isFileOk(file)	(file.is_open() ? 1 : 0)
#define isInitializedDebug(a,b)	((a && b) ? 1 : 0)
	

#endif	//_MACRO_H_