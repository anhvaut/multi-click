#define DllExport  __declspec( dllexport )
#define MOUSE_PROC 8	//MouseProc Message will be sent to main Wind
#define BUFFER_COUNT 256
#define TH1   0
#define TH2	1
#define TH3	3
#define TH4   4

#define CTRL_RIGHT_CLICK   0
#define SHIFT_RIGHT_CLICK  1
#define RIGHT_CLICK		         2


void SetLookMode(int);
void SetTextMode(int);
int GetLookMode(WPARAM wParam);
void SetHHook(HWND,HHOOK);
//void SetVowel(unsigned char);


LRESULT CALLBACK MyMouseProc(int,WPARAM,LPARAM);
CHAR *CALLBACK GetAnsiString() ;
WCHAR *CALLBACK GetUnicodeString() ;