// TalkClientSocket.cpp : 구현 파일입니다.
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


// CTalkClientSocket 멤버 함수

void CTalkClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pTalkClientDlg->ProcessReceive();

	CSocket::OnReceive(nErrorCode);
}

void CTalkClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pTalkClientDlg->ProcessClose();

	CSocket::OnClose(nErrorCode);
}
