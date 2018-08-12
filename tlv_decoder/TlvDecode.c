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
    TlvDecoder.cpp
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

TlvDecode::TlvDecode() 
{ 
	emvptr = new emvbuf; 
} //end of constructor

TlvDecode::~TlvDecode() 
{  
	if(emvptr)
	{
		cout << "delete emvptr\n";
		delete emvptr;
	}
} //end of destructor

void TlvDecode::DecodeChipDataTag(string sTagData)
{
 	char acChipData[DBG_LEN];
 	init_char(acChipData); 
 	char acTag[5];
 	init_char(acTag);
 	char acTagLength[3];
 	init_char(acTagLength);
	char acTagData[256];
 	init_char(acTagData);
	
 	sprintf(acChipData,'%s',sTagData); //load the value to character array
 
 	int iDataLen = 0, iChipDataLen = 0, iTagIndex = 0, int iCounter = 0, iDataTagLen = 0;
	long int  iTag = 0;
 	char acDataTagValue[256];
 	memset(acDataTagValue,'\0',sizeof(acDataTagValue));
 
 	iChipDataLen = strlen(acChipData);
 
 
 	while(iTagIndex < iChipDataLen)
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
			iDataLen = 4;
 		}
		else
 		{
			iDataLen = 2;
			memcpy(acTag,acChipData,2); //copy only the first 2bytes if non 'F' value
 		}
 		iTagIndex += iDataLen; //move the index depends on the value of Data Tag
		memcpy(acTagLength,acChipData + iTagIndex, 2);
 		iDataTagLen = strtol(acTagLength,NULL,16);
 
 		iTagIndex += 2; // We will add 2 bytes for length and move the index
 
 		//now we will copy the Tag Value and we will move again depends on the length
 		memcpy(acTagData,acChipData+iTagIndex, iDataLen*2);
 		cout << "TAG:: "<< acTag << "::TAG LENGTH:: " <<  iDataTagLen << "::TAG VALUE::" << acTagData << ENDL;
		iTag = strtol(acTag, NULL, 16);
		switch(iTag)
		{
			case emv_tag_71:
				memcpy(emvptr->issuer_script_template_1, acTagData, iDataTagLen);
				break;
			case emv_tag_72:
				memcpy(emvptr->issuer_script_template_2, acTagData, iDataTagLen);
				break;
			case emv_tag_82:
				memcpy(emvptr->app_interchange_profile, acTagData, iDataTagLen);
				break;
			case emv_tag_84: 
				memcpy(emvptr->dedicated_file_name, acTagData, iDataTagLen);
				break;
			case emv_tag_91: 	
				memcpy(emvptr->issuer_authentication_data, acTagData, iDataTagLen);
				break;
			case emv_tag_95: 	
				memcpy(emvptr->terminal_verification_result, acTagData, iDataTagLen);
				break;
			case emv_tag_9A:
				memcpy(emvptr->transaction_date, acTagData, iDataTagLen);
				break;
			case emv_tag_9C:	
				memcpy(emvptr->transaction_type, acTagData, iDataTagLen);
				break;
			case emv_tag_5F2A:
				memcpy(emvptr->transaction_currency_code, acTagData, iDataTagLen);
				break;
			case emv_tag_9F02:
				memcpy(emvptr->amount_authorized, acTagData, iDataTagLen);
				break;
			case emv_tag_9F03:
				memcpy(emvptr->amount_other, acTagData, iDataTagLen);
				break;
			case emv_tag_9F06:
				memcpy(emvptr->application_identifier, acTagData, iDataTagLen);
				break;
			case emv_tag_9F07:
				memcpy(emvptr->application_usage_control, acTagData, iDataTagLen);
				break;
			case emv_tag_9F09:
				memcpy(emvptr->terminal_application_version_number, acTagData, iDataTagLen);
				break;
			case emv_tag_9F10:
				memcpy(emvptr->issuer_application_data, acTagData, iDataTagLen);
				break;
			case emv_tag_9F1A:
				memcpy(emvptr->terminal_country_code, acTagData, iDataTagLen);
				break;
			case emv_tag_9F1E:
				memcpy(emvptr->interface_device_serial_number, acTagData, iDataTagLen);
				break;
			case emv_tag_9F26:
				memcpy(emvptr->application_crpytogram, acTagData, iDataTagLen);
				break;
			case emv_tag_9F27:
				memcpy(emvptr->cryptogram_information_data, acTagData, iDataTagLen);
				break;
			case emv_tag_9F33:
				memcpy(emvptr->terminal_capability, acTagData, iDataTagLen);
				break;
			case emv_tag_9F34:
				memcpy(emvptr->cardholder_verfication_method_result, acTagData, iDataTagLen);
				break;
			case emv_tag_9F35:
				memcpy(emvptr->terminal_type, acTagData, iDataTagLen);
				break;
			case emv_tag_9F36:
				memcpy(emvptr->application_transaction_counter, acTagData, iDataTagLen);
				break;
			case emv_tag_9F37:
				memcpy(emvptr->unpredictable_number, acTagData, iDataTagLen);
				break;
			case emv_tag_9F41:
				memcpy(emvptr->transaction_sequence_counter, acTagData, iDataTagLen);
				break;
			case emv_tag_9F53:
				memcpy(emvptr->transaction_category_code, acTagData, iDataTagLen);
				break;
			case emv_tag_9F5B:
				memcpy(emvptr->issuer_script_result, acTagData, iDataTagLen);
				break;
			case emv_tag_9F63:
				memcpy(emvptr->card_product_identification, acTagData, iDataTagLen);
				break;
			case emv_tag_9F74:
				memcpy(emvptr->issuer_authorization_code, acTagData, iDataTagLen);
				break;
			default:
				break;
		}
 		//sprintf(acWholeDataTag,"%s%s",acWholeDataTag,acTagData); // may use depends on system requirement
	}
}

int TlvDecode::emvdump(struct emvbuf *emvptr)
{
	this->emvptr = emvptr;
	cout << "EMV DUMP START \n";
	cout << "Issuer Script Template 1 : ["<<this->emvptr->issuer_script_template_1 << "] \n";							
	cout << "Issuer Script Template 2 : ["	<<	this->emvptr->issuer_script_template_2 << "] \n";
	cout << "Application Interchange Profile : ["	<<	this->emvptr->app_interchange_profile << "] \n";
	cout << "Dedicated File Name : ["	<<	this->emvptr->dedicated_file_name << "] \n";
	cout << "Issuer Authentication Data : ["	<<	this->emvptr->issuer_authentication_data << "] \n";
	cout << "Terminal Verification Result : ["	<<	this->emvptr->terminal_verification_result << "] \n";
	cout << "Transaction Date : ["	<<	this->emvptr->transaction_date << "] \n";
	cout << "Transaction Type : ["	<<	this->emvptr->transaction_type << "] \n";
	cout << "Transaction Currency Code : ["	<<	this->emvptr->transaction_currency_code << "] \n";
	cout << "Amount Authorized : ["	<<	this->emvptr->amount_authorized << "] \n";
	cout << "Amount Other : ["	<<	this->emvptr->amount_other << "] \n";
	cout << "Application Identifier : ["	<< this->emvptr->application_identifier << "] \n";
	cout << "Application Usage Control : ["	<<	this->emvptr->application_usage_control << "] \n";
	cout << "Terminal Application Version Number : ["	<< this->emvptr->terminal_application_version_number << "] \n";
	cout << "Issuer Application Data : ["	<<	this->emvptr->issuer_application_data << "] \n";
	cout << "Terminal Country Code : ["	<<	this->emvptr->terminal_country_code << "] \n";
	cout << "Interface Device Serial Number : ["	<<	this->emvptr->interface_device_serial_number << "] \n";
	cout << "Application Cryptogram : ["	<<	this->emvptr->application_crpytogram << "] \n";
	cout << "Cryptogram Information Data : ["	<<	this->emvptr->cryptogram_information_data << "] \n";
	cout << "Terminal Capability : ["	<<	this->emvptr->terminal_capability << "] \n";
	cout << "Cardholder Verification Method Result : ["	<<	this->emvptr->cardholder_verfication_method_result << "] \n";
	cout << "Terminal Type : ["	<<	this->emvptr->terminal_type << "] \n";
	cout << "Application Transaction Counter : ["	<<	this->emvptr->application_transaction_counter << "] \n";
	cout << "Unpredictable Number : ["	<<	this->emvptr->unpredictable_number << "] \n";
	cout << "Transaction Sequence Counter : ["	<<	this->emvptr->transaction_sequence_counter << "] \n";
	cout << "Transaction Category Code : ["	<<	this->emvptr->transaction_category_code << "] \n";
	cout << "Issuer Script Result : ["	<<	this->emvptr->issuer_script_result << "] \n";
	cout << "Card Product Identification : ["	<<	this->emvptr->card_product_identification << "] \n";
	cout << "Issuer authorization Code - Electronic Cash : [" << this->emvptr->issuer_authorization_code << "] \n";
	cout << "EMV DUMP END \n";
	return 0;
}