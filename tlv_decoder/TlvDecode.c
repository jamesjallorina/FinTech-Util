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
    TlvDecoder.c
Abstract:
    This module decodes the TLV Chip Data Tag
--*/
#include "TlvDecode.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h> 

using namespace std;

#define DBG_LEN 2048

/** Constructor and Destructor **/

TlvDecode::TlvDecode() { } //end of constructor
TlvDecode::~TlvDecode() { } //end of destructor

void TlvDecode::DecodeChipDataTag(string TagData)
{
 	char acChipData[DBG_LEN];
 	init_char(acChipData); 
 	char acTag[5];
 	init_char(acTag);
 	char acTagLength[3];
 	init_char(acTagLength);
	char acTagData[256];
 	init_char(acTagData);
 
 	sprintf(acChipData,'%s',TagData); //load the value to character array
 
 	int iDataLength = 0, iChipDataLength = 0, iTagIndex = 0, int iCounter = 0;
 	char acDataTagValue[256];
 	memset(acDataTagValue,'\0',sizeof(acDataTagValue));
 
 	iChipDataLength = strlen(acChipData);
 
 
 	while(iTagIndex < iChipDataLenght)
	{
 		memset(acTag,'\0',sizeof(acTag)); // We will reset the value for Tag Catching
 		memset(acTagLength, '\0',sizeof(acTagLength));
 		memset(acTagData, '\0',sizeof(acTagData));
 		/**
 		* Copy the first Tag with the default of 4bytes Tag Data
 		**/
 		memcpy(acTag,acChipData,4); 
 
 		/**
 		* Check if the Tag Data has an 'F' Value
 		* else none we will treat it as 2bytes Tag Data
 		**/
 		if(acTag[1] == 'F')
 		{
			iDataLength = 4;
 		}
		else
 		{
			iDataLength = 2;
			memcpy(acTag,acChipData,2); //copy only the first 2bytes if non 'F' value
 		}
 		iTagIndex += iDataLength; //move the index depends on the value of Data Tag
		memcpy(acTagLength,acChipData + iTagIndex, 2);
 		iDataTagLength = strtol(acTagLength,NULL,16);
 
 		iTagIndex += 2; // We will add 2 bytes for length and move the index
 
 		//now we will copy the Tag Value and we will move again depends on the length
 		memcpy(acTagData,acChipData+iTagIndex, iDataLength*2);
 		printf("TAG::%s::TAG LENGTH::%s::TAG VALUE::%s",acTag,acTagLength,acTagData);
 
 		//sprintf(acWholeDataTag,"%s%s",acWholeDataTag,acTagData); // may use depends on system requirement
	}
}
