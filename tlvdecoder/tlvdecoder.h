#ifndef TLV_DECODER_H
#define TLV_DECODER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>

#define DBG_LEN 2048
#define init_char(str) (memset(str,'\0',sizeof(str)))

namespace emv {

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

class emvparser 
{
public:
        void DecodeChipDataTag(const string emvtags);

private:
	const char emvtags[255+1];
	std::string issuer_script_template_1;
	std::string issuer_script_template_2;
	std::string app_interchange_profile;
	std::string dedicated_file_name;
	std::string issuer_authentication_data;
	std::string terminal_verification_result;
	std::string transaction_date;
	std::string transaction_type;
	std::string transaction_currency_code;
	std::string amount_authorized;
	std::string amount_other;
	std::string application_identifier;
	std::string application_usage_control;
	std::string terminal_application_version_number;
	std::string issuer_application_data;
	std::string terminal_country_code;
	std::string interface_device_serial_number;
	std::string application_crpytogram;
	std::string cryptogram_information_data;
	std::string terminal_capability;
	std::string cardholder_verfication_method_result;
	std::string terminal_type;
	std::string application_transaction_counter;
	std::string unpredictable_number;
	std::string transaction_sequence_counter;
	std::string transaction_category_code;
	std::string issuer_script_result;
	std::string card_product_identification;
	std::string issuer_authorization_code;
};

} //namespace emv

#endif //TLV_DECODER_H