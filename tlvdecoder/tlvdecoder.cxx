//codedforC++98standard
//CreatebyJamesJallorina
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
        function        : string_init
        description     : initialize private string members
*/
void emvparser::string_init()
{
        issuer_script_template_1 = "";
        issuer_script_template_2 = "";
        app_interchange_profile = "";
        dedicated_file_name = "";
        issuer_authentication_data = "";
        terminal_verification_result = "";
        transaction_date = "";
        transaction_type = "";
        transaction_currency_code = "";
        amount_authorized = "";
        amount_other = "";
        application_identifier = "";
        application_usage_control = "";
        terminal_application_version_number = "";
        issuer_application_data = "";
        terminal_country_code = "";
        interface_device_serial_number = "";
        application_crpytogram = "";
        cryptogram_information_data = "";
        terminal_capability = "";
        cardholder_verfication_method_result = "";
        terminal_type = "";
        application_transaction_counter = "";
        unpredictable_number = "";
        transaction_sequence_counter = "";
        transaction_category_code = "";
        issuer_script_result = "";
        card_product_identification = "";
        issuer_authorization_code = "";

}

/*
        function: emvparser copy constructor
        @emvparser: pass an emvparser object
*/
emvparser::emvparser(const emvparser &e)
{
        hval = e.hval;  //added copy ctor 
        sval = e.sval;  //added copy ctor
        issuer_script_template_1 = e.issuer_script_template_1;
        issuer_script_template_2 = e.issuer_script_template_2;
        app_interchange_profile = e.app_interchange_profile;
        dedicated_file_name = e.dedicated_file_name;
        issuer_authentication_data = e.issuer_authentication_data;
        terminal_verification_result = e.terminal_verification_result;
        transaction_date = e.transaction_date;
        transaction_type = e.transaction_type;
        transaction_currency_code = e.transaction_currency_code;
        amount_authorized = e.amount_authorized;
        amount_other = e.amount_other;
        application_identifier = e.application_identifier;
        application_usage_control = e.application_usage_control;
        terminal_application_version_number = e.terminal_application_version_number;
        issuer_application_data = e.issuer_application_data;
        terminal_country_code = e.terminal_country_code;
        interface_device_serial_number = e.interface_device_serial_number;
        application_crpytogram = e.application_crpytogram;
        cryptogram_information_data = e.cryptogram_information_data;
        terminal_capability = e.terminal_capability;
        cardholder_verfication_method_result = e.cardholder_verfication_method_result;
        terminal_type = e.terminal_type;
        application_transaction_counter = e.application_transaction_counter;
        unpredictable_number = e.unpredictable_number;
        transaction_sequence_counter = e.transaction_sequence_counter;
        transaction_category_code = e.transaction_category_code;
        issuer_script_result = e.issuer_script_result;
        card_product_identification = e.card_product_identification;
        issuer_authorization_code = e.issuer_authorization_code;
}



/*
        function: convert char strings to hex
        @tags   : charstringtags
        @len    : lengthoftags
*/
unsigned char *emvparser::convert_to_hex(const unsigned char *tags, size_t *len)
{
        //char *p = &tags[0];
        size_t c = 0;
        size_t emvlen = *len;
        static unsigned char p[255+1];
        unsigned char msb;
        unsigned char lsb;
        for(int i = 0; i < emvlen; )
        {
                msb = tags[i] < 58 ? (tags[i++] - 48) << 4 : (tags[i++] - 55) << 4;

                lsb = tags[i] < 58 ? tags[i++] - 48 : tags[i++] - 55;         
                //printf("mlsb : %.2x \n", msb);
                //printf("lsb : %.2x \n", lsb);
                p[c] = msb | lsb;
                //printf("p[c] : %.2x \n", p[c]);
                c++;
        }
        *len = c;
        return &p[0];
}

/*
        function: convert hex to string
        @tags   : charstringtags
        @len    : lengthoftags
*/
unsigned char *emvparser::convert_to_string(const unsigned char *tags, size_t *hlen, size_t *slen)
{
        size_t c = 0;
        size_t emvlen = *hlen;
        unsigned char buf;
        static unsigned char p[255+255+1];
        
        memset((unsigned char *)p, 0, sizeof(p));
        
//      printf("passed emvlen: %zu \n", emvlen);
//      printf("passed hextags: \n");
//      for(int j = 0; j < emvlen; j++)
//      {
//              printf("0x%.2x ", tags[j]);
//      }
        for(int i = 0; i < emvlen; i++)
        {
 //             printf("converting tag: %.2x \n", tags[i]);
                buf = ((tags[i] & 0xF0) >> 4) < 10 ? (((tags[i] & 0xF0) >> 4) + 48) : (((tags[i] & 0xF0) >> 4) + 55);
//              printf("%c ", buf);
                p[c++] = buf; 
                //sprintf(p[i], "%x", buf[c]);
                buf = (tags[i] & 0x0F) < 10 ? (tags[i] & 0x0F) + 48 : (tags[i] & 0x0F) + 55;
                //sprintf(p[i], "%x", buf[c]);
//              printf("%c ", buf);
                p[c++] = buf;
//              printf("\n");
//              printf("i: %d \n", i);
        }
        *slen = c;
        
        return &p[0];
}




/*
        function   : decod eemvtags
        @emvtags   : charstringtags
*/
void emvparser::decode(const char *emvtags)
{
        char chipdata[DBG_LEN];
        init_char(chipdata);
        char tag[4 + 1];
        init_char(tag);
        char taglen[2 + 1];
        init_char(taglen);
        char tagdata[255 + 1];
        init_char(tagdata);
        std::string _tag = "";
        if(emvtags[0] == '\0')
                return;

        sprintf(chipdata,"%s",emvtags); //loadthevaluetocharacterarray

        int iDataLen = 0, iChipDataLen = 0, itagIndex = 0, iDataTagLen = 0;     //intiCounter = 0
        long int itag = 0;

        iChipDataLen = strlen(chipdata);


        while(itagIndex < iChipDataLen)
        {
        memset(tag,'\0',sizeof(tag)); // WewillresetthevalueforTagCatching
        memset(taglen, '\0',sizeof(taglen));
        memset(tagdata, '\0',sizeof(tagdata));
       
	memcpy(tag,chipdata+itagIndex,2);

        /**
        * Check if the Tag Data hasan 'F' or 'f' Value
        * else none we will treat it as 2bytes Tag Data
        **/
        if(tag[1] == 'F' || tag[1] == 'f')      //incorporate lowercase too
		iDataLen = 4;
        else
		iDataLen = 2;

	memcpy(tag, chipdata+itagIndex, iDataLen); 

        itagIndex += iDataLen; //move the index depends on the value of DataTag
        memcpy(taglen, chipdata + itagIndex, 2);
	itagIndex += 2; // We will add 2bytes for length and move the index
        iDataTagLen = strtol(taglen,NULL,16);
	iDataTagLen *= 2;	//multiplyby2

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
        	std::cout << "emv tag not defined: " << "[" << tag << "]" << std::endl;
        break;
        }
        //sprintf(acWholeDataTag,"%s%s",acWholeDataTag,tagdata); // mayusedependsonsystemrequirement
        }

        return;
}

void emvdump(emvparser e)
{
        printf("EMV DUMP START \n");
        printf("%-50s:[%s] \n", "Issuer Script Template1", e.issuer_script_template_1.c_str());
        printf("%-50s:[%s] \n", "Issuer Script Template2", e.issuer_script_template_2.c_str());
        printf("%-50s:[%s] \n", "Application Interchange Profile", e.app_interchange_profile.c_str());
        printf("%-50s:[%s] \n", "Dedicated File Name", e.dedicated_file_name.c_str());
        printf("%-50s:[%s] \n", "Issuer Authentication Data" , e.issuer_authentication_data.c_str());
        printf("%-50s:[%s] \n", "Terminal Verification Result", e.terminal_verification_result.c_str());
        printf("%-50s:[%s] \n", "Transaction Date", e.transaction_date.c_str());
        printf("%-50s:[%s] \n", "Transaction Type", e.transaction_type.c_str());
        printf("%-50s:[%s] \n", "Transaction Currency Code", e.transaction_currency_code.c_str());
        printf("%-50s:[%s] \n", "Amount Authorized", e.amount_authorized.c_str());
        printf("%-50s:[%s] \n", "Amount Other", e.amount_other.c_str());
        printf("%-50s:[%s] \n", "Application Identifier", e.application_identifier.c_str());
        printf("%-50s:[%s] \n", "Application UsageControl", e.application_usage_control.c_str());
        printf("%-50s:[%s] \n", "Terminal Application VersionNumber", e.terminal_application_version_number.c_str());
        printf("%-50s:[%s] \n", "Issuer Application Data", e.issuer_application_data.c_str());
        printf("%-50s:[%s] \n", "Terminal CountryCode", e.terminal_country_code.c_str());
        printf("%-50s:[%s] \n", "Interface Device Serial Number", e.interface_device_serial_number.c_str());
        printf("%-50s:[%s] \n", "Application Cryptogram", e.application_crpytogram.c_str());
        printf("%-50s:[%s] \n", "Cryptogram Information Data", e.cryptogram_information_data.c_str());
        printf("%-50s:[%s] \n", "Terminal Capability", e.terminal_capability.c_str());
        printf("%-50s:[%s] \n", "Card holder Verification Method Result", e.cardholder_verfication_method_result.c_str());
        printf("%-50s:[%s] \n", "Terminal Type", e.terminal_type.c_str());
        printf("%-50s:[%s] \n", "Application Transaction Counter", e.application_transaction_counter.c_str());
        printf("%-50s:[%s] \n", "Unpredictable Number", e.unpredictable_number.c_str());
        printf("%-50s:[%s] \n", "Transaction Sequence Counter", e.transaction_sequence_counter.c_str());
        printf("%-50s:[%s] \n", "Transaction Category Code", e.transaction_category_code.c_str());
        printf("%-50s:[%s] \n", "Issuer Script Result", e.issuer_script_result.c_str());
        printf("%-50s:[%s] \n", "Card Product Identification", e.card_product_identification.c_str());
        printf("%-50s:[%s] \n", "Issuer Authorization Code - ElectronicCash", e.issuer_authorization_code.c_str());
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
