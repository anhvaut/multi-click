
#if !defined(AFX_MultiClickDLG_H__3916B450_FB76_11D4_868C_00E02930B0CE__INCLUDED_)
#define AFX_MultiClickDLG_H__3916B450_FB76_11D4_868C_00E02930B0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	nUNICODE_BOM						0xFEFF		// Unicode "byte order mark" 
#define	sNEWLINE								_T("\r\n")	// New line characters
#define	sDEFAULT_UNICODE_FILLER_CHAR	"#"			// Filler char used when no conversion from Unicode to local code page is possible

class CStdioFileEx: public CStdioFile
{
public:
	CStdioFileEx();
	CStdioFileEx( LPCTSTR lpszFileName, UINT nOpenFlags );

	virtual BOOL	Open( LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL );
	virtual BOOL	ReadString(CString& rString);
	virtual void	WriteString( LPCTSTR lpsz );
	bool				IsFileUnicodeText()	{ return m_bIsUnicodeText; }	
	unsigned long	GetCharCount();

	// flag cho phe'p ghi unicode
	static const UINT modeWriteUnicode;


	static int		GetUnicodeStringFromMultiByteString(IN char * szMultiByteString, OUT wchar_t* szUnicodeString, IN OUT int& nUnicodeBufferSize, IN UINT nCodePage=-1);


	static int			GetMultiByteStringFromUnicodeString(wchar_t * szUnicodeString,char* szMultiByteString,
																			short nMultiByteBufferSize,UINT nCodePage=-1);



	static bool IsFileUnicode(const CString& sFilePath);


protected:
	UINT ProcessFlags(const CString& sFilePath, UINT& nOpenFlags);

	bool		m_bIsUnicodeText;
	UINT		m_nFlags;
};

#endif

