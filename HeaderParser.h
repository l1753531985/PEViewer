/*************************************************************************
    > File Name: ./HeaderParser.h
    > Author: LiRvs 
    > Mail: l1753531985@gmail.com 
    > Created Time: Mon 14 Nov 2022 04:28:33 AM EST
 ************************************************************************/
#ifndef _HEADERPARSER_H_
#define _HEADERPARSER_H_

#include <string>
#include <stdio.h>
#include <string.h>
#include "PEData.h"
#include <vector>

using namespace std;

class HeaderParser {
public:
	HeaderParser(const string& name)
		:filename{name} 
	{ 
		filePtr = fopen(name.c_str(),"rb"); 
		dosHeaderFlag = dosHeaderParse();
		NTHeaderFlag = NTHeaderParse();
		SectionHeaderFlag = sectionHeaderParse();
	} 
	bool dosHeaderParse();	
	bool NTHeaderParse();	
	bool sectionHeaderParse();
	bool getHexDump(uint8_t* buf, int size, int count, long seek);
	~HeaderParser() 
	{ 
		if (filePtr) fclose(filePtr); 
	}
private:
	string filename;
	bool dosHeaderFlag = false;
	bool NTHeaderFlag = false;
	bool SectionHeaderFlag = false;
	DosHeader dh;
	NTHeader nth;
	vector<SectionHeader> vsh;
	FILE* filePtr = NULL;
	bool SignatureParse();
	bool ImageFileHeaderParse();
	bool ImageOptionalHeaderParse();
};
#endif
