#ifndef _TYPEDEF_H
#define _TYPEDEF_H

//============Point================
//============title point
#define TITLE_TOP	185
#define TITLE_LEFT  20
//=================================


#define CTRL_RIGHT_CLICK   0
#define SHIFT_RIGHT_CLICK  1
#define RIGHT_CLICK		   2

#define MODE_SWITCH	6
#define VIETNAMESE_ENGLISH 0
#define VIETNAMESE_FRANCE  1
#define VIETNAMESE_GERMANY 2
//#define VIETNAMESE_VIETNAMESE 3
#define ENGLISH_VIETNAMESE 3
#define FRANCE_VIETNAMESE  4
#define GERMANY_VIETNAMESE 5

//nho sua lai languageArray , neu co them vao ngon ngu moi




//==========keyboard
#define NUM_CHARSET		10

#define NUM_TYPING		2
#define TELEX_TYPING	0
#define VNI_TYPING		1

#define WOVEL		 1	//have 72 wovel _8bitwovel
#define TONE_MARK    13
#define DOUBLE_MARK  18
#define BREVE_MARK   27
#define TELEX_SHORTKEY 29



#define isWovel(x)(1<=x&&x<13)
#define isToneMark(x)(13<=x&&x<18)
#define isDoubleMark(x)(18<=x&&x<27)
#define isBreveMark(x)(x>=27&&x<29)
#define isTelexShortKey(x)(x>=29)
#define isVniDoubleMark(x)(x=='6'||x=='9')
#define isVniBreveMark(x)(x=='7'||x=='8')

#define NUM_8bit	2

#define UNICODE_CHARSET  0
#define _8BIT_CHARSET   -1
#define _16BIT_CHARSET   1
#define VIQR_CHARSET     2

#define ALT_Z		1	//ALT+Z
#define CTRL_SHIFT	0   //CTRL+SHIFT

#define TCVN3		0
#define VIQR		2
#define VNI			4
//#define UNICODE		5 
//=================================
#define UPDOWN_X	285	
#define UP_Y		50
#define DOWN_Y		150
//=================================
struct CharsetInfo{
		TCHAR *charsetText;
		UINT id;
		TCHAR *displayText;
};
struct TypingInfo{
		TCHAR *inputText;
		UINT id;
};

CharsetInfo CharsetText[];
TypingInfo InputMethod[];
TCHAR* languageArray[];

#endif