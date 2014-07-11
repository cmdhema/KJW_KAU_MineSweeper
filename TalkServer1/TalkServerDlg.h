// TalkServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"
#include "ServiceSocket.h"
#include "atltypes.h"

// CTalkServerDlg ��ȭ ����
class CTalkServerDlg : public CDialog
{
// �����Դϴ�.
public:
	CTalkServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TALKSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CServiceSocket *m_pServiceSocket;
	CListenSocket *m_pListenSocket;
public:
	CListBox m_list_talk;
	CEdit m_edit_talk;
	CEdit m_edit_port;
	CEdit m_edit_id;
	CButton m_button_send;
	CButton m_button_start;
	CButton m_button_stop;
	CButton m_game_start;
	CStatic text_oppo;
	CStatic text_me;
public:
	void ProcessAccept();
	void ProcessReceive(CServiceSocket*);
	void ProcessClose();
	void SetButtonStatus(bool bSend, bool bStart, bool bStop, bool bGame);
	void setPoint(CString);
	void make(CPoint point);
	void loadbitmap(int i,CPoint point);
	void clear();
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnBnClickedGameStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	HBITMAP hbit;
	HBITMAP hbit2;
	CStatic image_ready;
	CStatic image_ready2;
	CFont font;
	CBrush m_brush;
	CBitmap m_background;
	CBitmapButton button_tusi;
	CBitmapButton button_three;
	CBitmapButton button_power;
public:
	CString xpoint;
	CString ypoint;
	int xp;
	int yp;
	int sec;
	int op_count;
	bool op;
public:
	int click_n;
	int find_mine(int x, int y);          // ��� �Լ� -> �ֺ� 8������ ���ڰ����� ���ϴ� �Լ�
	int m_min;
	int m_sec;
	int tag[20][20];
	int tag1[20][20];
	CPoint point_temp;
	int end;
	bool rbutton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void see_2row(int mine,int x,int y);

};
