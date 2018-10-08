/****************************************************************************
**	Author : James Marjun Jallorina
**	Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph
**
**	Module Name:
**		TlvDecoder.cpp
**	Abstract:
**		This module decodes the TLV Chip Data Tag
*****************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h> 
#include "TlvDecode.hpp"
#include "macro.hpp"
#include "emvdef.hpp"
#include "TlvHelper.hpp"
#include "debug.hpp"

using namespace std;

/** Constructor and Destructor **/

TlvDecode::TlvDecode() 
{ 
	emvptr = new emvbuf; 
} //end of constructor

TlvDecode::~TlvDecode() 
{  
	if(emvptr != NULL)
	{
		printInfo("free *emvptr\n");
		delete emvptr;
		emvptr = NULL;
	}
} //end of destructor

void TlvDecode::DecodeChipDataTag(const char* EmvTags)
{
 	char acChipData[DBG_LEN];
 	init_char(acChipData); 
 	char acTag[5];
 	init_char(acTag);
 	char acTagLength[3];
 	init_char(acTagLength);
	char acTagData[256];
 	init_char(acTagData);
	
	if(EmvTags[0] == '\0')
		return;
	
 	sprintf(acChipData,'%s',EmvTags); //load the value to character array
 
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
 		//cout << "TAG:: "<< acTag << "::TAG LENGTH:: " <<  iDataTagLen << "::TAG VALUE::" << acTagData << ENDL;
		printDebug("TAG: [%s] TAGLEN: [%d] TAGVALUE: [%s] \n", acTag, iDataTagLen, acTagData);
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
	return;
}
void TlvDecode::DecodeChipDataTag(const string sEmvTags)
{
	const char *emvTags = sEmvTags.c_str();
	
	if(emvTags[0] != '\0')
		DecodeChipDataTag(emvTags);
	
	return;
}

int TlvDecode::emvdump(struct emvbuf *emvptr)
{
	if(!emvptr)
	{
		printDebug("emvptr is null \n");
		return (-1);
	}
	
	printDebug("EMV DUMP START \n");
	printDebug("Issuer Script Template 1 : [%s] \n",			this->emvptr->issuer_script_template_1);
	printDebug("Issuer Script Template 2 : [%s] \n", 			this->emvptr->issuer_script_template_2);
	printDebug("Application Interchange Profile : [%s] \n",		this->emvptr->app_interchange_profile);
	printDebug("Dedicated File Name : [%s] \n",					this->emvptr->dedicated_file_name);
	printDebug("Issuer Authentication Data : [%s] \n",			this->emvptr->issuer_authentication_data);
	printDebug("Terminal Verification Result : [%s] \n",		this->emvptr->terminal_verification_result);
	printDebug("Transaction Date : [%s] \n",					this->emvptr->transaction_date); 
	printDebug("Transaction Type : [%s] \n",					this->emvptr->transaction_type);
	printDebug("Transaction Currency Code : [%s] \n",			this->emvptr->transaction_currency_code); 
	printDebug("Amount Authorized : [%s] \n",					this->emvptr->amount_authorized);
	printDebug("Amount Other : [%s] \n",						this->emvptr->amount_other);
	printDebug("Application Identifier : [%s] \n",				this->emvptr->application_identifier );
	printDebug("Application Usage Control : [%s] \n",			this->emvptr->application_usage_control );
	printDebug("Terminal Application Version Number : [%s] \n",	this->emvptr->terminal_application_version_number );
	printDebug("Issuer Application Data : [%s] \n",				this->emvptr->issuer_application_data);
	printDebug("Terminal Country Code : [%s] \n",				this->emvptr->terminal_country_code );
	printDebug("Interface Device Serial Number : [%s] \n",		this->emvptr->interface_device_serial_number );
	printDebug("Application Cryptogram : [%s] \n",				this->emvptr->application_crpytogram );
	printDebug("Cryptogram Information Data : [%s] \n",			this->emvptr->cryptogram_information_data);
	printDebug("Terminal Capability : [%s] \n"					this->emvptr->terminal_capability );
	printDebug("Cardholder Verification Method Result : [%s] \n",this->emvptr->cardholder_verfication_method_result );
	printDebug("Terminal Type : [%s] \n",						this->emvptr->terminal_type );
	printDebug("Application Transaction Counter : [%s] \n",		this->emvptr->application_transaction_counter);
	printDebug("Unpredictable Number : [%s] \n",				this->emvptr->unpredictable_number );
	printDebug("Transaction Sequence Counter : [%s] \n",		this->emvptr->transaction_sequence_counter );
	printDebug("Transaction Category Code : [%s] \n",			this->emvptr->transaction_category_code );
	printDebug("Issuer Script Result : [%s] \n",				this->emvptr->issuer_script_result );
	printDebug("Card Product Identification : [%s] \n",			this->emvptr->card_product_identification );
	printDebug("Issuer authorization Code - Electronic Cash : [%s] \n", this->emvptr->issuer_authorization_code);
	printDebug("EMV DUMP END \n");
	return 0;
}