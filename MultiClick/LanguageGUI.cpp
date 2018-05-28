#include "stdafx.h"
#include "LanguageGUI.h"
#include "resource.h"
#include "UTF8.h"
#include "SettingDlg.h"

AuthorDlgItem m_AuthorDlgItem[][10]={
								//tieng anh
								{
									{IDC_STATICM,"InfoDict was Written by two author:"},
									{IDC_STATIC1,"Name: Tran The vu"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Name: Huynh Thi Le Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"person support:"},
									{IDC_STATIC6,"Truong Ngoc Chau"},
									{IDC_STATIC7,"IT Faculty"},
									{IDC_STATIC8,"DaNang University Of Technology"},
									{IDC_STATIC9,""},
								},
								//
								//tieng Phap
								{
									{IDC_STATICM,"InfoDict was Written by two author:"},
									{IDC_STATIC1,"Name: Tran The vu"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Name: Huynh Thi Le Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"person support:"},
									{IDC_STATIC6,"Truong Ngoc Chau"},
									{IDC_STATIC7,"IT Faculty"},
									{IDC_STATIC8,"DaNang University Of Technology"},
									{IDC_STATIC9,""},
								},
								//tieng duc
							
								{
									{IDC_STATICM,"InfoDict was Written by two author:"},
									{IDC_STATIC1,"Name: Tran The vu"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Name: Huynh Thi Le Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"person support:"},
									{IDC_STATIC6,"Truong Ngoc Chau"},
									{IDC_STATIC7,"IT Faculty"},
									{IDC_STATIC8,"DaNang University Of Technology"},
									{IDC_STATIC9,""},
								},
								//tieng viet
				
								{
									{IDC_STATICM,"InfoDict  được viết bởi 2 tác giả:"},
									{IDC_STATIC1,"Tên: Trần Thế Vũ"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Tên: Huỳnh Thị Lệ Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"Với sự hướng dẫn:"},
									{IDC_STATIC6,"Giảng Viên : Trương Ngọc Châu"},
									{IDC_STATIC7,"Khoa Công Nghệ Thông Tin "},
									{IDC_STATIC8,"Đại Học Bách Khoa Đà Nẵng"},
									{IDC_STATIC9," "},
								},
								//tieng Nga
								
								{
									{IDC_STATICM,"InfoDict was Written by two author:"},
									{IDC_STATIC1,"Name: Tran The vu"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Name: Huynh Thi Le Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"person support:"},
									{IDC_STATIC6,"Truong Ngoc Chau"},
									{IDC_STATIC7,"IT Faculty"},
									{IDC_STATIC8,"DaNang University Of Technology"},
									{IDC_STATIC9,""},
								},
								// tieng Nauy
								{
									{IDC_STATICM,"InfoDict was Written by two author:"},
									{IDC_STATIC1,"Name: Tran The vu"},
									{IDC_STATIC2,"Email : anhvaut@yahoo.co.uk"},
									{IDC_STATIC3,"Name: Huynh Thi Le Thanh"},
									{IDC_STATIC4,"Email : foreverbluerain@yahoo.com"},
									{IDC_STATIC5,"person support:"},
									{IDC_STATIC6,"Truong Ngoc Chau"},
									{IDC_STATIC7,"IT Faculty "},
									{IDC_STATIC8,"DaNang University Of Technology"},
									{IDC_STATIC9,""},
								
								}
							  };


void changeAuthorDlgGUI(HWND hwnd,int index){
	// items
	// so^' lu+o+.ng items ca^`n pha?i ddo^?i trong 1 dialog 
	// khi thay ddo^i ngo^n ngu~
	int items=sizeof(m_AuthorDlgItem[index])/sizeof(AuthorDlgItem);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_AuthorDlgItem[index][j].text,unicode_string);
		 SetDlgItemText(hwnd,m_AuthorDlgItem[index][j].id,unicode_string);
	}
}

SettingDlgItem m_SettingDlgItem[][13]={
								//tieng anh
								{
									{IDC_STATIC1,"AutoLook"},
									{IDC_STATIC11,"Left Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Right Click"},
									{IDC_STATIC2,"Options"},
									{IDC_STATIC21,"Close window when mouse out"},
									{IDC_STATIC22,"Run at boot time"},
									{IDC_STATIC3,"Language gui"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"About"},
									{IDC_CANCEL,"Cancel"}
								},
								//
								//tieng Phap
								{
									{IDC_STATIC1,"AutoLook"},
									{IDC_STATIC11,"Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Right Click"},
									{IDC_STATIC2,"Options"},
									{IDC_STATIC21,"Close window when mouse out"},
									{IDC_STATIC22,"Run at boot time"},
									{IDC_STATIC3,"Language gui"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"About"},
									{IDC_CANCEL,"Cancel"}
								},
								//tieng duc
							
								{
									{IDC_STATIC1,"AutoLook"},
									{IDC_STATIC11,"Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Right Click"},
									{IDC_STATIC2,"Options"},
									{IDC_STATIC21,"Close window when mouse out"},
									{IDC_STATIC22,"Run at boot time"},
									{IDC_STATIC3,"Language gui"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"About"},
									{IDC_CANCEL,"Cancel"}
								},
								//tieng viet
				
								{
									{IDC_STATIC1,"Tra Từ Tự Động"},
									{IDC_STATIC11,"Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Chuột Phải"},
									{IDC_STATIC2,"Tuỳ Chọn"},
									{IDC_STATIC21,"Đóng cửa sổ khi đưa chuột qua"},
									{IDC_STATIC22,"Khởi Động Cùng Windows"},
									{IDC_STATIC3,"Thay Đổi Ngôn Ngữ Của Giao Diện"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"Giới Thiệu"},
									{IDC_CANCEL,"Tắt"}
								},
								//tieng Nga
								
								{
									{IDC_STATIC1,"AutoLook"},
									{IDC_STATIC11,"Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Right Click"},
									{IDC_STATIC2,"Options"},
									{IDC_STATIC21,"Close window when mouse out"},
									{IDC_STATIC22,"Run at boot time"},
									{IDC_STATIC3,"Language gui"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"About"},
									{IDC_CANCEL,"Cancel"}
								},
								// tieng Nauy
								{
									{IDC_STATIC1,"AutoLook"},
									{IDC_STATIC11,"Ctrl"},
									{IDC_STATIC12,"Shift"},
									{IDC_STATIC13,"No"},
									{IDC_STATIC14,"+"},
									{IDC_STATIC15,"Right Click"},
									{IDC_STATIC2,"Options"},
									{IDC_STATIC21,"Close window when mouse out"},
									{IDC_STATIC22,"Run at boot time"},
									{IDC_STATIC3,"Language gui"},
									{IDC_TASKBAR,"TaskBar"},
									{IDC_ABOUT,"About"},
									{IDC_CANCEL,"Cancel"}
								
								}
							  };


void changeSettingDlgGUI(HWND hwnd,int index){
	// items
	// so^' lu+o+.ng items ca^`n pha?i ddo^?i trong 1 dialog 
	// khi thay ddo^i ngo^n ngu~
	int items=sizeof(m_SettingDlgItem[index])/sizeof(SettingDlgItem);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_SettingDlgItem[index][j].text,unicode_string);
		 SetDlgItemText(hwnd,m_SettingDlgItem[index][j].id,unicode_string);
	}
}


//////////////


SettingDlgCombobox m_SettingDlgCombobox[][6]={
												//Tieng Anh
												{
													{IDC_GUILANGUAGE,"English"},
													{IDC_GUILANGUAGE,"Frence"},
													{IDC_GUILANGUAGE,"German"},
													{IDC_GUILANGUAGE,"Vietnamese"},
													{IDC_GUILANGUAGE,"Russia"},
													{IDC_GUILANGUAGE,"Nauy"},
												},
												//Tieng Phap
												{
													{IDC_GUILANGUAGE,"English"},
													{IDC_GUILANGUAGE,"Frence"},
													{IDC_GUILANGUAGE,"German"},
													{IDC_GUILANGUAGE,"Vietnamese"},
													{IDC_GUILANGUAGE,"Russia"},
													{IDC_GUILANGUAGE,"Nauy"},
												},
												//Tieng Duc
												{
													{IDC_GUILANGUAGE,"English"},
													{IDC_GUILANGUAGE,"Frence"},
													{IDC_GUILANGUAGE,"German"},
													{IDC_GUILANGUAGE,"Vietnamese"},
													{IDC_GUILANGUAGE,"Russia"},
													{IDC_GUILANGUAGE,"Nauy"},
												},
												//Tieng Nga
												{
													{IDC_GUILANGUAGE,"Tiếng Anh"},
													{IDC_GUILANGUAGE,"Tiếng Pháp"},
													{IDC_GUILANGUAGE,"Tiếng Đức"},
													{IDC_GUILANGUAGE,"Tiếng Việt"},
													{IDC_GUILANGUAGE,"Tiếng Nga"},
													{IDC_GUILANGUAGE,"Tiếng Nauy"},
												},
												//Tieng Nga
												{
													{IDC_GUILANGUAGE,"English"},
													{IDC_GUILANGUAGE,"Frence"},
													{IDC_GUILANGUAGE,"German"},
													{IDC_GUILANGUAGE,"Vietnamese"},
													{IDC_GUILANGUAGE,"Russia"},
													{IDC_GUILANGUAGE,"Nauy"},
												},
												//Tieng Nauy
												{
													{IDC_GUILANGUAGE,"English"},
													{IDC_GUILANGUAGE,"Frence"},
													{IDC_GUILANGUAGE,"German"},
													{IDC_GUILANGUAGE,"Vietnamese"},
													{IDC_GUILANGUAGE,"Russia"},
													{IDC_GUILANGUAGE,"Nauy"},
												},

											  };


extern CComboBox languageOption;
void changeSettingDlgComboboxGUI(int index){
	// items
	// so^' lu+o+.ng items ca^`n pha?i ddo^?i trong 1 dialog 
	// khi thay ddo^i ngo^n ngu~
	int items=sizeof(m_SettingDlgCombobox[index])/sizeof(SettingDlgCombobox);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_SettingDlgCombobox[index][j].text,unicode_string);
		 languageOption.InsertString(j,unicode_string);
		// GetDlgItem(hwnd,IDC_GUILANGUAGE)->SendMessage( CB_ADDSTRING, 0,(LPARAM)unicode_string);
		 //GetDlgItem(hwnd,IDC_GUILANGUAGE)->
		
	}
}


/////// TreePropSheet

TreePropSheetGUI m_TreePropSheetGUI[][3]={	
										//tieng anh
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Cancel"},
											{ID_APPLY_NOW,"Help"},
										},
										//Tieng Phap
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Cancel"},
											{ID_APPLY_NOW,"Help"},
										},
										//Tieng Duc
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Cancel"},
											{ID_APPLY_NOW,"Help"},
										},
										//Tieng Viet
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Tắt"},
											{ID_APPLY_NOW,"Giúp Đỡ"},
										},
										//Tieng Nga
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Cancel"},
											{ID_APPLY_NOW,"Help"},
										},
										//Tieng Nauy
										{
											{IDOK,"Taskbar"},
											{IDCANCEL,"Cancel"},
											{ID_APPLY_NOW,"Help"},
										},
								   };


void changeTreePropSheetGUI(HWND hwnd,int index){
	
	int items=sizeof(m_TreePropSheetGUI[index])/sizeof(TreePropSheetGUI);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_TreePropSheetGUI[index][j].text,unicode_string);
		 SetDlgItemText(hwnd,m_TreePropSheetGUI[index][j].id,unicode_string);
	}
}


/////ReadDlg

ReadDlgGUI m_ReadDlgGUI[][5]={	
										//tieng anh
										{
											{IDC_STATIC1,"Shotcut Keys"},
											{IDC_STATIC11,"Right Ctrl+Right Click"},
											{IDC_STATIC2,"Options"},
											{IDC_READ_TURN_OFF,"turn off"},
											{IDC_READ_SHOW,"Show Dialog"},
										},
										//Tieng Phap
										{
											{IDC_STATIC1,"Shotcut Keys"},
											{IDC_STATIC11,"Right Ctrl+Right Click"},
											{IDC_STATIC2,"Options"},
											{IDC_READ_TURN_OFF,"turn off"},
											{IDC_READ_SHOW,"Show Dialog"},
										},
										//Tieng Duc
										{
											{IDC_STATIC1,"Shotcut Keys"},
											{IDC_STATIC11,"Right Ctrl+Right Click"},
											{IDC_STATIC2,"Options"},
											{IDC_READ_TURN_OFF,"turn off"},
											{IDC_READ_SHOW,"Show Dialog"},
										},
										//Tieng Viet
										{
											{IDC_STATIC1,"Phim Tắt"},
											{IDC_STATIC11,"Phím Ctrl Phải + Chuột Phải"},
											{IDC_STATIC2,"Tuỳ Chọn"},
											{IDC_READ_TURN_OFF,"Tắt Chức Năng Này"},
											{IDC_READ_SHOW,"Hiển Thị Hộp Thoại Khi Đọc"},
										},
										//Tieng Nga
										{
											{IDC_STATIC1,"Shotcut Keys"},
											{IDC_STATIC11,"Right Ctrl+Right Click"},
											{IDC_STATIC2,"Options"},
											{IDC_READ_TURN_OFF,"turn off"},
											{IDC_READ_SHOW,"Show Dialog"},
										},
										//Tieng Nauy
										{
											{IDC_STATIC1,"Shotcut Keys"},
											{IDC_STATIC11,"Right Ctrl+Right Click"},
											{IDC_STATIC2,"Options"},
											{IDC_READ_TURN_OFF,"turn off"},
											{IDC_READ_SHOW,"Show Dialog"},
										},
								   };

void changeReadDlgGUI(HWND hwnd,int index){
	
	int items=sizeof(m_ReadDlgGUI[index])/sizeof(ReadDlgGUI);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_ReadDlgGUI[index][j].text,unicode_string);
		 SetDlgItemText(hwnd,m_ReadDlgGUI[index][j].id,unicode_string);
	}
}



////Server

ServerDlgGUI m_ServerDlgGUI[][4]={	
										//tieng anh
										{
											{IDC_STATIC1,"Connection Status"},
										
											{IDC_STATIC2,"Update Options"},
											{IDC_AUTOUPDATE,"Always autoupdate new version"},
											{IDC_CHECK_NEW_VERSION,"Check for new version"},
										},
										//Tieng Phap
										{
											{IDC_STATIC1,"Connection Status"},
											
											{IDC_STATIC2,"Update Options"},
											{IDC_AUTOUPDATE,"Always autoupdate new version"},
											{IDC_CHECK_NEW_VERSION,"Check for new version"},
										},
										//Tieng Duc
										{
											{IDC_STATIC1,"Connection Status"},
										
											{IDC_STATIC2,"Update Options"},
											{IDC_AUTOUPDATE,"Always autoupdate new version"},
											{IDC_CHECK_NEW_VERSION,"Check for new version"},
										},
										//Tieng Viet
										{
											{IDC_STATIC1,"Tình Trạng Kết Nối"},
											{IDC_STATIC2,"Tuỳ Chọn"},
											{IDC_AUTOUPDATE,"Tự Động Cập Nhật Phiên Bản Mới"},
											{IDC_CHECK_NEW_VERSION,"Cập Nhật Phiên Bản Mới"},
										},
										//Tieng Nga
										{
											{IDC_STATIC1,"Connection Status"},
									
											{IDC_STATIC2,"Update Options"},
											{IDC_AUTOUPDATE,"Always autoupdate new version"},
											{IDC_CHECK_NEW_VERSION,"Check for new version"},
										},
										//Tieng Nauy
										{
											{IDC_STATIC1,"Connection Status"},
											{IDC_STATIC2,"Update Options"},
											{IDC_AUTOUPDATE,"Always autoupdate new version"},
											{IDC_CHECK_NEW_VERSION,"Check for new version"},
										},
								   };

void changeServerDlgGUI(HWND hwnd,int index){
	
	int items=sizeof(m_ServerDlgGUI[index])/sizeof(ServerDlgGUI);
	wchar_t unicode_string[256];
  

	for(int j=0;j<items;j++){
		 Utf8_Unicode((BYTE*)m_ServerDlgGUI[index][j].text,unicode_string);
		 SetDlgItemText(hwnd,m_ServerDlgGUI[index][j].id,unicode_string);
	}
}


