// TalkClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TalkClient.h"
#include "TalkClientSocket.h"

#include "TalkClientDlg.h"

// CTalkClientSocket

CTalkClientSocket::CTalkClientSocket(CTalkClientDlg *pTalkClientDlg)
{
	m_pTalkClientDlg = pTalkClientDlg;
}

CTalkClientSocket::~CTalkClientSocket()
{
}


// CTalkClientSocket ��� �Լ�

void CTalkClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pTalkClientDlg->ProcessReceive();

	CSocket::OnReceive(nErrorCode);
}

void CTalkClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pTalkClientDlg->ProcessClose();

	CSocket::OnClose(nErrorCode);
}
