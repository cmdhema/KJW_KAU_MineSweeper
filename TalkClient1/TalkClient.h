// TalkClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTalkClientApp:
// �� Ŭ������ ������ ���ؼ��� TalkClient.cpp�� �����Ͻʽÿ�.
//

class CTalkClientApp : public CWinApp
{
public:
	CTalkClientApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTalkClientApp theApp;