#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *convert_to_hex(const unsigned char *tags, size_t *len)
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


unsigned char *convert_to_string(const unsigned char *tags, size_t *hlen, size_t *slen)
{
        size_t c = 0;
        size_t emvlen = *hlen;
	unsigned char buf;
        static unsigned char p[255+255+1];
	
        memset((unsigned char *)p, 0, sizeof(p));
	
//	printf("passed emvlen: %zu \n", emvlen);
//	printf("passed hextags: \n");
//	for(int j = 0; j < emvlen; j++)
//	{
//		printf("0x%.2x ", tags[j]);
//	}
        for(int i = 0; i < emvlen; i++)
        {
		printf("converting tag: %.2x \n", tags[i]);
		buf = ((tags[i] & 0xF0) >> 4) < 10 ? (((tags[i] & 0xF0) >> 4) + 48) : (((tags[i] & 0xF0) >> 4) + 55);
//		printf("%c ", buf);
		p[c++] = buf; 
		//sprintf(p[i], "%x", buf[c]);
		buf = (tags[i] & 0x0F) < 10 ? (tags[i] & 0x0F) + 48 : (tags[i] & 0x0F) + 55;
		//sprintf(p[i], "%x", buf[c]);
//		printf("%c ", buf);
		p[c++] = buf;
//		printf("\n");
//		printf("i: %d \n", i);
        }
	*slen = c;
	
        return &p[0];
}

#if 0
unsigned char *convert_to_hex(const unsigned char *tags, size_t *len)
{
	//char *p = &tags[0];
	size_t c = 0;
	size_t emvlen = *len;
	static unsigned char p[255+1];
	unsigned char fb;
	unsigned char sb;
	for(int i = 0; i < emvlen; )
	{
		if(tags[i] < 58){
			fb = (tags[i++] - 48) << 4;
		}
		else{
			fb = (tags[i++] - 55) << 4;
		}
		if(tags[i] < 58){
			sb = tags[i++] - 48;
		}
		else{
			sb = tags[i++] - 55;
		}
		//printf("fb : %.2x \n", fb);
		//printf("sb : %.2x \n", sb);
		p[c] = fb | sb;
		//printf("p[c] : %.2x \n", p[c]);
			c++;
	}
	*len = c;
	return &p[0];
}
#endif 


int main(int argc, char **argv)
{
	//const unsigned char *emvbuf = "82021800950580000480009A031903249C01005F2A0206089F0206000000005000";
//	const unsigned char *emvbuf = (unsigned char *)"82021800950580000480009A031903249C01005F2A0206089F02009F03060000000000009F090200969F100706010A03A000009F1A0206089F1E0831303130323339379F26089CACA1980BE11EBA9F2701809F3303E040009F34030200009F3501119F3602000B9F3704A353AD555F24009F40056000F0F0019F08020096";

	unsigned char *emvbuf = (unsigned char *) argv[1];
	unsigned char *emv_hex = NULL;
	unsigned char *emv_string = NULL;
	unsigned char buf[255+255 +1];

	size_t hexlen = strlen((const char *)emvbuf); 
	size_t stringlen = 0;	

	memset((unsigned char *) buf, 0, sizeof(buf));

	emv_hex = convert_to_hex(emvbuf, &hexlen);	
	printf("hexlen: %zu \n", hexlen);
	memcpy((unsigned char* )buf, emv_hex, hexlen);
	
//	printf("converted string to hex : ");
//	for(int i =0; i < hexlen; ++i)
//	{
	//printf("0x%.2x, ", emv_hex[i]);
//	printf("0x%.2x ", buf[i]);
//	}
//	printf("\n");
	emv_string = convert_to_string(buf, &hexlen, &stringlen);
	printf("converted hex to string: ");
	printf("%s \n", emv_string);
	printf("actual stringlen: %zu \n", stringlen);
	return 0;
}
