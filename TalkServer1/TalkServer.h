// TalkServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTalkServerApp:
// �� Ŭ������ ������ ���ؼ��� TalkServer.cpp�� �����Ͻʽÿ�.
//

class CTalkServerApp : public CWinApp
{
public:
	CTalkServerApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTalkServerApp theApp;