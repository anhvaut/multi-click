#ifndef _OPACITY_H
#define _OPACITY_H
class Opacity{
public:

	void SetWindowLayered (const HWND hwnd);
	void SetWindowOpacity (const HWND hwnd, const int iOpacity);
	
};
//cach dung
// m_opacity.SetWindowLayered (this->GetSafeHwnd ());
//m_opacity.SetWindowOpacity (this->GetSafeHwnd (), 100);

#endif