#include "stdafx.h"
#include "UTF8.h"

//----------------------------------------------------------------------------------------------------------------------
// Ham chuyen doi UTF-8 sang Unicode
//----------------------------------------------------------------------------------------------------------------------
void Utf8_Unicode(BYTE *string_in, wchar_t *string_out)
{
	int i, scnt = strlen((char*)string_in);
	wchar_t unicode;
	i = 0;
	while (i <scnt) 
	{ // duyet tung byte
		if (0xc2<= string_in[i] && string_in[i] <= 0xe0 &&
		0x80<= string_in[i+1] && string_in[i+1] <= 0xbf)
		{
		// 2byte
		unicode = (string_in[i++] & 0x3f)<<6;
		unicode += (string_in[i++] & 0x3f);
		*string_out= unicode;
		}
		else 
			if (0xe0<= string_in[i] && string_in[i] <= 0xef &&
				0x80<= string_in[i+1] && string_in[i+1] <= 0xbf &&
				0x80<= string_in[i+2] && string_in[i+2] <= 0xbf) 
			{
			// 3byte
				unicode = (string_in[i++] & 0x0f)<<12;
				unicode += ((string_in[i++] & 0x3f)<<6);
				unicode += (string_in[i++] & 0x3f);
				*string_out = unicode;
			} 
			else 
				{ // 1byte
					*string_out = string_in[i++];
				}
				string_out++;
		}
		// chua ma ket thuc chuoi
	*string_out = 0;
}

/*
* Ham chuyen cac ma khac sang utf8
*/
CString  EncodeToUTF8(LPCTSTR szSource)
{
	WORD ch;

	BYTE bt1, bt2, bt3, bt4, bt5, bt6;

	int n, nMax = _tcslen(szSource);

	CString sFinal, sTemp;

	for (n = 0; n < nMax; ++n)
	{
		ch = (WORD)szSource[n];

		if (ch == _T('='))
		{
			sTemp.Format(_T("=%02X"), ch);

			sFinal += sTemp;
		}
		else if (ch < 128)
		{
			sFinal += szSource[n];
		}
		else if (ch <= 2047)
		{
			 bt1 = (BYTE)(192 + (ch / 64));
			 bt2 = (BYTE)(128 + (ch % 64));

			sTemp.Format(_T("=%02X=%02X"), bt1, bt2);
						
			sFinal += sTemp;
		}
		else if (ch <= 65535)
		{
			 bt1 = (BYTE)(224 + (ch / 4096));
			 bt2 = (BYTE)(128 + ((ch / 64) % 64));
			 bt3 = (BYTE)(128 + (ch % 64));

			sTemp.Format(_T("=%02X=%02X=%02X"), bt1, bt2, bt3);
						
			sFinal += sTemp;
		}
		else if (ch <= 2097151)
		{
			 bt1 = (BYTE)(240 + (ch / 262144));
			 bt2 = (BYTE)(128 + ((ch / 4096) % 64));
			 bt3 = (BYTE)(128 + ((ch / 64) % 64));
			 bt4 = (BYTE)(128 + (ch % 64));

			sTemp.Format(_T("=%02X=%02X=%02X=%02X"), bt1, bt2, bt3, bt4);
			sFinal += sTemp;
		}
		else if (ch <=67108863)
		{
			bt1 = (BYTE)(248 + (ch / 16777216));
			bt2 = (BYTE)(128 + ((ch / 262144) % 64));
			bt3 = (BYTE)(128 + ((ch / 4096) % 64));
			bt4 = (BYTE)(128 + ((ch / 64) % 64));
			bt5 = (BYTE)(128 + (ch % 64));

			sTemp.Format(_T("=%02X=%02X=%02X=%02X=%02X"), bt1, bt2, bt3, bt4, bt5);
			sFinal += sTemp;
		}
		else if (ch <=2147483647)
		{
			 bt1 = (BYTE)(252 + (ch / 1073741824));
			 bt2 = (BYTE)(128 + ((ch / 16777216) % 64));
			 bt3 = (BYTE)(128 + ((ch / 262144) % 64));
			 bt4 = (BYTE)(128 + ((ch / 4096) % 64));
			 bt5 = (BYTE)(128 + ((ch / 64) % 64));
			 bt6 = (BYTE)(128 + (ch % 64));

			sTemp.Format(_T("=%02X=%02X=%02X=%02X=%02X=%02X"), bt1, bt2, bt3, bt4, bt5, bt6);
			sFinal += sTemp;
		}

	}

	return sFinal;
}

void strncpy1(char *dest,char *src,int n){
	int lensrc=0,i=0;
	while (*(src+lensrc)!='\0')lensrc++;
	if (n< lensrc){
	while(*(src+i)!='\0'&&i!=n) {*(dest+i)=*(src+i);i++;}
	*(dest+i)='\0';
	}
}

int indexOf(const char *s,int c){
 int i=0;
 while (*(s+i)!='\0'&& *(s+i)!=c) i++;

 return i;
}  


void strcat1(char *dest,char *src){
   int lendest=0,lensrc=0,i;
	while(*(dest+lendest)!='\0') lendest++;
	while(*(src+lensrc)!='\0') lensrc++;
	   i=lendest;
       while (i<lendest+lensrc){
       *(dest+i)=*(src+i-lendest);
       i++;
       }
       *(dest+i)='\0';
}



