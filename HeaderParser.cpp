/*************************************************************************
    > File Name: ./HeaderParser.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 14 Nov 2022 04:34:28 AM EST
 ************************************************************************/

#include "HeaderParser.h" 

bool HeaderParser::getHexDump(uint8_t* buf, int size, int count=1, long seek=0)
{
	if (!filePtr)
		return false;
	if (fseek(filePtr, seek, SEEK_SET) == -1)
		return false;
	int realSize = -1;
	if ((realSize = fread(buf,size,count,filePtr)) == -1)
		return false;
	return true;
}

bool HeaderParser::dosHeaderParse() 
{
	uint8_t buf[DOS_HEADER_BUF_SIZE];
	if (!getHexDump(buf, DOS_HEADER_BUF_SIZE, 1,1))
		return false;
	//for (int i = 0; i < DOS_HEADER_BUF_SIZE; i++)
	//	printf("%X ", buf[i]);
	memcpy(&dh, buf, DOS_HEADER_BUF_SIZE);
	printf("%X\n", dh.e_oeminfo);
	return true;
}

