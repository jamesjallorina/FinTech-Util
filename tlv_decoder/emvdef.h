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
    emvdef.h
Abstract:
    This module defines emv structure
--*/
#ifndef _EMV_DEF_H_
#define _EMV_DEF_H_

const char *emv_tag_71 		= "71";
const char *emv_tag_72 		= "72";
const char *emv_tag_82 		= "82";
const char *emv_tag_84 		= "84"; 	
const char *emv_tag_91 	    = "91"; 	
const char *emv_tag_95 	    = "95"; 	
const char *emv_tag_9A 	    = "9A"; 	
const char *emv_tag_9C 	    = "9C"; 	
const char *emv_tag_5F2A    = "5F2A";
const char *emv_tag_9F02    = "9F02";
const char *emv_tag_9F03    = "9F03";
const char *emv_tag_9F06    = "9F06";
const char *emv_tag_9F07    = "9F07";
const char *emv_tag_9F09    = "9F09";
const char *emv_tag_9F10    = "9F10";
const char *emv_tag_9F1A    = "9F1A";
const char *emv_tag_9F1E    = "9F1E";
const char *emv_tag_9F26    = "9F26";
const char *emv_tag_9F27    = "9F27";
const char *emv_tag_9F33    = "9F33";
const char *emv_tag_9F34    = "9F34";
const char *emv_tag_9F35    = "9F35";
const char *emv_tag_9F36    = "9F36";
const char *emv_tag_9F37    = "9F37";
const char *emv_tag_9F41    = "9F41";
const char *emv_tag_9F53    = "9F53";
const char *emv_tag_9F5B    = "9F5B";
const char *emv_tag_9F63    = "9F63";
const char *emv_tag_9F74    = "9F74";

struct emvbuf{
	issuer_script_template_1[128+1];
	issuer_script_template_2[128+1];
	app_interchange_profile[2+1];
	dedicated_file_name[16+1];
	issuer_authentication_data[16+1];
	terminal_verification_result[5+1];
	transaction_date[3+1];
	transaction_type[1+1];
	transaction_currency_code[2+1];
	amount_authorized[6+1];
	amount_other[6+1];
	application_identifier[16+1];
	application_usage_control[2+1];
	terminal_application_version_number[2+1];
	issuer_application_data[32+1];
	terminal_country_code[2+1];
	interface_device_serial_number[8+1];
	application_crpytogram[8+1];
	cryptogram_information_data[1+1];
	terminal_capability[3+1];
	cardholder_verfication_method_result[3+1];
	terminal_type[1+1];
	application_transaction_counter[2+1];
	unpredictable_number[4+1];
	transaction_sequence_counter[4+1];
	transaction_category_code[1+1];
	issuer_script_result[25+1];
	card_product_identification[16+1];
	issuer_authorization_code[6+1];
};

#endif