// ServiceSocket.cpp : 구현 파일입니다.
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


// CServiceSocket 멤버 함수

void CServiceSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pTalkServerDlg->ProcessReceive(this);

	CSocket::OnReceive(nErrorCode);
}

void CServiceSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pTalkServerDlg->ProcessClose();

	CSocket::OnClose(nErrorCode);
}
