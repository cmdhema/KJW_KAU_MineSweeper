// TalkClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TalkClientSocket.h"
#include "atltypes.h"
#include "afxext.h"


// CTalkClientDlg 대화 상자
class CTalkClientDlg : public CDialog
{
// 생성입니다.
public:
	CTalkClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TALKCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTalkClientSocket *m_pTalkClientSocket;
public:
	CListBox m_list_box;
	CEdit m_edit_talk;
	CButton m_button_send;
	CIPAddressCtrl m_ip_address;
	CButton m_button_connect;
	CButton m_button_disconnect;
	CEdit m_edit_port;
	CEdit m_edit_id;
public:
	CString xpoint;
	CString ypoint;
	int xp;
	int yp;
	int sec;
public:
	void ProcessClose();
	void SetButtonStatus(bool, bool, bool);
	void ProcessReceive();
	void setPoint(CString);
	void make(CPoint point);
	void loadbitmap(int i,CPoint point);
	int find_mine(int x, int y);          // 멤버 함수 -> 주변 8방향의 지뢰개수를 구하는 함수
	void clear();
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CStatic image_ready;
	CStatic image_ready2;
	HBITMAP hbit;
	HBITMAP hbit2;
	CStatic text_oppo;
	CStatic text_me;
	CFont font;
	CBitmap m_background;
	CBitmapButton button_tusi;
	CBitmapButton button_three;
	CBitmapButton button_power;
public:
	CPoint point_temp;
	int click_n;
	int m_min;
	int m_sec;
	int tag[20][20];
	int tag1[20][20];
	int end;
	bool op;
	int op_count;
	bool rbutton;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void CTalkClientDlg::see_2row(int mine,int x,int y);
	afx_msg void OnBnClickedButton3();

};
