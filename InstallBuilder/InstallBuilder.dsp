# Microsoft Developer Studio Project File - Name="InstallBuilder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=InstallBuilder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "InstallBuilder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InstallBuilder.mak" CFG="InstallBuilder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InstallBuilder - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "InstallBuilder - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InstallBuilder - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386 /out:"Release/builder.exe"

!ELSEIF  "$(CFG)" == "InstallBuilder - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Builder.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "InstallBuilder - Win32 Release"
# Name "InstallBuilder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddShortcutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogResize.cpp
# End Source File
# Begin Source File

SOURCE=.\FilesTab.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralTab.cpp
# End Source File
# Begin Source File

SOURCE=.\InstallBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\InstallBuilder.rc
# End Source File
# Begin Source File

SOURCE=.\InstallBuilderDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\InstallBuilderView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputTab.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutTab.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticLink.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\WizardPages.cpp
# End Source File
# Begin Source File

SOURCE=.\WizardSheet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddShortcutDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogResize.h
# End Source File
# Begin Source File

SOURCE=.\FilesTab.h
# End Source File
# Begin Source File

SOURCE=.\GeneralTab.h
# End Source File
# Begin Source File

SOURCE=.\InstallBuilder.h
# End Source File
# Begin Source File

SOURCE=.\InstallBuilderDoc.h
# End Source File
# Begin Source File

SOURCE=.\InstallBuilderView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OutputTab.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutObject.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutTab.h
# End Source File
# Begin Source File

SOURCE=.\StaticLink.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\WizardPages.h
# End Source File
# Begin Source File

SOURCE=.\WizardSheet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\finger.cur
# End Source File
# Begin Source File

SOURCE=.\res\idr_file.ico
# End Source File
# Begin Source File

SOURCE=.\res\InstallBuilder.ico
# End Source File
# Begin Source File

SOURCE=.\res\InstallBuilder.rc2
# End Source File
# Begin Source File

SOURCE=.\res\InstallBuilderDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\setup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shortcuts.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabicons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\stub.exe
# End Source File
# End Target
# End Project
