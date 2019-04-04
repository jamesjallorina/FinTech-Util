#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>


#define DBG_LEN 2048
#define init_char(str) (memset(str,'\0',sizeof(str)))

using namespace std;

const long int emv_tag_71 = 113; //tag 71
const long int emv_tag_72 = 114; //tag 72
const long int emv_tag_82 = 130; //tag 82
const long int emv_tag_84 = 132; //tag 84
const long int emv_tag_91 = 145; //tag 91
const long int emv_tag_95 = 149; //tag 95
const long int emv_tag_9A = 154; //tag 9A
const long int emv_tag_9C = 156; //tag 9C
const long int emv_tag_5F2A = 24362; //tag 5F2A
const long int emv_tag_9F02 = 40706; //tag 9F02
const long int emv_tag_9F03 = 40707; //tag 9F03
const long int emv_tag_9F06 = 40710; //tag 9F06
const long int emv_tag_9F07 = 40711; //tag 9F07
const long int emv_tag_9F09 = 40713; //tag 9F09
const long int emv_tag_9F10 = 40720; //tag 9F10
const long int emv_tag_9F1A = 40730; //tag 9F1A
const long int emv_tag_9F1E = 40734; //tag 9F1E
const long int emv_tag_9F26 = 40742; //tag 9F26
const long int emv_tag_9F27 = 40743; //tag 9F27
const long int emv_tag_9F33 = 40755; //tag 9F33
const long int emv_tag_9F34 = 40756; //tag 9F34
const long int emv_tag_9F35 = 40757; //tag 9F35
const long int emv_tag_9F36 = 40758; //tag 9F36
const long int emv_tag_9F37 = 40759; //tag 9F37
const long int emv_tag_9F41 = 40769; //tag 9F41
const long int emv_tag_9F53 = 40787; //tag 9F53
const long int emv_tag_9F5B = 40795; //tag 9F5B
const long int emv_tag_9F63 = 40803; //tag 9F63
const long int emv_tag_9F74 = 40820; //tag 9F74


struct emv 
{
char issuer_script_template_1[128+1];
char issuer_script_template_2[128+1];
char app_interchange_profile[4+1];
char dedicated_file_name[32+1];
char issuer_authentication_data[32+1];
char terminal_verification_result[10+1];
char transaction_date[6+1];
char transaction_type[2+1];
char transaction_currency_code[4+1];
char amount_authorized[12+1];
char amount_other[12+1];
char application_identifier[32+1];
char application_usage_control[4+1];
char terminal_application_version_number[4+1];
char issuer_application_data[64+1];
char terminal_country_code[4+1];
char interface_device_serial_number[16+1];
char application_crpytogram[16+1];
char cryptogram_information_data[2+1];
char terminal_capability[6+1];
char cardholder_verfication_method_result[6+1];
char terminal_type[2+1];
char application_transaction_counter[4+1];
char unpredictable_number[8+1];
char transaction_sequence_counter[8+1];
char transaction_category_code[2+1];
char issuer_script_result[50+1];
char card_product_identification[32+1];
char issuer_authorization_code[12+1];
};


int emvdump(struct emv *);
struct emv *DecodeChipDataTag(const char*);

struct emv *DecodeChipDataTag(const char* emvtags)
{
        char acChipData[DBG_LEN];
        init_char(acChipData);
        char acTag[5];
        init_char(acTag);
        char acTagLength[3];
        init_char(acTagLength);
        char acTagData[256];
        init_char(acTagData);

        if(emvtags[0] == '\0')
        return NULL;

        static struct emv emvbuf;
        memset(&emvbuf, 0, sizeof(emvbuf));

        struct emv *emvptr = &emvbuf;

        sprintf(acChipData,"%s",emvtags); //load the value to character array

        int iDataLen = 0, iChipDataLen = 0, iTagIndex = 0, iDataTagLen = 0;     //int iCounter = 0
        long int iTag = 0;
        char acDataTagValue[256];
        memset(acDataTagValue,'\0',sizeof(acDataTagValue));

        iChipDataLen = strlen(acChipData);


        while(iTagIndex < iChipDataLen)
        {
        memset(acTag,'\0',sizeof(acTag)); // We will reset the value for Tag Catching
        memset(acTagLength, '\0',sizeof(acTagLength));
        memset(acTagData, '\0',sizeof(acTagData));
       
	memcpy(acTag,acChipData+iTagIndex,2);

        /**
        * Check if the Tag Data has an 'F' Value
        * else none we will treat it as 2bytes Tag Data
        **/
        if(acTag[1] == 'F')
			iDataLen = 4;
        else
			iDataLen = 2;

	memcpy(acTag,acChipData+iTagIndex, iDataLen); 
		
        iTagIndex += iDataLen; //move the index depends on the value of Data Tag
        memcpy(acTagLength,acChipData + iTagIndex, 2);
	iTagIndex += 2; // We will add 2 bytes for length and move the index
        iDataTagLen = strtol(acTagLength,NULL,16);
	iDataTagLen *= 2;	//multiply by 2

        //now we will copy the Tag Value and we will move again depends on the length
        memcpy(acTagData,acChipData+iTagIndex, iDataTagLen);
	iTagIndex += iDataTagLen;	//move the index
	iTag = strtol(acTag, NULL, 16);
	//printf("TAG: [%s] TAGLEN: [%d] TAGVALUE: [%s] \n", acTag, iDataTagLen/2, acTagData);
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
        emvdump(emvptr);

        return emvptr;
}

int emvdump(struct emv *emvptr)
{
        if(!emvptr)
        {
        printf("emvptr is null \n");
        return (-1);
        }

        printf("EMV DUMP START \n");
        printf("%-50s:[%s] \n", "Issuer Script Template 1", emvptr->issuer_script_template_1);
        printf("%-50s:[%s] \n", "Issuer Script Template 2",emvptr->issuer_script_template_2);
        printf("%-50s:[%s] \n", "Application Interchange Profile",emvptr->app_interchange_profile);
        printf("%-50s:[%s] \n", "Dedicated File Name",emvptr->dedicated_file_name);
        printf("%-50s:[%s] \n","Issuer Authentication Data" ,emvptr->issuer_authentication_data);
        printf("%-50s:[%s] \n", "Terminal Verification Result",emvptr->terminal_verification_result);
        printf("%-50s:[%s] \n", "Transaction Date",emvptr->transaction_date);
        printf("%-50s:[%s] \n", "Transaction Type",emvptr->transaction_type);
        printf("%-50s:[%s] \n", "Transaction Currency Code",emvptr->transaction_currency_code);
        printf("%-50s:[%s] \n", "Amount Authorized",emvptr->amount_authorized);
        printf("%-50s:[%s] \n", "Amount Other",emvptr->amount_other);
        printf("%-50s:[%s] \n", "Application Identifier",emvptr->application_identifier );
        printf("%-50s:[%s] \n", "Application Usage Control",emvptr->application_usage_control );
        printf("%-50s:[%s] \n", "Terminal Application Version Number",emvptr->terminal_application_version_number );
        printf("%-50s:[%s] \n", "Issuer Application Data",emvptr->issuer_application_data);
        printf("%-50s:[%s] \n", "Terminal Country Code",emvptr->terminal_country_code );
        printf("%-50s:[%s] \n", "Interface Device Serial Number",emvptr->interface_device_serial_number );
        printf("%-50s:[%s] \n", "Application Cryptogram",emvptr->application_crpytogram );
        printf("%-50s:[%s] \n", "Cryptogram Information Data",emvptr->cryptogram_information_data);
        printf("%-50s:[%s] \n", "Terminal Capability",emvptr->terminal_capability );
        printf("%-50s:[%s] \n", "Cardholder Verification Method Result",emvptr->cardholder_verfication_method_result );
        printf("%-50s:[%s] \n", "Terminal Type",emvptr->terminal_type );
        printf("%-50s:[%s] \n", "Application Transaction Counter",emvptr->application_transaction_counter);
        printf("%-50s:[%s] \n", "Unpredictable Number",emvptr->unpredictable_number );
        printf("%-50s:[%s] \n", "Transaction Sequence Counter",emvptr->transaction_sequence_counter );
        printf("%-50s:[%s] \n", "Transaction Category Code",emvptr->transaction_category_code );
        printf("%-50s:[%s] \n", "Issuer Script Result",emvptr->issuer_script_result );
        printf("%-50s:[%s] \n", "Card Product Identification",emvptr->card_product_identification );
        printf("%-50s:[%s] \n", "Issuer authorization Code - Electronic Cash",emvptr->issuer_authorization_code);
        printf("EMV DUMP END \n");
        return 0;
}

int main(int argc, char **argv)
{
	if(argc < 2){
		cout << "usage: " << endl;
		cout << "tlvdecoder [emvtags]" << endl;
		return (-1);
	}
	DecodeChipDataTag(argv[1]);

	return (0);

}
