#ifndef _CODE_TABLE_H
#define _CODE_TABLE_H

class CCodeTable{
public:
	 int isVietNamese(CHAR* st);
	 int isVietNameseW(WORD* st,int);
	 CHAR* convert(WORD* st,int,int);
	 CHAR* convert2Utf8(WORD* st,int,int);
	 void Convert_String(CHAR *string_out, wchar_t *string_in);
};
#endif