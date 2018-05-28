#include "stdafx.h"
#include "typedef.h"
#include "resource.h"


CharsetInfo CharsetText[]={{_T("TCVN3"),	ID_KEY_TCVN3,_T("01 - TCVN3")},

						{_T("Vietware_F"),	ID_KEY_VIETWAREF,_T("02 - Vietware_F")},
						{_T("VIQR"),		ID_KEY_VIQR,_T("03 - VIQR")},
						{_T("Vietware_X"),	ID_KEY_VIETWAREX,_T("04 - Vietware_X")},
						{_T("VNI Windows")	,ID_KEY_VNI,_T("05 - VNI Windows")},
						{_T("Unicode"),		ID_KEY_UNICODE,_T("06 - Unicode")},
						{_T("BKHCM2"),		ID_KEY_BKHCM2,_T("07 - BKHCM2")},
						{_T("BKHCM1"),		ID_KEY_BKHCM1,_T("08 - BKHCM1")},
						{_T("VPS"),			ID_KEY_VPS,_T("09 - VPS")},
						{_T("VISCII"),		ID_KEY_VISCII,_T("10 - VISCII")},
					//	{_T("WINDOW CP 1258"),		ID_KEY_WINCP1258,_T("11 - WINDOW CP 1258")}

						};

TypingInfo InputMethod[] = {{_T("TELEX"), ID_TELEX_TYPING},
							{_T("VNI"),   ID_VNI_TYPING}};

TCHAR* languageArray[]={_T("Vietnamese-English"),
						_T("Vietnamese-France"),
						_T("Vietnamese-Germany"),
						//_T("VietNam-VietNam"),
					   _T("English-Vietnamese"),
						_T("France-Vietnamese"),
						_T("Germany-Vietnamese"),};



						