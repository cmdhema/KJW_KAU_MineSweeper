#pragma once

class CTalkClientDlg;
// CTalkClientSocket ��� ����Դϴ�.

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


