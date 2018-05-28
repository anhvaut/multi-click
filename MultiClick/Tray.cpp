
#include "stdAfx.h"
#include "tray.h"
#include "resource.h"
#include "Regedit.h"
#include "typedef.h"
#include "UTF8.h"


extern CRegeditInfo regedit;

               
void  CreateMenuItemList();              
BOOL  SetIcon(CString pszTip, int nAction);                         
BOOL  IsItemChecked(UINT IDItem);



// Liet ke cac Item va text tuong ung cua Menu

//index		 =0 : giao die^.n co' ngo^n ngu+~ tie^'ng anh
//			 =1 : giao die^.n co' ngo^n ngu+~ tie^'ng pha'p
//			 =2 : giao die^.n co' ngo^n ngu+~ tie^'ng ddu+'c
//			 =3 : giao die^.n co' ngo^n ngu+~ tie^'ng vie^.t
//			 =4 : giao die^.n co' ngo^n ngu+~ tie^'ng Nga
//			 =5 : giao die^.n co' ngo^n ngu+~ tie^'ng Nauy

void changeMenuGUI(int index);

//POPUP MENU
HMENU hMenu;
// load menu
CNewMenu owermenu,keyonMenu,autolookMenu,lookuponMenu,onlineMenu,dictionaryMenu;

HWND  hwnd; 
HINSTANCE hinst;
CWnd* cwnd;

//TRAY
bool  bTray;

void SystemTray::OnNotifyTray(LPARAM lParam)
{

 // Right click, show the menu
 if(lParam == WM_RBUTTONDOWN) 
 {
	
	

	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(hwnd);
	owermenu.TrackPopupMenu(TPM_RIGHTALIGN,pt.x,pt.y-20,cwnd);  
	

 }else{
	 
	 switch(lParam){
	 case WM_LBUTTONDBLCLK:
		 if(OnAutoLook()){
			SetIcon("Diable",2);
			CheckAutoLookOff();
			//SetKeyOff();
			//EnableMenuItem(hMenu,ID_KEY_ON,true);
			
		 }else{
			SetIcon("Diable",3);
			CheckAutoLookOn();
			//SetKeyOn();
			//EnableMenuItem(hMenu,ID_KEY_ON,false);
		 }
		 break;
	 case WM_LBUTTONDOWN:
		POINT pt;
		GetCursorPos(&pt);
		SetForegroundWindow(hwnd);
		owermenu.TrackPopupMenu(TPM_RIGHTALIGN,pt.x,pt.y-20,cwnd);  
		 break;
	 case WM_LBUTTONUP:
		
		break;
	 default:
		 break;

	 }

	
   }//end else

 	
 PostMessage(hwnd,WM_NULL,0,0);
}

void SystemTray::OnDestroyTray()
{
	owermenu.DestroyMenu();
    SetIcon("", 0);
}

BOOL SystemTray::TRAY_IsInTray()
{
	return bTray; 
}

void SystemTray::TRAY_Menu_Show()
{			
	POINT pt;// point structure
	GetCursorPos(&pt);// get the cursors position
	SetForegroundWindow(hwnd);// set the foreground window
	owermenu.TrackPopupMenu(TPM_RIGHTALIGN,pt.x,pt.y,cwnd);// track the popup
	PostMessage(hwnd,WM_NULL,0,0);// post a null message	    
}

void SystemTray::TRAY_Init(HWND hWnd,HINSTANCE hInst,CWnd* cWnd)
{

    hwnd = hWnd;
	hinst=hInst;
	cwnd=cWnd;
   

	SetIcon("InfoDict 2.0", 1);
	CreateMenuItemList();
	SetRegeditVal();
	
	
} 

void CreateMenuItemList()
{
	
	regedit.getValue();
	changeMenuGUI(regedit.guiLanguage);
		
}



BOOL SetIcon(CString pszTip , int nAction) 
{              
UINT  uIcon; // Icon ID buffer
DWORD dMsg;  // Message buffer (ADD/DELETE/MODIFY)
NOTIFYICONDATA ni;

	ni.cbSize = sizeof(ni);
	ni.uID = 0;
	lstrcpyn(ni.szTip, pszTip, sizeof(ni.szTip)); 
	ni.hWnd = hwnd;
	ni.uFlags = NIF_MESSAGE | NIF_TIP | NIF_ICON; // We want to use icon, tip, and callback message
	ni.uCallbackMessage = WM_NOTIFYICONTRAY;      // Our custom callback message (WM_APP + 1)
    
    switch (nAction){
        case 0:// Remove tray icon
                return Shell_NotifyIcon(NIM_DELETE, &ni);
           break; 
        case 1://Add icon in tray
                uIcon=IDR_MAINFRAME; // Set tray icon
                dMsg=NIM_ADD; // Add tray icon        
           break;
        case 2:// Modify current icon in tray
                uIcon=IDI_DISABLE; // Set new tray icon	
                dMsg=NIM_MODIFY; // Modify tray icon     
           break;    
	    case 3:// Modify current icon in tray
                uIcon=IDR_MAINFRAME; // Set new tray icon	
                dMsg=NIM_MODIFY; // Modify tray icon     
           break;      
       
     }
     
     //Load selected icon
     ni.hIcon = (HICON)LoadIcon((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 
                                                       MAKEINTRESOURCE(uIcon));	
     // Windooows, ohohooo, we have changed icon! :)                                                
     return Shell_NotifyIcon(dMsg, &ni);       
     
     
}


DWORD SystemTray::CheckItem(UINT IDItem,BOOL Checked)
{
  UINT uCheck;
  uCheck = Checked ? MF_CHECKED : MF_UNCHECKED; //retrieve state (checked/unchecked)

  return owermenu.CheckMenuItem(IDItem, MF_BYCOMMAND|uCheck);
}

BOOL IsItemChecked(UINT IDItem)
{
DWORD uCheck;

  uCheck = owermenu.CheckMenuItem( IDItem, MF_BYCOMMAND);
  
  if (uCheck != -1){
     return (uCheck == MF_CHECKED) ? 1 : 0;
  }
  
return 0;
}

void SystemTray::OnEndKey(){
	regedit.setValue();
	OnDestroyTray();
	DestroyWindow(hwnd);
	
}
void SystemTray::OnEndKey1(HWND hwnd){
	regedit.setValue();
	OnDestroyTray();
	DestroyWindow(hwnd);
	
}

/*
*  xu+? li' su+. kie^.n cho menu : ba^.t tra tu+` tu+. ddo^.ng le^n
*/
void SystemTray::CheckAutoLookOn(){
if(!IsItemChecked(ID_AUTOLOOK_ON)){
	CheckItem(ID_AUTOLOOK_ON,TRUE);

	
	autolookMenu.InsertMenu(1, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
	autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
	autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
	//autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_ONLYTEXT, _T("Word, Acrobat"));

	SetRegeditVal();
}
	
}

void SystemTray::CheckAutoLookOnF(){

	CheckItem(ID_AUTOLOOK_ON,TRUE);

	
}
/*
*  xu+? li' su+. kie^.n cho menu : ta('t tra tu+` tu+. ddo^ng 
*/
void SystemTray::CheckAutoLookOff(){
	CheckItem(ID_AUTOLOOK_ON,FALSE);
	
	autolookMenu.DeleteMenu(1,MF_BYPOSITION);
	autolookMenu.DeleteMenu(1,MF_BYPOSITION);
	autolookMenu.DeleteMenu(1,MF_BYPOSITION);
	autolookMenu.DeleteMenu(1,MF_BYPOSITION);
	//autolookMenu.DeleteMenu(1,MF_BYPOSITION);
	//autolookMenu.DeleteMenu(1,MF_BYPOSITION);




}

int SystemTray::OnAutoLook(){
	return (IsItemChecked(ID_AUTOLOOK_ON));
}

/*
*  Xu+? li' cho vie^c cho.n che^' ddo^. Tra Tu+` 
*/
void SystemTray::chooseModeLook1(){
		regedit.autoLook=CTRL_RIGHT_CLICK;
		//(pSetLookMode)(CTRL_RIGHT_CLICK);
		CheckItem(ID_CTRL_CLICK,TRUE);
		CheckItem(ID_SHIFT_CLICK,FALSE);
		CheckItem(ID_CLICK,FALSE);
}

void SystemTray::chooseModeLook2(){
		regedit.autoLook=SHIFT_RIGHT_CLICK;
		//(pSetLookMode)(SHIFT_RIGHT_CLICK);
		CheckItem(ID_CTRL_CLICK,FALSE);
		CheckItem(ID_SHIFT_CLICK,TRUE);
		CheckItem(ID_CLICK,FALSE);
}
void SystemTray::chooseModeLook3(){
		regedit.autoLook=RIGHT_CLICK;
		//(pSetLookMode)(RIGHT_CLICK);
		CheckItem(ID_CTRL_CLICK,FALSE);
		CheckItem(ID_SHIFT_CLICK,FALSE);
		CheckItem(ID_CLICK,TRUE);
	
}





void SystemTray::SetRegeditVal(){
	regedit.getValue();
	
	// kie^?m tra che^' ddo^. tra tu+` co' trong regedit
	// check va`o menu
	if(regedit.onAutoLook)
		CheckAutoLookOnF();
	else CheckAutoLookOff();

	// kie^?m tra loa.i se~ du`ng tra tu+` co' trong regedit
	if(regedit.autoLook==CTRL_RIGHT_CLICK)
		chooseModeLook1();
	else if(regedit.autoLook==SHIFT_RIGHT_CLICK)
		chooseModeLook2();
	else if(regedit.autoLook==RIGHT_CLICK)
		chooseModeLook3();

  
	// regedit cho bo^. go~
	/*
	for(int i=0;i<NUM_CHARSET;i++){
			if(i==regedit.charset){
				CheckItem(CharsetText[i].id,TRUE);
				regedit.charset=i;
			}
			else
				CheckItem(CharsetText[i].id,FALSE);
	}
	
	if(!regedit.inputMethod) CheckItem(ID_TELEX_TYPING,TRUE);
	else CheckItem(ID_VNI_TYPING,TRUE);
	*/

	
	if(regedit.onlyText) CheckItem(ID_ONLYTEXT,TRUE);
	
	
	if(regedit.kindDictionary==0)  CheckItem(ID_LOOKUPON_ENGLISH,TRUE);
	if(regedit.kindDictionary==1)  CheckItem(ID_LOOKUPON_FRANCE,TRUE);
	if(regedit.kindDictionary==2)  CheckItem(ID_LOOKUPON_GERMANY,TRUE);
	if(regedit.kindDictionary==3)  CheckItem(ID_LOOKUPON_VIETNAMESE,TRUE);
	if(regedit.kindDictionary==4)  CheckItem(ID_LOOKUPON_RUSSIA,TRUE);
	if(regedit.kindDictionary==5)  CheckItem(ID_LOOKUPON_NAUY,TRUE);

	if(regedit.onlineLookup)  CheckItem( ID_LOOKUPONLINE,TRUE);
	else CheckItem( ID_LOOKUPONLINE,FALSE);


}

int SystemTray::isOnlyText(){
	return (IsItemChecked(ID_ONLYTEXT));
}
int SystemTray::onLookOnAuto(){
	return (IsItemChecked(ID_LOOKUPON_AUTOMATIC));
}


void changeMenuGUI(int index){
	//char *st="Tự Điển Online";
	 
	
	 if(index==0){
		 onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();


			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, _T("Online Dictionary    "));
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, _T("Update New version "));
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, _T("Online Lookup     "));
			

			

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, _T("     ON     "));
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH, _T("English <--> Vietnamese"));
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, _T("France <--> Vietnamese"));
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, _T("Germany <--> Vietnamese"));
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE, _T("Vietnamese <--> Vietnamese"));
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, _T("Russia --> Vietnamese"));
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, _T("Nauy --> Vietnamese"));


				
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV, _T("English - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV, _T("France - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV, _T("Germany - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, _T("Russia - Vietnamese Dictionary"));
			
			
			
			owermenu.CreatePopupMenu();
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, _T("Online Features"));
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu, _T("Autolook ..."));
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, _T("Lookup on"));
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, _T("Local Dictionary "));
			owermenu.InsertODMenu(4,_T("InfoKey"),MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			owermenu.InsertODMenu(5,_T("Setting"),MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			owermenu.InsertODMenu(6,_T("Help"),MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			owermenu.InsertODMenu(7,_T("Exit"),MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
	  else if(index==1){//tieng phap
			onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();


			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, _T("Online Dictionary    "));
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, _T("Update Dictionary "));
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, _T("Online Lookup     "));
			

			

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, _T("     ON     "));
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH, _T("English <--> Vietnamese"));
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, _T("France <--> Vietnamese"));
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, _T("Germany <--> Vietnamese"));
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE, _T("Vietnamese <--> Vietnamese"));
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, _T("Russia --> Vietnamese"));
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, _T("Nauy --> Vietnamese"));
			
			
				
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV, _T("English - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV, _T("France - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV, _T("Germany - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, _T("Russia - Vietnamese Dictionary"));
			
			
			
			owermenu.CreatePopupMenu();
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, _T("Online Features"));
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu, _T("Autolook ..."));
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, _T("Lookup on"));
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, _T("Local Dictionary "));
			owermenu.InsertODMenu(4,_T("InfoKey"),MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			owermenu.InsertODMenu(5,_T("Setting"),MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			owermenu.InsertODMenu(6,_T("Help"),MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			owermenu.InsertODMenu(7,_T("Exit"),MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
	  else if(index==2){//tieng duc
			onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();


			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, _T("Online Dictionary    "));
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, _T("Update New version "));
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, _T("Online Lookup     "));
			

			

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, _T("     ON     "));
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH, _T("English <--> Vietnamese"));
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, _T("France <--> Vietnamese"));
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, _T("Germany <--> Vietnamese"));
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE, _T("Vietnamese <--> Vietnamese"));
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, _T("Russia --> Vietnamese"));
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, _T("Nauy --> Vietnamese"));
			
			
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV, _T("English - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV, _T("France - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV, _T("Germany - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, _T("Russia - Vietnamese Dictionary"));
			
			
			
			owermenu.CreatePopupMenu();
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, _T("Online Features"));
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu, _T("Autolook ..."));
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, _T("Lookup on"));
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, _T("Local Dictionary"));
			owermenu.InsertODMenu(4,_T("InfoKey"),MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			owermenu.InsertODMenu(5,_T("Setting"),MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			owermenu.InsertODMenu(6,_T("Help"),MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			owermenu.InsertODMenu(7,_T("Exit"),MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
	   else if(index==3){//tieng viet
			 onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();
			
			
			wchar_t unicode_string[256];
			Utf8_Unicode((BYTE*)"Tự Điển Trực Tuyến",unicode_string);
			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, unicode_string);
			
			Utf8_Unicode((BYTE*)"Cập Nhật Phiên Bản Mới",unicode_string);
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, unicode_string);
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			Utf8_Unicode((BYTE*)"Tra Từ Tự Động Trực Tuyến",unicode_string);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, unicode_string);
			

		

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			Utf8_Unicode((BYTE*)"Bật",unicode_string);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, unicode_string);
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			Utf8_Unicode((BYTE*)"Phím Ctrl Trái+Chuột Phải",unicode_string);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, unicode_string);
			Utf8_Unicode((BYTE*)"Shift+Chuột Phải",unicode_string);
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, unicode_string);
			Utf8_Unicode((BYTE*)"Chuột Phải",unicode_string);
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, unicode_string);
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			Utf8_Unicode((BYTE*)"Tiếng Anh <---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH,unicode_string);
			Utf8_Unicode((BYTE*)"Tiếng Pháp <---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, unicode_string);
			Utf8_Unicode((BYTE*)"Tiếng Đức <---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, unicode_string);
			Utf8_Unicode((BYTE*)"Tiếng Việt <---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE,unicode_string);
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			Utf8_Unicode((BYTE*)"Tiếng Nga ---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, unicode_string);
			Utf8_Unicode((BYTE*)"Tiếng Nauy ---> Tiếng Việt",unicode_string);
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, unicode_string);
			
			
			//wchar_t unicode_string[256];
			//Utf8_Unicode((BYTE*)"Tự Điển",unicode_string);
			Utf8_Unicode((BYTE*)"Tự Điển Anh Việt",unicode_string);
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV,unicode_string);
			Utf8_Unicode((BYTE*)"Tự Điển Pháp Việt",unicode_string);
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV,unicode_string);
			Utf8_Unicode((BYTE*)"Tự Điển Đức Việt",unicode_string);
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV,unicode_string);
			Utf8_Unicode((BYTE*)"Tự Điển Nga Việt",unicode_string);
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, unicode_string);
			
			
			
			
			owermenu.CreatePopupMenu();
			Utf8_Unicode((BYTE*)"Tính Năng Trực Tuyến",unicode_string);
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, unicode_string);
			Utf8_Unicode((BYTE*)"Tra Từ Tự Động",unicode_string);
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu,unicode_string);
			Utf8_Unicode((BYTE*)"Tra Từ Trên",unicode_string);
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, unicode_string);
			Utf8_Unicode((BYTE*)"Tự Điển offline",unicode_string);
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, unicode_string);
			Utf8_Unicode((BYTE*)"Bộ Gõ InfoKey",unicode_string);
			owermenu.InsertODMenu(4,unicode_string,MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			Utf8_Unicode((BYTE*)"Thiết Lập",unicode_string);
			owermenu.InsertODMenu(5,unicode_string,MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			Utf8_Unicode((BYTE*)"Trợ giúp",unicode_string);
			owermenu.InsertODMenu(6,unicode_string,MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			Utf8_Unicode((BYTE*)"Thoát",unicode_string);
			owermenu.InsertODMenu(7,unicode_string,MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
    else if(index==4){//tieng Nga
			onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();


			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, _T("Online Dictionary    "));
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, _T("Update New version "));
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, _T("Online Lookup     "));
			

			

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, _T("     ON     "));
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH, _T("English <--> Vietnamese"));
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, _T("France <--> Vietnamese"));
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, _T("Germany <--> Vietnamese"));
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE, _T("Vietnamese <--> Vietnamese"));
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, _T("Russia --> Vietnamese"));
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, _T("Nauy --> Vietnamese"));
			
			
			
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV, _T("English - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV, _T("France - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV, _T("Germany - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, _T("Russia - Vietnamese Dictionary"));
			
			
			
			owermenu.CreatePopupMenu();
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, _T("Online Features"));
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu, _T("Autolook ..."));
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, _T("Lookup on"));
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, _T("Local Dictionary"));
			owermenu.InsertODMenu(4,_T("InfoKey"),MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			owermenu.InsertODMenu(5,_T("Setting"),MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			owermenu.InsertODMenu(6,_T("Help"),MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			owermenu.InsertODMenu(7,_T("Exit"),MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
	 else if(index==5){//tieng Nauy
			onlineMenu.CreatePopupMenu();
			autolookMenu.CreatePopupMenu();
			lookuponMenu.CreatePopupMenu();
			dictionaryMenu.CreatePopupMenu();


			onlineMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARYONLINE, _T("Online Dictionary    "));
			onlineMenu.InsertMenu(1, MF_BYPOSITION , ID_UPDATEDICTONARY, _T("Update New version "));
			onlineMenu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
			onlineMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPONLINE, _T("Online Lookup     "));
			

		

			//autolookMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			autolookMenu.InsertMenu(0, MF_BYPOSITION , ID_AUTOLOOK_ON, _T("     ON     "));
			autolookMenu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
			autolookMenu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_CLICK, _T("Left Ctrl+Right Click"));
			autolookMenu.InsertMenu(3, MF_BYPOSITION , ID_SHIFT_CLICK, _T("Shift+Right Click"));
			autolookMenu.InsertMenu(4, MF_BYPOSITION , ID_CLICK, _T("Right Click"));
			//autolookMenu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
			//autolookMenu.InsertMenu(6, MF_BYPOSITION , ID_ONLYTEXT, _T("Word,acrobat..."));
			
			//lookuponMenu.InsertODMenu(0,_T("Config"),MF_BYPOSITION , ID_KEY_CONF,IDB_HELP);
			//lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_AUTOMATIC, _T("Normal"));
			lookuponMenu.InsertMenu(0, MF_BYPOSITION , ID_LOOKUPON_ENGLISH, _T("English <--> Vietnamese"));
			lookuponMenu.InsertMenu(1, MF_BYPOSITION , ID_LOOKUPON_FRANCE, _T("France <--> Vietnamese"));
			lookuponMenu.InsertMenu(2, MF_BYPOSITION , ID_LOOKUPON_GERMANY, _T("Germany <--> Vietnamese"));
			lookuponMenu.InsertMenu(3, MF_BYPOSITION , ID_LOOKUPON_VIETNAMESE, _T("Vietnamese <--> Vietnamese"));
			lookuponMenu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
			lookuponMenu.InsertMenu(5, MF_BYPOSITION , ID_LOOKUPON_RUSSIA, _T("Russia --> Vietnamese"));
			lookuponMenu.InsertMenu(6, MF_BYPOSITION , ID_LOOKUPON_NAUY, _T("Nauy --> Vietnamese"));
			
			
			
			dictionaryMenu.InsertMenu(0, MF_BYPOSITION , ID_DICTIONARY_ENGLISHV, _T("English - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(1, MF_BYPOSITION , ID_DICTIONARY_FRANCEV, _T("France - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(2, MF_BYPOSITION , ID_DICTIONARY_GERMANYV, _T("Germany - Vietnamese Dictionary"));
			dictionaryMenu.InsertMenu(3, MF_BYPOSITION , ID_DICTIONARY_NAUY_NV, _T("Russia - Vietnamese Dictionary"));
			
			
			
			owermenu.CreatePopupMenu();
			owermenu.AppendMenu(MF_POPUP, (UINT) onlineMenu.m_hMenu, _T("Online Features"));
			owermenu.AppendMenu(MF_POPUP, (UINT) autolookMenu.m_hMenu, _T("Autolook ..."));
			owermenu.AppendMenu(MF_POPUP, (UINT) lookuponMenu.m_hMenu, _T("Lookup on"));
			owermenu.AppendMenu(MF_POPUP, (UINT) dictionaryMenu.m_hMenu, _T("Local Dictionary"));
			owermenu.InsertODMenu(4,_T("InfoKey"),MF_BYPOSITION , ID_INFOKEY,IDB_INFOKEY);
			owermenu.InsertODMenu(5,_T("Setting"),MF_BYPOSITION , ID_PANEL,IDB_OPTION);
			owermenu.InsertODMenu(6,_T("Help"),MF_BYPOSITION , ID_OPEN_HELP,IDB_HELP);
			owermenu.InsertODMenu(7,_T("Exit"),MF_BYPOSITION , ID_END,IDB_MENU_CLOSE);
	
	

	
			//CNewMenu* pSubMenu = menu.AppendODPopupMenu(_T("NewMenu"));
			//pSubMenu->InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));;
			owermenu.SetMenuTitle(_T("InfoDict 2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	 }
	
	
}

