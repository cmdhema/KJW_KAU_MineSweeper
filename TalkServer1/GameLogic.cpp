// GameLogic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TalkServer.h"
#include "GameLogic.h"
#include "TalkServerDlg.h"


// GameLogic ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GameLogic, CDialog)

GameLogic::GameLogic(CWnd* pParent /*=NULL*/)
	: CDialog(GameLogic::IDD, pParent)
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameLogic, CDialog)
END_MESSAGE_MAP()

