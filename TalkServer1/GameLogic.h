#pragma once


// GameLogic ��ȭ �����Դϴ�.

class GameLogic : public CDialog
{
	DECLARE_DYNAMIC(GameLogic)

public:
	GameLogic(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GameLogic();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TALKSERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()




};
