
#include "resource.h"
class CVNKeyBoardDlg : public CDialog
{
public:
	CVNKeyBoardDlg();
	
	void InitData();
	void Charset();
	void InputMethodChange();
	void SwitchKey1();
	void SwitchKey2();
	void Taskbar();

	CBrush  m_WhiteBrush;
// Dialog Data
	enum { IDD = IDD_KEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	
// Implementation
protected:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};
