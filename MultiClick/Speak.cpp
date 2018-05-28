#include "stdafx.h"
#include "Speak.h"

 


    CComPtr<ISpVoice>   m_cpVoice;
    CComPtr<ISpAudio>   m_cpOutAudio;
	ISpVoice* m_pVoice1;
/*
* Kho+?i ddo.ng chu+o+ng tri`nh do.c
*/
HRESULT initSapi()
{
    HRESULT                 hr;
    
    hr = m_cpVoice.CoCreateInstance( CLSID_SpVoice );

    return hr;
}


/*
* Ngu+`ng do.c mo.t doa.n text
*/
void stop(){
    HRESULT hr = m_cpVoice->Speak( NULL, SPF_PURGEBEFORESPEAK, 0 );

    if( FAILED( hr ) )
    {
					MessageBox(NULL,_T("stop error"),_T("error"),MB_OK);
    }
}

/*
* Do.c mo^.t doa.n text
*/

void   speakText(CString text)
{
	/*
   	HRESULT             hr = S_OK;
	m_cpVoice->Speak( text, SPF_ASYNC, 0 );
	if( FAILED( hr ) )
		{
			MessageBox(NULL,_T("speak error"),_T("error"),MB_OK);
		}
	hr = m_cpVoice->Resume();      
	if( FAILED( hr ) )
	{
			MessageBox(NULL,_T("speak resume error"),_T("error"),MB_OK);
	}
	*/

	ISpVoice * pVoice = NULL;

    if (FAILED(CoInitialize(NULL)))
	{
		//AfxMessageBox("Error to intiliaze COM");
        return;
	}

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
		
	
        hr = pVoice->Speak(text.AllocSysString(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    CoUninitialize();
}
/*
* thie^'t la^.p to^'c do^. do.c  doa.n text
*/
void setSpeakRate(long i){
	 m_cpVoice->SetRate(i);
}

void setVolume(long i){
    m_cpVoice->SetVolume(i);
}

/////////////////////////////////////////////////////////////////
HRESULT VoiceChange()
{
	
    HRESULT         hr = S_OK;
	/*
    GUID*           pguidAudioFormat = NULL;
    int             iFormat = 0;

	HWND voices;
	
    // Get the token associated with the selected voice
    ISpObjectToken* pToken = SpGetCurSelComboBoxToken( (HWND)"LH Michelle");


    //Determine if it is the current voice
    CComPtr<ISpObjectToken> pOldToken;
    hr = m_cpVoice->GetVoice( &pOldToken );

    if (SUCCEEDED(hr))
    {
        if (pOldToken != pToken)
        {        
           // ngu+`ng do.c gio.ng do.c cu~
            hr = m_cpVoice->Speak( NULL, SPF_PURGEBEFORESPEAK, 0);
            // chuye^?n sang gio.ng do.c mo+'i
            if (SUCCEEDED (hr) )
            {
                hr = m_cpVoice->SetVoice( pToken );
            }
        }
    }
*/
    return hr;
}

