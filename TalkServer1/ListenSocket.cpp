// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TalkServer.h"
#include "ListenSocket.h"

#include "TalkServerDlg.h"

// CListenSocket

CListenSocket::CListenSocket(CTalkServerDlg *pTalkServerDlg)
{
	m_pTalkServerDlg = pTalkServerDlg;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��� �Լ�

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pTalkServerDlg->ProcessAccept();

	CSocket::OnAccept(nErrorCode);
}
