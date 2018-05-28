// Speak.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Speak.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;

}

HRESULT  InitSapi()
{
    HRESULT                 hr;
    
    hr = m_cpVoice.CoCreateInstance( CLSID_SpVoice );

    return hr;
}





