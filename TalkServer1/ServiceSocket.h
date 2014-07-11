#pragma once

// CServiceSocket ��� ����Դϴ�.
class CTalkServerDlg;

class CServiceSocket : public CSocket
{
public:
	CServiceSocket(CTalkServerDlg *pTalkServerDlg);
	virtual ~CServiceSocket();
public:
	CTalkServerDlg *m_pTalkServerDlg;

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


