// TalkServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TalkServer.h"
#include "TalkServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int mine[20][20]={0};

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTalkServerDlg ��ȭ ����

CTalkServerDlg::CTalkServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTalkServerDlg::IDD, pParent)
, m_min(0)
, m_sec(0)
, point_temp(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brush.CreateSolidBrush(GRAY_BRUSH);

	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			tag[i][j]=0;// �ƹ� �͵� �ȴ�������
		}
	}
	end = 30;
	op=false;
	op_count=3;


}

void CTalkServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LIST_TALK, m_list_talk);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edit_port);
	DDX_Control(pDX, ID_EDIT_TALK, m_edit_talk);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_button_send);
	DDX_Control(pDX, IDC_BUTTON_START, m_button_start);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_button_stop);
	DDX_Control(pDX, IDC_STATIC_ID, m_edit_id);
	DDX_Control(pDX, IDC_GAME_START, m_game_start);
	DDX_Control(pDX, IDC_IMAGE_READY, image_ready);
	DDX_Control(pDX, IDC_IMAGE_READY2, image_ready2);
	DDX_Control(pDX, IDC_STATIC_ME, text_me);
	DDX_Control(pDX, IDC_STATIC_OPPO, text_oppo);
	//	DDX_Control(pDX, IDC_IMAGE_BACKGROUND, image_background);
	DDX_Control(pDX, IDC_BUTTON2, button_tusi);
	DDX_Control(pDX, IDC_BUTTON3, button_three);
	DDX_Control(pDX, IDC_BUTTON4, button_power);
}

BEGIN_MESSAGE_MAP(CTalkServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START, &CTalkServerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CTalkServerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTalkServerDlg::OnBnClickedButtonSend)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_GAME_START, &CTalkServerDlg::OnBnClickedGameStart)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON2, &CTalkServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTalkServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTalkServerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTalkServerDlg �޽��� ó����

BOOL CTalkServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetButtonStatus(FALSE,TRUE,FALSE,FALSE);


	m_background.LoadBitmapA(IDB_BITMAP18);

	hbit= ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP13));
	image_ready.SetBitmap(hbit);

	hbit2= ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP14));
	image_ready2.SetBitmap(hbit2);

	font.CreateFontA(20,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"����");

	GetDlgItem(IDC_STATIC_ME)->SetFont(&font);
	GetDlgItem(IDC_STATIC_OPPO)->SetFont(&font);

	button_tusi.LoadBitmaps(IDB_BITMAP19,NULL,NULL,NULL);
	button_three.LoadBitmaps(IDB_BITMAP20,NULL,NULL,NULL);
	button_power.LoadBitmaps(IDB_BITMAP21,NULL,NULL,NULL);

	button_tusi.SizeToContent();
	button_three.SizeToContent();
	button_power.SizeToContent();



	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CTalkServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTalkServerDlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}



	SetTimer(1, 1000, NULL);               // ����ã�⸦ ���������� �ð������ ������� wm_timer ���� 1��(1000ms)���� �ݺ�


	click_n = 0;                          
	for(int i = 0; i < 20 ; i++){          // ���� ��ġ�� ���� ������ ������ 2���� �迭 �ʱ�ȭ
		for(int j = 0; j < 20 ; j++) mine[i][j] = 0;
	}		

	srand((unsigned int)time(NULL)); 

	for (int i = 0; i < 30 ; i++)            // ������ ���� 30���� ��ġ�� �����ϰ� 2���� �迭�� �Է�
	{
		int rand_x = rand()%20;
		int rand_y = rand()%20;
		TRACE("%d, %d\n",rand_x,rand_y);
		mine[rand_x][rand_y] = 2;		
	}



	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);


	CBitmap bitmap;                            
	bitmap.CreateCompatibleBitmap(&dc, 400, 400);    
	memDC.SelectObject(&bitmap);	// memdc�� �� ��ȭ���� �׷�����.
	bitmap.DeleteObject();          // ��Ʈ���� ������Ʈ �ʱ�ȭ

	bitmap.LoadBitmapA(IDB_BITMAP1); // ��Ʈ��1�� �ε��Ѵ�.
	CBrush brush(&bitmap);
	memDC.SelectObject(&brush);


	for(int i = 0; i <= 380 ; i=i+20){             // 20*20 �������� �簢���� memdc�� �׷��ش�.
		for (int j = 0; j <=380 ; j=j+20){//memdc(memory dc)�� ����ϴ� ������ �̸� �޸𸮿� dc�׸��� �׷��ΰ� ȭ�� dc�� �����Ͽ� ��Ÿ�������ؼ� ���
			memDC.Rectangle(i,j,i+20,j+20);
		}
	}

	dc.BitBlt(0,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc�� �׷��� ������ �信 �ѷ��ش�.
	dc.BitBlt(740,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc�� �׷��� ������ �信 �ѷ��ش�.

}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTalkServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTalkServerDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UINT nPort;
	TCHAR strPort[10];

	m_edit_port.GetWindowText(strPort,10);
	nPort = atoi(strPort);
	m_pListenSocket=new CListenSocket(this);

	if(!m_pListenSocket->Create(nPort)){
		m_list_talk.AddString(_T("Fail to create socket"));
		return;
	}

	m_list_talk.AddString("Success to Create Socket.....");

	if(!m_pListenSocket->Listen()){
		m_list_talk.AddString(_T("Fail to Listen Socket"));
		return;
	}

	m_list_talk.AddString("Listen Socket....");

	SetButtonStatus(FALSE,FALSE,TRUE,FALSE);
	m_button_send.SetFocus();
}

void CTalkServerDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pListenSocket->Close();
	m_pServiceSocket->Close();

	m_list_talk.AddString(_T("Close Socket"));
	delete m_pListenSocket;
	delete m_pServiceSocket;

	SetButtonStatus(FALSE,TRUE,FALSE,FALSE);
}


void CTalkServerDlg::OnBnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TCHAR strSndBuffer[500];
	TCHAR strIdBuffer[100];
	TCHAR SndMessage[600]="[";
	TCHAR *gubun2="]:";

	m_list_talk.SetCurSel(m_list_talk.GetCount()-1); 

	m_edit_id.GetWindowTextA(strIdBuffer,100);

	strcat(SndMessage,strIdBuffer);
	strcat(SndMessage,gubun2);

	m_edit_talk.GetWindowText(strSndBuffer,500);

	strcat(SndMessage,strSndBuffer);
	m_pServiceSocket->Send(SndMessage,(int)strlen(SndMessage));

	m_edit_talk.SetWindowText(_T(""));
	m_list_talk.AddString(_T(SndMessage));

	m_list_talk.SetCurSel(m_list_talk.GetCount()-1); 
	m_list_talk.SetCurSel(-1);

}



void CTalkServerDlg::ProcessAccept(){
	m_pServiceSocket=new CServiceSocket(this);

	m_pListenSocket->Accept(*m_pServiceSocket);

	m_list_talk.AddString("Connection Accept....");
	SetButtonStatus(TRUE,FALSE,TRUE,TRUE);
}

void CTalkServerDlg::ProcessReceive(CServiceSocket *pServiceSocket){
	int nRead;
	TCHAR rcvBuffer[1024];
	CString strBuffer=_T("");

	nRead=m_pServiceSocket->Receive(rcvBuffer,1024);

	if(rcvBuffer[0]=='['){
		m_list_talk.AddString(strBuffer.Left(nRead));
		m_list_talk.SetCurSel(m_list_talk.GetCount()-1); 
		m_list_talk.SetCurSel(-1);
	}
	else if(rcvBuffer[0]=='X'){
		setPoint(strBuffer);
	}
	else if(rcvBuffer[0]=='W'){
		::AfxMessageBox(_T("����� �����ϴ�.."));
	}
	else if(rcvBuffer[0]=='F'){
		clear();
	}
}



void CTalkServerDlg::ProcessClose(){
	m_pServiceSocket->Close();

	m_list_talk.AddString(_T("Client Close Socket"));
	delete m_pServiceSocket;

	SetButtonStatus(FALSE,FALSE,TRUE,FALSE);
}


void CTalkServerDlg::SetButtonStatus(bool bSend, bool bStart, bool bStop, bool bGame){
	m_button_send.EnableWindow(bSend);
	m_button_start.EnableWindow(bStart);
	m_button_stop.EnableWindow(bStop);
	m_game_start.EnableWindow(bGame);
}


void CTalkServerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	if(mine[point.x/20][point.y/20] == 1){        // Ŭ���� ĭ�� ��ġ�� ���°� ó�����°� �ƴҽ� ����
		return;
	}

	if(xp<400&& yp<400){
		CClientDC dc(this);
		if(mine[point.x/40][point.y/40] == 1){        // Ŭ���� ĭ�� ��ġ�� ���°� ó�����°� �ƴҽ� ����
			return;
		}

		point_temp = point;                          // ���ʹ�ư�� Ŭ���� ������ ��ǥ�� ����


	}
	if(mine[point.x/20][point.y/20]!= 2 && rbutton==true)
	{
		make(point);
	}
	rbutton= false;

	CDialog::OnLButtonDown(nFlags, point);

}

void CTalkServerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(tag[point.x/20][point.y/20]==0) 
	{

		CClientDC dc(this);
		CBitmap bitmap;

		if(point.x<=400 && point.y<=400){
			if(mine[point.x/20][point.y/20] == 0){// ���� ��ġ�� ���ڰ� ���� ��� �迭�� ������ �� ��ġ�� �׸��� �ٲٰ�, �ֺ� 8������ ���ڰ����� ����Ѵ�.	
				int a;
				a = find_mine(point.x/20,point.y/20);
				CClientDC dc(this);
				CBitmap bitmap;
				if(a!=0){
					loadbitmap(a,point);
					++click_n;
				}
				else{
					loadbitmap(a,point);
					++click_n;

					make(point);
				}
			}


			else if(mine[point.x/20][point.y/20] == 2){          // ���� ��ġ�� ���ڰ� ���� ��� �� ��ġ�� �׸��� �ٲ��ְ� ���ӿ��� �� ���� �����.
				if(op==false)
				{
					mine[point.x/20][point.y/20] = 2;
					bitmap.LoadBitmap(IDB_BITMAP2);
					CBrush brush(&bitmap);
					dc.SelectObject(&brush);
					TCHAR send[8]="FININSH";
					m_pServiceSocket->Send(send,strlen(send));
					dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
					::AfxMessageBox(_T("���ڸ� ��ҽ��ϴ�."));
					for(int i=0;i<20;i++)
					{	
						for(int j=0;j<20;j++)
						{
							tag[i][j]=0;// �ƹ� �͵� �ȴ�������
						}
					}
					Invalidate(true);
				}
				else
				{
					mine[point.x/20][point.y/20] = 2;
					bitmap.LoadBitmap(IDB_BITMAP21);
					CBrush brush(&bitmap);
					dc.SelectObject(&brush);
					dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
					op_count--;
					if(op_count==0)
					{
						op=false;
					}
				}
			}


			if(click_n == 470){                                   // ���ڰ� ���� ��ġ�� ���� Ŭ������ ���
				bitmap.DeleteObject();
				bitmap.LoadBitmapA(IDB_BITMAP13);
				CBrush brush(&bitmap);
				dc.SelectObject(&brush);
			}
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}



void CTalkServerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	TCHAR xy[10]="X";
	TCHAR xxp[10];
	TCHAR yyp[10];
	int xp;
	int yp;

	xp=point.x;
	yp=point.y;

	itoa(xp,xxp,10);
	itoa(yp,yyp,10);

	strcat(xy,xxp);
	strcat(xy,"X");
	strcat(xy,yyp);
	strcat(xy,"X");


	rbutton=true;
	CClientDC dc(this);
	CBitmap bitmap;
	if(tag[point.x/20][point.y/20]==0 || tag[point.x/20][point.y/20]==2){
		m_pServiceSocket->Send(xy,strlen(xy));
		if(tag[point.x/20][point.y/20]==2)
		{
			bitmap.LoadBitmapA(IDB_BITMAP8);
			CBrush brush(&bitmap);
			dc.SelectObject(&brush);	
			dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
			tag[point.x/20][point.y/20]=0;
		}
		else
		{
			bitmap.LoadBitmapA(IDB_BITMAP3);
			CBrush brush(&bitmap);
			dc.SelectObject(&brush);	
			dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
			tag[point.x/20][point.y/20]=2;
			if(mine[point.x/20][point.y/20]==2)
			{
				end--;
				if(end==0)
				{
					TCHAR send[5]="WIN";
					m_pServiceSocket->Send(send,strlen(send));
					CString vic;
					vic.Format(_T("���ϵ帳�ϴ�! ����� �̰���ϴ�! ����� ����� %d�� %d��"),m_min, m_sec); // ����ã�� ���� �޽��� �� �ð���� ���
					::AfxMessageBox(vic);
					KillTimer(1);             // �ð��� ����ִ� wm_timer�� �����Ѵ�.
					m_min = 0;                // ����ʱ�ȭ
					m_sec = 0;
					for(int i=0;i<20;i++)
					{	
						for(int j=0;j<20;j++)
						{
							tag[i][j]=0;// �ƹ� �͵� �ȴ�������
						}
					}
					Invalidate(true);
				}
			}
		}
	}
}




int CTalkServerDlg::find_mine(int x, int y)            // Ŭ���� ĭ �ֺ��� ���ڰ����� ���ϴ� ��� �Լ�
{
	CClientDC dc(this);
	CBitmap bitmap;

	int find=0 ;
	int n = 0;

	struct offset{                          // �̷�ã��� ����� �˰���
		int x;
		int y;
	};
	offset dir[8];                          // 8������ �����ϴ� ����ü ����
	dir[0].x = -1; dir[0].y = -1;
	dir[1].x = 0; dir[1].y = -1;
	dir[2].x = 1; dir[2].y = -1;
	dir[3].x = 1; dir[3].y = 0;
	dir[4].x = 1; dir[4].y = 1;
	dir[5].x = 0; dir[5].y = 1;
	dir[6].x = -1; dir[6].y = 1;
	dir[7].x = -1; dir[7].y = 0;
	offset search;

	while(n < 8){                        // Ŭ���� ��ġ�� �ֺ��� 8���� �迭�� �а�, find (���� ����)�� ++�Ѵ�.
		search.x=x;
		search.y=y;

		search.x = search.x + dir[n].x;
		search.y = search.y + dir[n].y;     

		if(mine[search.x][search.y] == 2 && search.x >= 0 && search.y >=0 && search.x < 20 && search.y < 20)
			++find;		

		n++;
	}

	return find;         // ���� ������ �����Ѵ�.
}


void CTalkServerDlg::OnBnClickedGameStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TCHAR send[10]="START";
	m_pServiceSocket->Send(send,strlen(send));

	image_ready.CloseWindow();
	image_ready2.CloseWindow();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	pDC->SetTextColor(RGB(0,0,255));
	//	return m_brush;

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}



void CTalkServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1){        
		++m_sec;
		if(sec==m_sec)
		{
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<20;j++)
				{
					int a = find_mine(i,j);
					if(mine[i][j]==2  && tag[i][j]==0)
					{
						CClientDC dc(this);
						CBitmap bitmap;
						bitmap.LoadBitmap(IDB_BITMAP1);
						CBrush brush(&bitmap);
						dc.SelectObject(&brush);
						dc.Rectangle(i*20,j*20,i*20+20,j*20+20);
					}
				}
			}
		}// �� ����
		if(m_sec == 60){          // �� ����
			++m_min;
			m_sec = 0;          
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CTalkServerDlg::setPoint(CString strBuffer){

	AfxExtractSubString(xpoint,strBuffer,1,'X');
	AfxExtractSubString(ypoint,strBuffer,2,'X');

	xp=atoi(xpoint);
	yp=atoi(ypoint);

	xp=xp/20*20;
	yp=yp/20*20;

	CClientDC dc(this);

	if(mine[xp/40][yp/40] == 1){        // Ŭ���� ĭ�� ��ġ�� ���°� ó�����°� �ƴҽ� ����
		return;
	}

	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP3);             // Ŭ���ҽ� ��Ʈ�� 2�� �ε��Ͽ� ĭ�� �׸��� �ٲ��ش�.

	CBrush brush(&bitmap);
	dc.SelectObject(&brush);
	dc.Rectangle((xp+750)/20*20, yp/20*20, (xp+750)/20*20+20, yp/20*20+20);
}



void CTalkServerDlg::make(CPoint point){
	int a;
	point.x=point.x-20;
	point.y=point.y-20;

	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2 )
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.x=point.x+20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.x=point.x+20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{

		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;

		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.y=point.y+20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;

		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.y=point.y+20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.x=point.x-20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}
	}

	point.x=point.x-20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			tag[point.x/20][point.y/20]=1;
			make(point);
		}

	}

	point.y=point.y-20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2)
	{
		a = find_mine(point.x/20,point.y/20);
		loadbitmap(a,point);
		++click_n;
		if(a==0 && tag[point.x/20][point.y/20]==0)
		{
			make(point);
			tag[point.x/20][point.y/20]=1;
		}
	}
}


void CTalkServerDlg::loadbitmap(int i, CPoint point){

	CClientDC dc(this);
	CBitmap bitmap;

	if(i==0)
	{	
		bitmap.LoadBitmapA(IDB_BITMAP9);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==1)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP4);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);		
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==2)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP5);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==3)
	{	
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP6);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==4)
	{	
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP7);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==5)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP10);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==6)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP11);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);

	}
	if(i==7)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmapA(IDB_BITMAP12);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);

	}
}


void CTalkServerDlg::clear(){

	CClientDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);


	CBitmap bitmap;                            
	bitmap.CreateCompatibleBitmap(&dc, 400, 400);    
	memDC.SelectObject(&bitmap);	// memdc�� �� ��ȭ���� �׷�����.
	bitmap.DeleteObject();          // ��Ʈ���� ������Ʈ �ʱ�ȭ

	bitmap.LoadBitmapA(IDB_BITMAP1); // ��Ʈ��1�� �ε��Ѵ�.
	CBrush brush(&bitmap);
	memDC.SelectObject(&brush);


	for(int i = 0; i <= 380 ; i=i+20){             // 20*20 �������� �簢���� memdc�� �׷��ش�.
		for (int j = 0; j <=380 ; j=j+20){//memdc(memory dc)�� ����ϴ� ������ �̸� �޸𸮿� dc�׸��� �׷��ΰ� ȭ�� dc�� �����Ͽ� ��Ÿ�������ؼ� ���
			memDC.Rectangle(i,j,i+20,j+20);
		}
	}
	dc.BitBlt(740,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc�� �׷��� ������ �信 �ѷ��ش�.
}


BOOL CTalkServerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDialog::OnEraseBkgnd(pDC);

	if(!m_background.m_hObject)
		return true;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;

	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bmap.bmWidth,bmap.bmHeight,SRCCOPY);

	dc.SelectObject(pOldBitmap);

	return true;
}

void CTalkServerDlg::OnBnClickedButton2()
{
	sec=m_sec;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(mine[i][j]==2  && tag[i][j]==0)
			{
				CClientDC dc(this);
				CBitmap bitmap;
				bitmap.LoadBitmap(IDB_BITMAP18);
				CBrush brush(&bitmap);
				dc.SelectObject(&brush);
				dc.Rectangle(i*20,j*20,i*20+20,j*20+20);
			}
		}
	}
	sec=sec+3;
}

void CTalkServerDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(mine[i][j]==2)
			{
				CClientDC dc(this);
				CBitmap bitmap;
				bitmap.LoadBitmap(IDB_BITMAP17);
				CBrush brush(&bitmap);
				dc.SelectObject(&brush);
				dc.Rectangle(i*20,j*20,i*20+20,j*20+20);
			}
			else
			{ 
				int mine;
				mine=find_mine(i,j);
				see_2row(mine,i,j);
			}
		}
	}
}


void CTalkServerDlg::see_2row(int mine,int x,int y)
{
	CClientDC dc(this);
	CBitmap bitmap;
	if(mine==0)
	{	
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP9);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==1)
	{
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP4);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);		
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==2)
	{
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP5);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==3)
	{	
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP6);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==4)
	{	
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP7);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==5)
	{
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP10);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==6)
	{
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP11);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
	if(mine==7)
	{
		tag[x][y]=1;
		bitmap.LoadBitmap(IDB_BITMAP12);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(x*20,y*20,x*20+20,y*20+20);
	}
}
void CTalkServerDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	op=true;
}
