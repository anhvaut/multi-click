#ifndef  __SPEAK_H
#define __SPEAK_H

HRESULT initSapi();
void stop();
void   speakText(CString text);
void setSpeakRate(long i);
void setVolume(long i);
HRESULT VoiceChange();

#endif
