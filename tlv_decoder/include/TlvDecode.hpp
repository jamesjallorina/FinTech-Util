/**************************************************************************
**	Author : James Marjun Jallorina
**	Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph
**
**
**
**	Module Name:
**		TlvDecode.hpp
**	Abstract:
**    This module decodes the TLV Chip Data Tag
***************************************************************************/


#ifndef _TLV_DECODE_H_
#define _TLV_DECODE_H_

class TlvDecode
{
	private:
		emvbuf *emvptr;
	public:
		TlvDecode();
		virtual ~TlvDecode();
		virtual void DecodeChipDataTag(const char* EmvTags);
		virtual void DecodeChipDataTag(const string sEmvTags);
		virtual int emvdump(emvbuf *emvptr);
};

#endif	//_TLV_DECODE_H_