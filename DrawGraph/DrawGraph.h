
// DrawGraph.h : DrawGraph Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDrawGraphApp:
// �йش����ʵ�֣������ DrawGraph.cpp
//

class CDrawGraphApp : public CWinApp
{
public:
	CDrawGraphApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawGraphApp theApp;
