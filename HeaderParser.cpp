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
	if (!getHexDump(buf, DOS_HEADER_BUF_SIZE, 1,0))
		return false;
	//for (int i = 0; i < DOS_HEADER_BUF_SIZE; i++)
		//printf("%X ", buf[i]);
	memcpy(&dh, buf, DOS_HEADER_BUF_SIZE);
	//printf("%#x\n",dh.e_magic);
	//printf("%#x\n",dh.e_lfanew);
	return true;
}

bool HeaderParser::SignatureParse()
{
	int seek = dh.e_lfanew;
	uint8_t buf[SIGNATURE_HEADER_BUF_SIZE];
	if (!getHexDump(buf, SIGNATURE_HEADER_BUF_SIZE,1,seek))
		return false;
	memcpy(&nth, buf, SIGNATURE_HEADER_BUF_SIZE);
	//printf("%#x\n", nth.signature);
	return true;
}

bool HeaderParser::ImageFileHeaderParse()
{
	int seek = dh.e_lfanew+SIGNATURE_HEADER_BUF_SIZE;
	uint8_t buf[IMAGE_FILE_HEADER_BUF_SIZE];
	if (!getHexDump(buf, IMAGE_FILE_HEADER_BUF_SIZE,1,seek))
		return false;
	//for (int i = 0; i < DOS_HEADER_BUF_SIZE; i++)
		//printf("%X ", buf[i]);
	memcpy(&(nth.FileHeader), buf, IMAGE_FILE_HEADER_BUF_SIZE);
	//printf("%#x\n",nth.FileHeader.Machine);
	//printf("%#x\n",nth.FileHeader.NumberOfSections);
	//printf("%#x\n",nth.FileHeader.SizeOfOptionalHeader);
	//printf("%#x\n",nth.FileHeader.Characteristics);
	return true;
}

bool HeaderParser::ImageOptionalHeaderParse()
{
	int seek = dh.e_lfanew+SIGNATURE_HEADER_BUF_SIZE+IMAGE_FILE_HEADER_BUF_SIZE;
	int size = nth.FileHeader.SizeOfOptionalHeader;
	uint8_t buf[size];
	if (!getHexDump(buf,size,1,seek))
		return false;
	memcpy(&(nth.OptionalHeader), buf,size);
	/*
	printf("%#x\n",nth.OptionalHeader.Magic);
	printf("%#x\n",nth.OptionalHeader.AddressOfEntryPoint);
	printf("%#x\n",nth.OptionalHeader.ImageBase);
	printf("%#x\n",nth.OptionalHeader.SectionAlignment);
	printf("%#x\n",nth.OptionalHeader.FileAlignment);
	printf("%#x\n",nth.OptionalHeader.SizeOfImage);
	printf("%#x\n",nth.OptionalHeader.SizeOfHeaders);
	printf("%#x\n",nth.OptionalHeader.Subsystem);
	printf("%#x\n",nth.OptionalHeader.NumberOfRvaAndSizes);
	for (int i = 0; i < nth.OptionalHeader.NumberOfRvaAndSizes; i++)
	{
		IMAGE_DATA_DIRECTORY directory = nth.OptionalHeader.DataDirectory[i];
		printf("VA: %#x, Size:%#x\n",directory.VirtualAddress, directory.Size);
	}
	*/
	return true;
}

bool HeaderParser::NTHeaderParse()
{
	return SignatureParse() && ImageFileHeaderParse() && ImageOptionalHeaderParse();
}



