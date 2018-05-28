#ifndef  __UTF8_H
#define __UTF8_H

	void Utf8_Unicode(BYTE *string_in, wchar_t *string_out);
	CString  EncodeToUTF8(LPCTSTR szSource);
	void strncpy1(char *dest,char *src,int n);
	int indexOf(const char *s,int c);
	void strcat1(char *dest,char *src);

#endif
