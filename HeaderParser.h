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

using namespace std;

class HeaderParser {
public:
	HeaderParser(const string& name)
		:filename{name} 
	{ 
		filePtr = fopen(name.c_str(),"rb"); 
		dosHeaderFlag = dosHeaderParse();
		NTHeaderFlag = NTHeaderParse();
	} 
	bool dosHeaderParse();	
	bool NTHeaderParse();	
	bool getHexDump(uint8_t* buf, int size, int count, long seek);
	~HeaderParser() { if (filePtr) fclose(filePtr); }
private:
	string filename;
	bool dosHeaderFlag = false;
	bool NTHeaderFlag = false;
	DosHeader dh;
	NTHeader nth;
	FILE* filePtr = NULL;
	bool SignatureParse();
	bool ImageFileHeaderParse();
	bool ImageOptionalHeaderParse();
};
#endif
