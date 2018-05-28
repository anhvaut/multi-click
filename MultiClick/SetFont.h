/*----------------------
   EZFONT.H header file
  ----------------------*/

HFONT CreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes) ;

#define ATTR_BOLD          1
#define ATTR_ITALIC        2
#define ATTR_UNDERLINE     4
#define ATTR_STRIKEOUT     8
