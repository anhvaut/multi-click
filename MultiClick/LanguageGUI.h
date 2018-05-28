#ifndef  __LANGUAGE_GUI_H
#define __LANGUAGE_GUI_H


//**
// Liet ke cac Item va text tuong ung cua About dialog
//**
struct AuthorDlgItem{
	UINT   id;
	char *text;
};

AuthorDlgItem m_AuthorDlgItem[][10];
void changeAuthorDlgGUI(HWND hwnd,int index);

//**
//* Liet ke cac Item va text tuong ung cua Setting dialog
//**
struct SettingDlgItem{
	UINT   id;
	char *text;
};
SettingDlgItem m_SettingDlgItem[][13];
void changeSettingDlgGUI(HWND hwnd,int index);

//**
//combobox so^? ra menu cho.n ngo^n ngu~ trong SettingDlg
//**
struct SettingDlgCombobox{ 
	UINT   id;
	char *text;
};
SettingDlgCombobox m_SettingDlgCombobox[][6];
void changeSettingDlgComboboxGUI(int index);



//// TreePropSheet
struct TreePropSheetGUI{ 
	UINT   id;
	char *text;
};
TreePropSheetGUI m_TreePropSheetGUI[][3];
void changeTreePropSheetGUI(HWND hwnd,int index);


////ReadDlg
struct ReadDlgGUI{ 
	UINT   id;
	char *text;
};
ReadDlgGUI m_ReadDlgGUI[][5];
void changeReadDlgGUI(HWND hwnd,int index);

///ServerDlg
struct ServerDlgGUI{ 
	UINT   id;
	char *text;
};
ServerDlgGUI m_ServerDlgGUI[][4];
void changeServerDlgGUI(HWND hwnd,int index);








#endif
