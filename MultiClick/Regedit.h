#ifndef  __MY_REGEDIT_H
#define __MY_REGEDIT_H

class CRegeditInfo
{
public:
	///*****************
	//autoStart	 =0 : bo? che^' do^. kho^ng tu+. kho+?i ddo^.ng cu`ng windows
	//			 =1 : ba^.t che^' do^.tu+. kho+?i ddo^.ng cu`ng windows
	///*****************
	DWORD autoStart;

	///*****************
	//onAutoLook	 =0 : ta('t che^' ddo^. tra tu+` ba(`ng click and see
	//				 =1 : ba^.t
	///*****************
	DWORD onAutoLook;

	///*****************
	//	autoLook	 =0 : tra tu+` ba(`ng CTRL + RIGHT_CLICK
	//				 =1 : tra tu+` ba(`ng SHIFT + RIGHT_CLICK 
	//				 =2 : tra tu+` ba(`ng RIGHT_CLICK 
	///*****************
	DWORD autoLook;
	

	DWORD backcolor;
	DWORD titlecolor;
	DWORD textcolor;

	//Regedit cho bo^. go~
	DWORD inputMethod;
	DWORD charset;
	DWORD switchKey;
	DWORD VietNamese;//=1:VietNam;=0:English
	DWORD notFreeMarking;
	DWORD uClipboard;
	DWORD vietNameseOn;
	DWORD onlyText;//=1 Ho tro word,pdf
	DWORD lookupOnAuto;
	//////////////////

	///*****************
	//guiLanguage=0 : giao die^.n co' ngo^n ngu+~ tie^'ng anh
	//			 =1 : giao die^.n co' ngo^n ngu+~ tie^'ng pha'p
	//			 =2 : giao die^.n co' ngo^n ngu+~ tie^'ng ddu+'c
	//			 =3 : giao die^.n co' ngo^n ngu+~ tie^'ng vie^.t
	//			 =4 : giao die^.n co' ngo^n ngu+~ tie^'ng Nga
	//			 =5 : giao die^.n co' ngo^n ngu+~ tie^'ng Nauy
	///*****************
	DWORD guiLanguage;
	

	///*****************
	//kindDictionary=0 : bo^. tu+. ddie^?n lie^n quan dde^'n tie^'ng vie^.t va` english
	//			    =1 : tie^'ng vie^.t va` tie^'ng pha'p
	//			    =2 : tie^'ng vie^.t va` tie^'ng ddu+'c
	//			    =3 : tie^'ng vie^.t va` tie^'ng tie^'ng vie^.t
	//				=4 : tie^'ng vie^.t va` tie^'ng Nga
	//				=5 : tie^'ng vie^.t va` tie^'ng Na uy
	///*****************
	DWORD kindDictionary;
	

	DWORD onlineLookup;

	DWORD autoUpdate;//=0 khong tu update, =1 tu dong update phien ban moi

	//DWORD url;//luu dia chi url cua server 
	

public:
	CRegeditInfo(){
		autoStart=0;
		kindDictionary=0;
		autoLook=0;
		onAutoLook=1;
		backcolor=0x009bbad6;
		titlecolor=0;
		textcolor=0;
		uClipboard=1;
		onlineLookup=0;
		guiLanguage=3;
		autoUpdate=1;
		//url=(LPBYTE)_T("http://multidict.net");
	}
	~CRegeditInfo(){
	}
	int setValue();
	int getValue();
	int enableAutoStart(int);

	
};//end RegeditInfo

#endif
