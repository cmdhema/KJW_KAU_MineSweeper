#pragma once

// CListenSocket ��� ����Դϴ�.
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


