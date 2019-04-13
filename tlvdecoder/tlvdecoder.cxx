//coded for C++98 standard
//Create by James Jallorina
#include "tlvdecoder.h"

#if 0
using emv::emv_tag_71;
using emv::emv_tag_72;
using emv::emv_tag_82;
using emv::emv_tag_84;
using emv::emv_tag_91;
using emv::emv_tag_95;
using emv::emv_tag_9A;
using emv::emv_tag_9C;
using emv::emv_tag_5F2A;
using emv::emv_tag_9F02;
using emv::emv_tag_9F03;
using emv::emv_tag_9F06;
using emv::emv_tag_9F07;
using emv::emv_tag_9F09;
using emv::emv_tag_9F10;
using emv::emv_tag_9F1A;
using emv::emv_tag_9F1E;
using emv::emv_tag_9F26; 
using emv::emv_tag_9F27;
using emv::emv_tag_9F33;
using emv::emv_tag_9F34;
using emv::emv_tag_9F35;
using emv::emv_tag_9F36;
using emv::emv_tag_9F37;
using emv::emv_tag_9F41;
using emv::emv_tag_9F53;
using emv::emv_tag_9F5B;
using emv::emv_tag_9F63;
using emv::emv_tag_9F74;
#endif

/*
        function: convert char strings to hex
        @tags   : char string tags
        @len    : length of tags
*/
unsigned char *emvparser::convert_to_hex(const unsigned char *tags, size_t *len)
{
        //char *p = &tags[0];
        size_t c = 0;
        size_t emvlen = *len;
        static unsigned char p[255+1];
        unsigned char fb;
        unsigned char sb;
        for(int i = 0; i < emvlen; )
        {
                fb = tags[i] < 58 ? (tags[i++] - 48) << 4 : (tags[i++] - 55) << 4;

                sb = tags[i] < 58 ? sb = tags[i++] - 48 : tags[i++] - 55;         
                //printf("fb : %.2x \n", fb);
                //printf("sb : %.2x \n", sb);
                p[c] = fb | sb;
                //printf("p[c] : %.2x \n", p[c]);
                c++;
        }
        *len = c;
        return &p[0];
}

/*
        function: decode emv tags
        @emvtags   : char string tags
*/
void emvparser::decode(const char *emvtags)
{

        std::string _tag = "";

        char chipdata[DBG_LEN];
        init_char(chipdata);
        char tag[4 + 1];
        init_char(tag);
        char taglen[2 + 1];
        init_char(taglen);
        char tagdata[255 + 1];
        init_char(tagdata);

        if(emvtags[0] == '\0')
                return;

        sprintf(chipdata,"%s",emvtags); //load the value to character array

        int iDataLen = 0, iChipDataLen = 0, itagIndex = 0, iDataTagLen = 0;     //int iCounter = 0
        long int itag = 0;

        iChipDataLen = strlen(chipdata);


        while(itagIndex < iChipDataLen)
        {
        memset(tag,'\0',sizeof(tag)); // We will reset the value for Tag Catching
        memset(taglen, '\0',sizeof(taglen));
        memset(tagdata, '\0',sizeof(tagdata));
       
	memcpy(tag,chipdata+itagIndex,2);

        /**
        * Check if the Tag Data has an 'F' Value
        * else none we will treat it as 2bytes Tag Data
        **/
        if(tag[1] == 'F')
		iDataLen = 4;
        else
		iDataLen = 2;

	memcpy(tag, chipdata+itagIndex, iDataLen); 

        itagIndex += iDataLen; //move the index depends on the value of Data Tag
        memcpy(taglen, chipdata + itagIndex, 2);
	itagIndex += 2; // We will add 2 bytes for length and move the index
        iDataTagLen = strtol(taglen,NULL,16);
	iDataTagLen *= 2;	//multiply by 2

        //now we will copy the Tag Value and we will move again depends on the length
        memcpy(tagdata,chipdata+itagIndex, iDataTagLen);
	itagIndex += iDataTagLen;	//move the index
	itag = strtol(tag, NULL, 16);
	printf("TAG: [%s] TAGLEN: [%d] TAGVALUE: [%s] \n", tag, iDataTagLen/2, tagdata);
        _tag = tagdata;
        switch(itag)
        {
        case emv_tag_71:
                issuer_script_template_1 = _tag;
        break;
        case emv_tag_72:
                issuer_script_template_2 = _tag;
        break;
        case emv_tag_82:
                app_interchange_profile = _tag;
        break;
        case emv_tag_84:
                dedicated_file_name = _tag;
        break;
        case emv_tag_91:
                issuer_authentication_data = _tag;
        break;
        case emv_tag_95:
                terminal_verification_result = _tag;
        break;
        case emv_tag_9A:
                transaction_date = _tag;
        break;
        case emv_tag_9C:
                transaction_type = _tag;
        break;
        case emv_tag_5F2A:
                transaction_currency_code = _tag;
        break;
        case emv_tag_9F02:
                amount_authorized = _tag;
        break;
        case emv_tag_9F03:
                amount_other = _tag;
        break;
        case emv_tag_9F06:
                application_identifier = _tag;
        break;
        case emv_tag_9F07:
                application_usage_control = _tag;
        break;
        case emv_tag_9F09:
                terminal_application_version_number = _tag;
        break;
        case emv_tag_9F10:
                issuer_application_data = _tag;
        break;
        case emv_tag_9F1A:
                terminal_country_code = _tag;
        break;
        case emv_tag_9F1E:
                interface_device_serial_number = _tag;
        break;
        case emv_tag_9F26:
                application_crpytogram = _tag;
        break;
        case emv_tag_9F27:
                cryptogram_information_data = _tag;
        break;
        case emv_tag_9F33:
                terminal_capability = _tag;
        break;
        case emv_tag_9F34:
                cardholder_verfication_method_result = _tag;
        break;
        case emv_tag_9F35:
                terminal_type = _tag;
        break;
        case emv_tag_9F36:
                application_transaction_counter = _tag;
        break;
        case emv_tag_9F37:
                unpredictable_number = _tag;
        break;
        case emv_tag_9F41:
                transaction_sequence_counter = _tag;
        break;
        case emv_tag_9F53:
                transaction_category_code = _tag;
        break;
        case emv_tag_9F5B:
                issuer_script_result = _tag;
        break;
        case emv_tag_9F63:
                card_product_identification = _tag;
        break;
        case emv_tag_9F74:
                issuer_authorization_code = _tag;
        break;
        default:
        break;
        }
        //sprintf(acWholeDataTag,"%s%s",acWholeDataTag,tagdata); // may use depends on system requirement
        }

        return;
}

void emvdump(emvparser e)
{
        printf("EMV DUMP START \n");
        printf("%-50s:[%s] \n", "Issuer Script Template 1", e.issuer_script_template_1.c_str());
        printf("%-50s:[%s] \n", "Issuer Script Template 2", e.issuer_script_template_2.c_str());
        printf("%-50s:[%s] \n", "Application Interchange Profile", e.app_interchange_profile.c_str());
        printf("%-50s:[%s] \n", "Dedicated File Name", e.dedicated_file_name.c_str());
        printf("%-50s:[%s] \n","Issuer Authentication Data" , e.issuer_authentication_data.c_str());
        printf("%-50s:[%s] \n", "Terminal Verification Result", e.terminal_verification_result.c_str());
        printf("%-50s:[%s] \n", "Transaction Date", e.transaction_date.c_str());
        printf("%-50s:[%s] \n", "Transaction Type", e.transaction_type.c_str());
        printf("%-50s:[%s] \n", "Transaction Currency Code", e.transaction_currency_code.c_str());
        printf("%-50s:[%s] \n", "Amount Authorized", e.amount_authorized.c_str());
        printf("%-50s:[%s] \n", "Amount Other", e.amount_other.c_str());
        printf("%-50s:[%s] \n", "Application Identifier", e.application_identifier.c_str());
        printf("%-50s:[%s] \n", "Application Usage Control", e.application_usage_control.c_str());
        printf("%-50s:[%s] \n", "Terminal Application Version Number", e.terminal_application_version_number.c_str());
        printf("%-50s:[%s] \n", "Issuer Application Data", e.issuer_application_data.c_str());
        printf("%-50s:[%s] \n", "Terminal Country Code", e.terminal_country_code.c_str());
        printf("%-50s:[%s] \n", "Interface Device Serial Number", e.interface_device_serial_number.c_str());
        printf("%-50s:[%s] \n", "Application Cryptogram", e.application_crpytogram.c_str());
        printf("%-50s:[%s] \n", "Cryptogram Information Data", e.cryptogram_information_data.c_str());
        printf("%-50s:[%s] \n", "Terminal Capability", e.terminal_capability.c_str());
        printf("%-50s:[%s] \n", "Cardholder Verification Method Result", e.cardholder_verfication_method_result.c_str());
        printf("%-50s:[%s] \n", "Terminal Type", e.terminal_type.c_str());
        printf("%-50s:[%s] \n", "Application Transaction Counter", e.application_transaction_counter.c_str());
        printf("%-50s:[%s] \n", "Unpredictable Number", e.unpredictable_number.c_str());
        printf("%-50s:[%s] \n", "Transaction Sequence Counter", e.transaction_sequence_counter.c_str());
        printf("%-50s:[%s] \n", "Transaction Category Code", e.transaction_category_code.c_str());
        printf("%-50s:[%s] \n", "Issuer Script Result", e.issuer_script_result.c_str());
        printf("%-50s:[%s] \n", "Card Product Identification", e.card_product_identification.c_str());
        printf("%-50s:[%s] \n", "Issuer authorization Code - Electronic Cash", e.issuer_authorization_code.c_str());
        printf("EMV DUMP END \n");
        return;
}


int main(int argc, char **argv)
{
        emvparser _parser;

        if(argc < 2){
                std::cout << "usage: " << std::endl;
                std::cout << "tlvdecoder [emvtags]" << std::endl;
                return (-1);
        }
        _parser.decode(argv[1]);
        emvdump(_parser);

        return (0);

}
