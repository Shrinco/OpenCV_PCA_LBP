
// opencvMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CopencvMFCApp:
// �йش����ʵ�֣������ opencvMFC.cpp
//

class CopencvMFCApp : public CWinApp
{
public:
	CopencvMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CopencvMFCApp theApp;