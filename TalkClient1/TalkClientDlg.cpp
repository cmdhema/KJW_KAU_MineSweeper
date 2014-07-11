// TalkClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TalkClient.h"
#include "TalkClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int mine[20][20]={0};


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTalkClientDlg 대화 상자




CTalkClientDlg::CTalkClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTalkClientDlg::IDD, pParent)
, m_min(0)
, m_sec(0)
, point_temp(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			tag[i][j]=0;// 아무 것도 안눌럿을때
		}
	}
	end = 30;
	op=false;
	op_count=3;
}

void CTalkClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LIST_TALK, m_list_box);
	DDX_Control(pDX, ID_EDIT_TALK, m_edit_talk);
	DDX_Control(pDX, ID_BUTTON_SEND, m_button_send);
	DDX_Control(pDX, IDC_IPADDRESS, m_ip_address);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_button_connect);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT, m_button_disconnect);
	DDX_Control(pDX, IDC_STATIC_PORT, m_edit_port);
	DDX_Control(pDX, IDC_STATIC_ID, m_edit_id);
	DDX_Control(pDX, IDC_IMAGE_READY, image_ready);
	DDX_Control(pDX, IDC_IMAGE_READY2, image_ready2);
	DDX_Control(pDX, IDC_STATIC_OPPO, text_oppo);
	DDX_Control(pDX, IDC_STATIC_ME, text_me);
	DDX_Control(pDX, IDC_BUTTON1, button_tusi);
	DDX_Control(pDX, IDC_BUTTON2, button_three);
	DDX_Control(pDX, IDC_BUTTON3, button_power);
}

BEGIN_MESSAGE_MAP(CTalkClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CTalkClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CTalkClientDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(ID_BUTTON_SEND, &CTalkClientDlg::OnBnClickedButtonSend)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CTalkClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTalkClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTalkClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTalkClientDlg 메시지 처리기

BOOL CTalkClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetButtonStatus(FALSE,TRUE,FALSE);

	m_background.LoadBitmapA(IDB_BITMAP21);

	hbit= ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP13));
	image_ready.SetBitmap(hbit);

	hbit2= ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP14));
	image_ready2.SetBitmap(hbit2);

	font.CreateFontA(20,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"굴림");

	GetDlgItem(IDC_STATIC_ME)->SetFont(&font);
	GetDlgItem(IDC_STATIC_OPPO)->SetFont(&font);

	button_tusi.LoadBitmaps(IDB_BITMAP18,NULL,NULL,NULL);
	button_three.LoadBitmaps(IDB_BITMAP19,NULL,NULL,NULL);
	button_power.LoadBitmaps(IDB_BITMAP20,NULL,NULL,NULL);

	button_tusi.SizeToContent();
	button_three.SizeToContent();
	button_power.SizeToContent();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTalkClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTalkClientDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}


	SetTimer(1, 1000, NULL);               // 지뢰찾기를 성공했을때 시간기록을 재기위한 wm_timer 시작 1초(1000ms)마다 반복


	click_n = 0;                          
	for(int i = 0; i < 20 ; i++){          // 지뢰 위치와 상태 정보를 저장한 2차원 배열 초기화
		for(int j = 0; j < 20 ; j++) mine[i][j] = 0;
	}		

	srand((unsigned int)time(NULL)); 

	for (int i = 0; i < 30 ; i++)            // 난수로 지뢰 30개의 위치를 랜덤하게 2차원 배열에 입력
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
	memDC.SelectObject(&bitmap);	// memdc에 빈 도화지가 그려졌다.
	bitmap.DeleteObject();          // 비트맵의 오브젝트 초기화

	bitmap.LoadBitmap(IDB_BITMAP1); // 비트맵1을 로드한다.
	CBrush brush(&bitmap);
	memDC.SelectObject(&brush);


	for(int i = 0; i <= 380 ; i=i+20){             // 20*20 사이즈의 사각형을 memdc에 그려준다.
		for (int j = 0; j <=380 ; j=j+20){//memdc(memory dc)를 사용하는 이유는 미리 메모리에 dc그림을 그려두고 화면 dc에 복사하여 나타내기위해서 사용
			memDC.Rectangle(i,j,i+20,j+20);
		}
	}

	dc.BitBlt(0,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc에 그려진 내용을 뷰에 뿌려준다.
	dc.BitBlt(740,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc에 그려진 내용을 뷰에 뿌려준다.

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTalkClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTalkClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR strIP[20];	
	TCHAR strPort[10];

	UINT nPort;

	m_ip_address.GetWindowText(strIP,20);
	m_edit_port.GetWindowText(strPort,10);
	nPort=atoi(strPort);
	m_pTalkClientSocket = new CTalkClientSocket(this);
	if(!m_pTalkClientSocket->Create()){
		m_list_box.AddString(_T("Fail to Create Socket"));
		return;
	}

	m_list_box.AddString(_T("Socket Create...."));

	if(!m_pTalkClientSocket->Connect(strIP,nPort)){
		m_list_box.AddString(_T("Fail to connect"));
		return;
	}

	m_list_box.AddString(_T("Success to Connect...."));

	SetButtonStatus(TRUE,FALSE,TRUE);

}

void CTalkClientDlg::OnBnClickedButtonDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pTalkClientSocket->Close();
	delete m_pTalkClientSocket;
	SetButtonStatus(FALSE, TRUE, FALSE);
	m_list_box.AddString(_T("Close socket"));
}

void CTalkClientDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR strSndBuffer[500];
	TCHAR strIdBuffer[100];
	TCHAR SndMessage[600]="[";
	TCHAR *gubun2="]:";

	m_edit_id.GetWindowTextA(strIdBuffer,100);

	strcat(SndMessage,strIdBuffer);
	strcat(SndMessage,gubun2);

	m_edit_talk.GetWindowText(strSndBuffer,500);

	strcat(SndMessage,strSndBuffer);

	m_pTalkClientSocket->Send(SndMessage,(int)strlen(SndMessage));

	m_list_box.SetWindowText(SndMessage);
	m_edit_talk.SetWindowText(_T(""));
	m_list_box.AddString(_T(SndMessage));

	m_list_box.SetCurSel(m_list_box.GetCount()-1); 
	m_list_box.SetCurSel(-1);

}


void CTalkClientDlg::ProcessReceive(){
	int nRead;
	TCHAR rcvBuffer[1024];
	CString strBuffer=_T("");

	nRead=m_pTalkClientSocket->Receive(rcvBuffer,1024);
	strBuffer.Format("%s",rcvBuffer);

	if(strBuffer[0]=='['){
		m_list_box.AddString(strBuffer.Left(nRead));

		m_list_box.SetCurSel(m_list_box.GetCount()-1); 
		m_list_box.SetCurSel(-1);
	}
	else if(strBuffer[0]=='X'){
		setPoint(strBuffer);
	}
	else if(strBuffer[0]=='S'){
		image_ready.CloseWindow();
		image_ready2.CloseWindow();
	}
	else if(strBuffer[0]=='W'){
		::AfxMessageBox(_T("당신이 졌습니다.."));
	}
	else if(strBuffer[0]=='F'){
		clear();
	}
}


void CTalkClientDlg::ProcessClose(){
	m_list_box.AddString(_T("Server Close"));

	m_pTalkClientSocket->Close();
	delete m_pTalkClientSocket;
	SetButtonStatus(FALSE, TRUE, FALSE);

	m_list_box.AddString(_T("Connection Close"));
}

void CTalkClientDlg::SetButtonStatus(bool bSend, bool bConnect, bool bDisconnect){
	m_button_send.EnableWindow(bSend);
	m_button_connect.EnableWindow(bConnect);
	m_button_disconnect.EnableWindow(bDisconnect);
}


void CTalkClientDlg::setPoint(CString strBuffer){

	AfxExtractSubString(xpoint,strBuffer,1,'X');
	AfxExtractSubString(ypoint,strBuffer,2,'X');

	xp=atoi(xpoint);
	yp=atoi(ypoint);

	xp=xp/20*20;
	yp=yp/20*20;

	CClientDC dc(this);

	if(mine[xp/40][yp/40] == 1){        // 클릭한 칸의 위치의 상태가 처음상태가 아닐시 리턴
		return;
	}

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP3);             // 클릭할시 비트맵 2를 로드하여 칸의 그림을 바꿔준다.

	CBrush brush(&bitmap);
	dc.SelectObject(&brush);
	dc.Rectangle((xp+750)/20*20, yp/20*20, (xp+750)/20*20+20, yp/20*20+20);
}


void CTalkClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	if(point.x<400 && point.y<400){
		CClientDC dc(this);
		if(mine[point.x/20][point.y/20] == 1){        // 클릭한 칸의 위치의 상태가 처음상태가 아닐시 리턴
			return;
		}

		point_temp = point;                          // 왼쪽버튼을 클릭한 현재의 좌표를 저장
	}
	if(mine[point.x/20][point.y/20]!= 2 && rbutton==true)
	{
		make(point);
	}
	rbutton=false;
	CDialog::OnLButtonDown(nFlags, point);
}

void CTalkClientDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CBitmap bitmap;
	if(tag[point.x/20][point.y/20]==0) //!!
	{

		if(point.x<=400 && point.y<=400){
			if(mine[point.x/20][point.y/20] == 0)	{// 업한 위치에 지뢰가 없을 경우 배열의 정보와 그 위치의 그림을 바꾸고, 주변 8방향의 지뢰개수를 출력한다.	
				int a;
				a = find_mine(point.x/20,point.y/20);
				CClientDC dc(this);
				CBitmap bitmap;

				if(a!=0)
				{
					loadbitmap(a,point);
					++click_n;
				}
				else
				{
					loadbitmap(a,point);
					++click_n;
					make(point);
				}
			}


			else if(mine[point.x/20][point.y/20] == 2){          // 업한 위치에 지뢰가 있을 경우 그 위치의 그림을 바꿔주고 게임오버 및 게임 재시작.
			if(op==false)
			{
				TCHAR send[8]="FININSH";
				m_pTalkClientSocket->Send(send,strlen(send));
				mine[point.x/20][point.y/20] = 2;
				bitmap.LoadBitmap(IDB_BITMAP2);
				CBrush brush(&bitmap);
				dc.SelectObject(&brush);
				dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
				::AfxMessageBox(_T("지뢰를 밟았습니다."));
				Invalidate(true);
				for(int i=0;i<20;i++)
				{	
				for(int j=0;j<20;j++)
				{
					tag[i][j]=0;// 아무 것도 안눌럿을때
				}
				}
				
			}
			else
			{
				mine[point.x/20][point.y/20] = 2;
				bitmap.LoadBitmap(IDB_BITMAP17);
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

		}
	}
}


void CTalkClientDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	rbutton = true;
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

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(tag[point.x/20][point.y/20]==0 || tag[point.x/20][point.y/20]==2)
	{
		m_pTalkClientSocket->Send(xy,strlen(xy));

		CClientDC dc(this);
		CBitmap bitmap;
		if( tag[point.x/20][point.y/20]==2)
		{
			bitmap.LoadBitmap(IDB_BITMAP8);
			CBrush brush(&bitmap);
			dc.SelectObject(&brush);	
			dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
			tag[point.x/20][point.y/20]=0;
		}
		else
		{
			bitmap.LoadBitmap(IDB_BITMAP3);
			CBrush brush(&bitmap);
			dc.SelectObject(&brush);	
			dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
			tag[point.x/20][point.y/20]=2;
			if(mine[point.x/20][point.y/20]==2)
			{
				end--; //!!
				if(end==0) //!!
				{
					TCHAR send[5]="WIN";
					m_pTalkClientSocket->Send(send,strlen(send));
					CString vic;
					vic.Format(_T("축하드립니다! 당신이 이겼습니다! 당신의 기록은 %d분 %d초"),m_min, m_sec); // 지뢰찾기 성공 메시지 및 시간기록 출력
					::AfxMessageBox(vic);
					KillTimer(1);             // 시간을 재고있는 wm_를 종료한다.
					m_min = 0;                // 기록초기화
					m_sec = 0;
					for(int i=0;i<20;i++)
					{	
					for(int j=0;j<20;j++)
					{
					tag[i][j]=0;// 아무 것도 안눌럿을때
					}
					}
					Invalidate(true);
				}
			}
		}
	}

}

void CTalkClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1){
		++m_sec;
		if(sec==m_sec)
		{
			for(int i=0;i<20;i++)
			{
			for(int j=0;j<20;j++)
			{
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
		}
	
	                       // 초 증가
		if(m_sec == 60){          // 분 증가
			++m_min;
			m_sec = 0;          
		}
	}

	CDialog::OnTimer(nIDEvent);
}


int CTalkClientDlg::find_mine(int x, int y)            // 클릭한 칸 주변의 지뢰개수를 구하는 멤버 함수
{
	CClientDC dc(this);
	CBitmap bitmap;

	int find=0 ;
	int n = 0;

	struct offset{                          // 미로찾기와 비슷한 알고리즘
		int x;
		int y;
	};
	offset dir[8];                          // 8방향을 저장하는 구조체 생성
	dir[0].x = -1; dir[0].y = -1;
	dir[1].x = 0; dir[1].y = -1;
	dir[2].x = 1; dir[2].y = -1;
	dir[3].x = 1; dir[3].y = 0;
	dir[4].x = 1; dir[4].y = 1;
	dir[5].x = 0; dir[5].y = 1;
	dir[6].x = -1; dir[6].y = 1;
	dir[7].x = -1; dir[7].y = 0;
	offset search;

	while(n < 8){                        // 클릭한 위치의 주변의 8방향 배열을 읽고, find (지뢰 개수)를 ++한다.
		search.x=x;
		search.y=y;

		search.x = search.x + dir[n].x;
		search.y = search.y + dir[n].y;     

		if(mine[search.x][search.y] == 2 && search.x >= 0 && search.y >=0 && search.x < 20 && search.y < 20)
			++find;		

		n++;
	}

	return find;         // 지뢰 개수로 리턴한다.
}


void CTalkClientDlg::make(CPoint point)
{
	int a;
	point.x=point.x-20;
	point.y=point.y-20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0 && mine[point.x/20][point.y/20]!=2  )
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

	point.y=point.y+20;
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

	point.y=point.y+20;
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

	point.x=point.x-20;
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

	point.x=point.x-20;
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

	point.y=point.y-20;
	if(point.x>=0 && point.x<400  &&  point.y>=0 && point.y<400 && tag[point.x/20][point.y/20]==0&& mine[point.x/20][point.y/20]!=2 )
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



void CTalkClientDlg::loadbitmap(int i,CPoint point)
{
	CClientDC dc(this);
	CBitmap bitmap;

	if(i==0)
	{	
		bitmap.LoadBitmap(IDB_BITMAP9);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==1)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP4);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);		
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==2)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP5);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==3)
	{	
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP6);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==4)
	{	
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP7);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==5)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP10);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);
	}
	if(i==6)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP11);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);

	}
	if(i==7)
	{
		tag[point.x/20][point.y/20]=1;
		bitmap.LoadBitmap(IDB_BITMAP12);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.Rectangle(point.x/20*20, point.y/20*20, point.x/20*20+20, point.y/20*20+20);

	}

}


void CTalkClientDlg::clear(){

	CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);


	CBitmap bitmap;                            
	bitmap.CreateCompatibleBitmap(&dc, 400, 400);    
	memDC.SelectObject(&bitmap);	// memdc에 빈 도화지가 그려졌다.
	bitmap.DeleteObject();          // 비트맵의 오브젝트 초기화

	bitmap.LoadBitmapA(IDB_BITMAP1); // 비트맵1을 로드한다.
	CBrush brush(&bitmap);
	memDC.SelectObject(&brush);


	for(int i = 0; i <= 380 ; i=i+20){             // 20*20 사이즈의 사각형을 memdc에 그려준다.
		for (int j = 0; j <=380 ; j=j+20){//memdc(memory dc)를 사용하는 이유는 미리 메모리에 dc그림을 그려두고 화면 dc에 복사하여 나타내기위해서 사용
			memDC.Rectangle(i,j,i+20,j+20);
		}
	}
	dc.BitBlt(740,0,400, 400, &memDC, 0, 0, SRCCOPY);  // memdc에 그려진 내용을 뷰에 뿌려준다.
}


BOOL CTalkClientDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

void CTalkClientDlg::OnBnClickedButton1()
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
				bitmap.LoadBitmap(IDB_BITMAP15);
				CBrush brush(&bitmap);
				dc.SelectObject(&brush);
				dc.Rectangle(i*20,j*20,i*20+20,j*20+20);
			}
		}
	}
	sec=sec+3;
}

void CTalkClientDlg::OnBnClickedButton2()
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(mine[i][j]==2)
			{
				CClientDC dc(this);
				CBitmap bitmap;
				bitmap.LoadBitmap(IDB_BITMAP15);
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
void CTalkClientDlg::see_2row(int mine,int x,int y)
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
void CTalkClientDlg::OnBnClickedButton3()
{
	op=true;
}
