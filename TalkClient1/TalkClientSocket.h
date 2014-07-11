#pragma once

class CTalkClientDlg;
// CTalkClientSocket 명령 대상입니다.

class CTalkClientSocket : public CSocket
{
public:
	CTalkClientSocket(CTalkClientDlg *pTalkClientDlg);
	virtual ~CTalkClientSocket();
public:
	CTalkClientDlg *m_pTalkClientDlg;
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


