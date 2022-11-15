/*************************************************************************
    > File Name: ./HeaderParser.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 14 Nov 2022 04:28:33 AM EST
 ************************************************************************/
#ifndef _HEADERPARSER_H_
#define _HEADERPARSER_H_

#include <string>
#include <stdio.h>
#include <string.h>
#include "PEData.h"

#define DOS_HEADER_BUF_SIZE 40

using namespace std;

class HeaderParser {
public:
	HeaderParser(const string& name):filename{name} { filePtr = fopen(name.c_str(),"rb"); dosHeaderFlag = dosHeaderParse(); } 
	bool dosHeaderParse();	
	bool getHexDump(uint8_t* buf, int size, int count, long seek);
	~HeaderParser() { if (filePtr) fclose(filePtr); }
private:
	string filename;
	bool dosHeaderFlag = false;
	DosHeader dh;
	FILE* filePtr = NULL;
};
#endif
