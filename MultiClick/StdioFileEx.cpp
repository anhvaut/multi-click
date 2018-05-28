
#include "stdafx.h"
#include "StdioFileEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*static*/ const UINT CStdioFileEx::modeWriteUnicode = 0x20000; // Add this flag to write in Unicode

CStdioFileEx::CStdioFileEx(): CStdioFile()
{
	m_bIsUnicodeText = false;
}

CStdioFileEx::CStdioFileEx(LPCTSTR lpszFileName,UINT nOpenFlags)
	:CStdioFile(lpszFileName, ProcessFlags(lpszFileName, nOpenFlags))
{
}

BOOL CStdioFileEx::Open(LPCTSTR lpszFileName,UINT nOpenFlags,CFileException* pError /*=NULL*/)
{

	ProcessFlags(lpszFileName, nOpenFlags);

	return CStdioFile::Open(lpszFileName, nOpenFlags, pError);
}

BOOL CStdioFileEx::ReadString(CString& rString)
{
	const int	nMAX_LINE_CHARS = 4096;
	BOOL			bReadData;
	LPTSTR		lpsz;
	int			nLen = 0; //, nMultiByteBufferLength = 0, nChars = 0;
	CString		sTemp;
	wchar_t*		pszUnicodeString = NULL;
	char	*		pszMultiByteString= NULL;

	// If at position 0, discard byte-order mark before reading
	if (!m_pStream || (GetPosition() == 0 && m_bIsUnicodeText))
	{
		wchar_t	cDummy;
//		Read(&cDummy, sizeof(_TCHAR));
		Read(&cDummy, sizeof(wchar_t));
	}

// If compiled for Unicode
#ifdef _UNICODE
	// Do standard stuff -- both ANSI and Unicode cases seem to work OK
	bReadData = CStdioFile::ReadString(rString);
#else

	if (!m_bIsUnicodeText)
	{
		// Do standard stuff -- read ANSI in ANSI
		bReadData = CStdioFile::ReadString(rString);
	}
	else
	{
		pszUnicodeString	= new wchar_t[nMAX_LINE_CHARS]; 
		pszMultiByteString= new char[nMAX_LINE_CHARS];  

		// Read as Unicode, convert to ANSI; fixed by Dennis Jeryd 6/8/03
		bReadData = (NULL != fgetws(pszUnicodeString, nMAX_LINE_CHARS, m_pStream));
		if (GetMultiByteStringFromUnicodeString(pszUnicodeString, pszMultiByteString, nMAX_LINE_CHARS))
		{
			rString = (CString)pszMultiByteString;
		}

		if (pszUnicodeString)
		{
			delete pszUnicodeString;
		}

		if (pszMultiByteString)
		{
			delete pszMultiByteString;
		}
	}
#endif

	// xo'a end-of-line character ne^'u la` Unicode text mode
	if (bReadData)
	{
		
		nLen = rString.GetLength();
		if (nLen > 1 && rString.Mid(nLen-2) == sNEWLINE)
		{
			rString.GetBufferSetLength(nLen-2);
		}
		else
		{
			lpsz = rString.GetBuffer(0);
			if (nLen != 0 && (lpsz[nLen-1] == _T('\r') || lpsz[nLen-1] == _T('\n')))
			{
				rString.GetBufferSetLength(nLen-1);
			}
		}
	}

	return bReadData;
}


void CStdioFileEx::WriteString(LPCTSTR lpsz)
{
	//ne^'u ghi unicode va` o+? ddau do`ng ca^`n co' ma(.t na. byte mark
	if (m_nFlags & CStdioFileEx::modeWriteUnicode)
	{
		// Ta.i vi. tri' thu+' 0, ghi ma(.t na. mark tru+o+'c tie^n
		if (!m_pStream || GetPosition() == 0)
		{
			wchar_t cBOM = (wchar_t)nUNICODE_BOM;
			CFile::Write(&cBOM, sizeof(wchar_t));
		}
	}

// Ne^'u la` che^' ddo^. bie^n di.ch unicode...
#ifdef _UNICODE

	//Ghi che^' ddo^. unicode
	if (m_nFlags & CStdioFileEx::modeWriteUnicode)
	{
		// Write in byte mode
		CFile::Write(lpsz, lstrlen(lpsz) * sizeof(wchar_t));
	}
	// Kho^ng pha?i ghi che^' ddo^. unicode
	else
	{
		int		nChars = lstrlen(lpsz) + 1;				
		int		nBufferSize = nChars * sizeof(char);
		wchar_t*	pszUnicodeString	= new wchar_t[nChars]; 
		char	*	pszMultiByteString= new char[nChars];  
		int		nCharsWritten = 0;

		// Copy string to Unicode buffer
		lstrcpy(pszUnicodeString, lpsz);

		// Get multibyte string
		nCharsWritten = 
			GetMultiByteStringFromUnicodeString(pszUnicodeString, pszMultiByteString, nBufferSize, GetACP());
		
		if (nCharsWritten > 0)
		{
			
			// Do byte-mode write using actual chars written (fix by Howard J Oh)
			CFile::Write((const void*)pszMultiByteString,
				nCharsWritten*sizeof(char));
		}

		if (pszUnicodeString && pszMultiByteString)
		{
			delete [] pszUnicodeString;
			delete [] pszMultiByteString;
		}
	}
// Kho^ng pha?i bie^n di.ch che^' ddo^. unicode
#else
	//Ghi che^' ddo^. unicode
	if (m_nFlags & CStdioFileEx::modeWriteUnicode)
	{
		int		nChars = lstrlen(lpsz) + 1;	 // Why plus 1? Because yes
		int		nBufferSize = nChars * sizeof(wchar_t);
		wchar_t*	pszUnicodeString	= new wchar_t[nChars];
		char	*	pszMultiByteString= new char[nChars]; 
		int		nCharsWritten = 0;
		
		// Copy string to multibyte buffer
		lstrcpy(pszMultiByteString, lpsz);

		nCharsWritten =
			GetUnicodeStringFromMultiByteString(pszMultiByteString,
			pszUnicodeString, nChars, GetACP());
		
		if (nCharsWritten > 0)
		{
			//   CFile::Write(pszUnicodeString, lstrlen(lpsz) * sizeof(wchar_t));

			// Write in byte mode. Write actual number of chars written * bytes (fix by Howard J Oh)
			CFile::Write(pszUnicodeString, nCharsWritten*sizeof(wchar_t));
		}
		else
		{
			ASSERT(false);
		}

		if (pszUnicodeString && pszMultiByteString)
		{
			delete [] pszUnicodeString;
			delete [] pszMultiByteString;
		}
	}
	//kho^ng pha?i ghi che^' ddo^. unicode
	else
	{
		
		// Do byte-mode write. This avoids annoying "interpretation" of \n's as	\r\n
		CFile::Write((const void*)lpsz, lstrlen(lpsz)*sizeof(char));
	}

#endif
}

UINT CStdioFileEx::ProcessFlags(const CString& sFilePath, UINT& nOpenFlags)
{
	m_bIsUnicodeText = false;

	// If we have writeUnicode we must have write or writeRead as well
#ifdef _DEBUG
	if (nOpenFlags & CStdioFileEx::modeWriteUnicode)
	{
		ASSERT(nOpenFlags & CFile::modeWrite || nOpenFlags & CFile::modeReadWrite);
	}
#endif

	// If reading in text mode and not creating... ; fixed by Dennis Jeryd 6/8/03
	if (nOpenFlags & CFile::typeText && !(nOpenFlags & CFile::modeCreate) && !(nOpenFlags & CFile::modeWrite ))
	{
		m_bIsUnicodeText = IsFileUnicode(sFilePath);

		// If it's Unicode, switch to binary mode
		if (m_bIsUnicodeText)
		{
			nOpenFlags ^= CFile::typeText;
			nOpenFlags |= CFile::typeBinary;
		}
	}

	m_nFlags = nOpenFlags;

	return nOpenFlags;
}


/*static*/ bool CStdioFileEx::IsFileUnicode(const CString& sFilePath)
{
	CFile				file;
	bool				bIsUnicode = false;
	wchar_t			cFirstChar;
	CFileException	exFile;

	// Open file in binary mode and read first character
	if (file.Open(sFilePath, CFile::typeBinary | CFile::modeRead, &exFile))
	{
		// If byte is Unicode byte-order marker, let's say it's Unicode
		if (file.Read(&cFirstChar, sizeof(wchar_t)) > 0 && cFirstChar == (wchar_t)nUNICODE_BOM)
		{
			bIsUnicode = true;
		}

		file.Close();
	}
	else
	{
		// Handle error here if you like
	}

	return bIsUnicode;
}

unsigned long CStdioFileEx::GetCharCount()
{
	int				nCharSize;
	unsigned long	nByteCount, nCharCount = 0;

	if (m_pStream)
	{
		// Get size of chars in file
		nCharSize = m_bIsUnicodeText ? sizeof(wchar_t): sizeof(char);

		// If Unicode, remove byte order mark from count
		nByteCount = GetLength();
		
		if (m_bIsUnicodeText)
		{
			nByteCount = nByteCount - sizeof(wchar_t);
		}

		// Calc chars
		nCharCount = (nByteCount / nCharSize);
	}

	return nCharCount;
}


int CStdioFileEx::GetUnicodeStringFromMultiByteString(IN char * szMultiByteString, OUT wchar_t* szUnicodeString, IN OUT int& nUnicodeBufferSize, IN UINT nCodePage)
{
	bool		bOK = true;
	int		nCharsWritten = 0;
		
	if (szUnicodeString && szMultiByteString)
	{
		// If no code page specified, take default for system
		if (nCodePage == -1)
		{
			nCodePage = GetACP();
		}

		try 
		{
			// Zero out buffer first. NB: nUnicodeBufferSize is NUMBER OF CHARS, NOT BYTES!
			memset((void*)szUnicodeString, '\0', sizeof(wchar_t) *
				nUnicodeBufferSize);

			nCharsWritten = MultiByteToWideChar(nCodePage,MB_PRECOMPOSED,szMultiByteString,-1,szUnicodeString,nUnicodeBufferSize);
		}
		catch(...)
		{
			TRACE(_T("Controlled exception in MultiByteToWideChar!\n"));
		}
	}

	// Now fix nCharsWritten
	if (nCharsWritten > 0)
	{
		nCharsWritten--;
	}
	
	ASSERT(nCharsWritten > 0);
	return nCharsWritten;
}


int CStdioFileEx::GetMultiByteStringFromUnicodeString(wchar_t * szUnicodeString, char* szMultiByteString, 
																			short nMultiByteBufferSize, UINT nCodePage)
{
	BOOL		bUsedDefChar	= FALSE;
	int		nCharsWritten = 0;

	if (szUnicodeString && szMultiByteString) 
	{
		
		memset((void*)szMultiByteString, '\0', nMultiByteBufferSize);
		
	
		if (nCodePage == -1)
		{
			nCodePage = GetACP();
		}

		try 
		{
			nCharsWritten = WideCharToMultiByte(nCodePage, WC_COMPOSITECHECK | WC_SEPCHARS,
							szUnicodeString,-1, szMultiByteString, nMultiByteBufferSize, sDEFAULT_UNICODE_FILLER_CHAR, &bUsedDefChar);
		}
		catch(...) 
		{
			TRACE(_T("Controlled exception in WideCharToMultiByte!\n"));
		}
	} 


	if (nCharsWritten > 0)
	{
		nCharsWritten--;
	}
	
	return nCharsWritten;
}
