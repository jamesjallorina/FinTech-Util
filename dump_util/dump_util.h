#ifndef DUMP_UTIL_H
#define DUMP_UTIL_H


class dump
{
public:
	dump();
	dump(const dump &d);
	~dump();

	void outdump()

private:
	char *data;
}


#endif //DUMP_UTIL_H