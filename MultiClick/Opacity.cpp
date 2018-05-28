#include "stdafx.h"
#include "Opacity.h"

/////////opacity
void Opacity::SetWindowLayered (const HWND hwnd)
{
  long lExStyle = GetWindowLong (hwnd, GWL_EXSTYLE);
  lExStyle = lExStyle | 800000 & ~WS_EX_CONTEXTHELP & ~WS_EX_RIGHT;
  SetWindowLong (hwnd, GWL_EXSTYLE, lExStyle);
}

void Opacity::SetWindowOpacity (const HWND hwnd,const int iOpacity)
{
  typedef BOOL (FAR PASCAL* SET_LAYERED_WINDOW_ATTRIBUTES) (HWND, COLORREF, BYTE, DWORD);
  
  HMODULE hmodule = GetModuleHandle (TEXT("User32.dll"));
  SET_LAYERED_WINDOW_ATTRIBUTES pSetLayeredWindowAttributes;
  
  if (hmodule != 0)
    pSetLayeredWindowAttributes = reinterpret_cast <SET_LAYERED_WINDOW_ATTRIBUTES> (GetProcAddress (hmodule, "SetLayeredWindowAttributes"));

  if (pSetLayeredWindowAttributes != 0)
    pSetLayeredWindowAttributes (hwnd, 0, iOpacity, 2);
}

///////////////////////////////////