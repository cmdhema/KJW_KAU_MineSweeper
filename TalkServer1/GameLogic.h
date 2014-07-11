#pragma once


// GameLogic 대화 상자입니다.

class GameLogic : public CDialog
{
	DECLARE_DYNAMIC(GameLogic)

public:
	GameLogic(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GameLogic();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TALKSERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()




};
