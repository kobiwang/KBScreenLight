
// ScreenLight.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScreenLightApp:
// �йش����ʵ�֣������ ScreenLight.cpp
//

class CScreenLightApp : public CWinApp
{
public:
	CScreenLightApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScreenLightApp theApp;