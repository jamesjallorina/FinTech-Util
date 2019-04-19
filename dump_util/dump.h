#ifndef DUMP_UTIL_H
#define DUMP_UTIL_H


class dump
{
public:
	dump();
	dump(const dump &d);
	~dump();

	void outdump(const char *dump);
	void outdump();

private:
	char *data;
	size_t size;
}


#endif //DUMP_UTIL_H