/*
* Phie^n Ba?n InfoDict 2.0
* Ta'c Gia? : Tra^`n The^' Vu~ & Huy`nh Thi. Le^. Thanh
* No+i Co^ng Ta'c : Sinh Vie^n Tru+o+`ng DDa.i Ho.c Ba'ch Khoa DDa` Na(~ng . 
*							   Khoa Co^ng Nghe^. Tho^ng Tin.
*/

#ifndef _TRAY_H
#define _TRAY_H

#define WM_NOTIFYICONTRAY (WM_APP + 1)

class SystemTray{
public:
	CNewMenu m_newSubMenu;
	void  TRAY_Init(HWND hwnd,HINSTANCE hInstance,CWnd* cWnd);              
	BOOL  TRAY_IsInTray(void);              
	void  TRAY_Menu_Show(void);             
	void  OnNotifyTray(LPARAM lParam);            
	void  OnDestroyTray(void);               

	
	void  OnEndKey();

	/*
	* Bat , tat che^' ddo^. tra tu tu ddo^.ng
	*/
	void CheckAutoLookOn();
	void CheckAutoLookOnF();
	void CheckAutoLookOff();

	int  OnAutoLook();//=0 kho^ng ba^.t tra tu+` , =1 ba^.t tra tu+`

	/*
	* Cho.n he^' ddo^. tra tu+`
	*/
	void chooseModeLook1();
	void chooseModeLook2();
	void chooseModeLook3();

	/*
	* doc gia tri trong regedit
	* check menu Item neu gia tri =1
	*/
	void SetRegeditVal();

	int isOnlyText();
	int onLookOnAuto();
	void OnEndKey1(HWND hwnd);
	

	DWORD CheckItem(UINT IDItem,BOOL Checked);

};//end SystemTray

#endif