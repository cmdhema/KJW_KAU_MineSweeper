// ServiceSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TalkServer.h"
#include "ServiceSocket.h"

#include "TalkServerDlg.h"

// CServiceSocket

CServiceSocket::CServiceSocket(CTalkServerDlg *pTalkServerDlg)
{
	m_pTalkServerDlg = pTalkServerDlg;
}

CServiceSocket::~CServiceSocket()
{
}


// CServiceSocket ��� �Լ�

void CServiceSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pTalkServerDlg->ProcessReceive(this);

	CSocket::OnReceive(nErrorCode);
}

void CServiceSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pTalkServerDlg->ProcessClose();

	CSocket::OnClose(nErrorCode);
}
