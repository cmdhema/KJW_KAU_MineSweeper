// GameLogic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TalkServer.h"
#include "GameLogic.h"
#include "TalkServerDlg.h"


// GameLogic 대화 상자입니다.

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

