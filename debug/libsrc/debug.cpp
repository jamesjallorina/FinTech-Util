/*++
Author : James Marjun Jallorina
Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph

This program is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation, either version
3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
See the file 'LICENSE' for complete copying permission.

Module Name:
    debug.cpp
Abstract:
    This module serves as a debug utility in a file for logging purpose
--*/

#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <ofstream>
#include "debug.hpp"
#include "macros.hpp"

using namespace std;

#define DBG_LEN 2024
#define APP_NAME_LEN 50

static const char progname[APP_NAME_LEN + 1];
static const char const *FileName;

int app_name_init(char *app_name)
{
	if(progname[0]) 
		return (-1);
	else 
		strcpy(progname, app_name);
	return 0;
}

int debugOn(char *filename)
{
	static bool isInit = false;
	if(isInit) 
	{
		cout << "Filename already initialized\n";
		return (-1);
	}
	else
	{
		strcpy(FileName, filename);
		isInit = true;
	}
	return 0;
}

int printInfo(char *printmsg)
{
	char debug[DBG_LEN +1];
	ofstream fout(FileName);
	fout.open(FileName);

	if(isFileOk(fout) == false) return (-1);
	
	memset(debug, '\0', sizeof(debug));
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	
	
	sprintf("%02d:%02d:%04d %02d:%02d:%02d [   %s]: INFO: %s \n", 1 +local_time->tm_mon, local_time->tm_mday, 1970 + local_time->tm_year, 1 + local_time->tm_hour, 1 + local_time->tm_min, 1 + local_time->tm_sec, progname, printmsg);
	fout << debug;
	fout.cose();
	return 0;
}

	
	
	
int printDebug(char *printmsg)
{
	char debug[DBG_LEN +1];
	ofstream fout(FileName);
	fout.open(FileName);
	
	if(isFileOk(fout) == false) return (-1);
	
	memset(debug, '\0', sizeof(debug));
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	
	sprintf("%02d:%02d:%02d %02d:%02d:%02d [   %s]: DEBUG: %s \n", 1 +local_time->tm_mon, local_time->tm_mday, 1970 + local_time->tm_year, 1 + local_time->tm_hour, 1 + local_time->tm_min, 1 + local_time->tm_sec, progname, printmsg);
	fout << debug;
	fout.cose();
	return 0;
}

int printWarn(char *printmsg)
{
	char debug[DBG_LEN +1];
	ofstream fout(FileName);
	fout.open(FileName);
	
	if(isFileOk(fout) == false) return (-1);
	
	memset(debug, '\0', sizeof(debug));
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	
	sprintf("%02d:%02d:%02d %02d:%02d:%02d [   %s]: WARN: %s \n", 1 +local_time->tm_mon, local_time->tm_mday, 1970 + local_time->tm_year, 1 + local_time->tm_hour, 1 + local_time->tm_min, 1 + local_time->tm_sec, progname, printmsg);
	fout << debug;
	fout.cose();
	return 0;
}

int printFatal(char *printmsg)
{
	char debug[DBG_LEN +1];
	ofstream fout(FileName);
	fout.open(FileName);
	
	if(isFileOk(fout) == false) return (-1);
	
	memset(debug, '\0', sizeof(debug));
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	
	sprintf("%02d:%02d:%02d %02d:%02d:%02d [   %s]: FATAL: %s \n", 1 +local_time->tm_mon, local_time->tm_mday, 1970 + local_time->tm_year, 1 + local_time->tm_hour, 1 + local_time->tm_min, 1 + local_time->tm_sec, progname, printmsg);
	fout << debug;
	fout.cose();
	return 0;
}

int printError(char *printmsg)
{
	char debug[DBG_LEN +1];
	ofstream fout(FileName);
	fout.open(FileName);
	
	if(isFileOk(fout) == false) return (-1);
	
	memset(debug, '\0', sizeof(debug));
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	
	sprintf("%02d:%02d:%02d %02d:%02d:%02d [   %s]: ERROR: %s \n", 1 +local_time->tm_mon, local_time->tm_mday, 1970 + local_time->tm_year, 1 + local_time->tm_hour, 1 + local_time->tm_min, 1 + local_time->tm_sec, progname, printmsg);
	fout << debug;
	fout.cose();
	return 0;
}


