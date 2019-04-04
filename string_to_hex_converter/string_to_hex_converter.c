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

int main(int argc, char **argv)
{
	//const unsigned char *emvbuf = "82021800950580000480009A031903249C01005F2A0206089F0206000000005000";
//	const unsigned char *emvbuf = (unsigned char *)"82021800950580000480009A031903249C01005F2A0206089F02009F03060000000000009F090200969F100706010A03A000009F1A0206089F1E0831303130323339379F26089CACA1980BE11EBA9F2701809F3303E040009F34030200009F3501119F3602000B9F3704A353AD555F24009F40056000F0F0019F08020096";

	unsigned char *emvbuf = (unsigned char *) argv[1];
	unsigned char *emv = NULL;
	size_t len = strlen((const char *)emvbuf); 
	

	emv = convert_to_hex(emvbuf, &len);	
	for(int i =0; i < len; ++i)
	{
	printf("0x%.2x, ", emv[i]);
	}
	printf("\n");
}
