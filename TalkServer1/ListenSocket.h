#pragma once

// CListenSocket 명령 대상입니다.
class CTalkServerDlg;

class CListenSocket : public CSocket
{
public:
	CListenSocket(CTalkServerDlg *pTalkServerDlg);
	virtual ~CListenSocket();
public:
	CTalkServerDlg *m_pTalkServerDlg;

	virtual void OnAccept(int nErrorCode);
};


