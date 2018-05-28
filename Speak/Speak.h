#ifndef  __SPEAK_H
#define __SPEAK_H

 CComPtr<ISpVoice>   m_cpVoice;
 CComPtr<ISpAudio>   m_cpOutAudio;
HRESULT     InitSapi();


#endif
