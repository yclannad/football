
// FootballRobotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FootballRobot.h"
#include "FootballRobotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange ( CDataExchange* pDX ); // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx ( CAboutDlg::IDD )
{
}

void CAboutDlg::DoDataExchange ( CDataExchange* pDX )
{
    CDialogEx::DoDataExchange ( pDX );
}

BEGIN_MESSAGE_MAP ( CAboutDlg, CDialogEx )
END_MESSAGE_MAP()


// CFootballRobotDlg 对话框



CFootballRobotDlg::CFootballRobotDlg ( CWnd* pParent /*=NULL*/ )
    : CDialogEx ( CFootballRobotDlg::IDD, pParent )
    , m_edt_accountName ( _T ( "robot" ) )
    , m_edt_accountPwd ( _T ( "123456" ) )
    , m_edt_loginNum ( 1 )
    , m_edt_loginServer ( _T ( "192.168.20.54:8080" ) )
    , m_edt_actionDelay ( 500 )
{
    m_hIcon = AfxGetApp()->LoadIcon ( IDR_MAINFRAME );
}

void CFootballRobotDlg::DoDataExchange ( CDataExchange* pDX )
{
    CDialogEx::DoDataExchange ( pDX );
    DDX_Control ( pDX, IDL_ROBOTLIST, m_listCtrl );
    DDX_Text ( pDX, IDE_ROBOTACCOUNTNAME, m_edt_accountName );
    DDV_MaxChars ( pDX, m_edt_accountName, 255 );
    DDX_Text ( pDX, IDE_ROBOTACCOUNTPWD, m_edt_accountPwd );
    DDV_MaxChars ( pDX, m_edt_accountPwd, 255 );
    DDX_Text ( pDX, IDE_NUMBER, m_edt_loginNum );
    DDV_MinMaxInt ( pDX, m_edt_loginNum, 1, 9999 );
    DDX_Text ( pDX, IDE_LOGINSERVER, m_edt_loginServer );
    DDV_MaxChars ( pDX, m_edt_loginServer, 255 );
    DDX_Text ( pDX, IDE_ACTIONDELAY, m_edt_actionDelay );
    DDV_MinMaxInt ( pDX, m_edt_actionDelay, 1, 10000 );
}

BEGIN_MESSAGE_MAP ( CFootballRobotDlg, CDialogEx )
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CFootballRobotDlg 消息处理程序

BOOL CFootballRobotDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    // 将“关于...”菜单项添加到系统菜单中。
    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT ( ( IDM_ABOUTBOX & 0xFFF0 ) == IDM_ABOUTBOX );
    ASSERT ( IDM_ABOUTBOX < 0xF000 );
    CMenu* pSysMenu = GetSystemMenu ( FALSE );

    if ( pSysMenu != NULL ) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString ( IDS_ABOUTBOX );
        ASSERT ( bNameValid );

        if ( !strAboutMenu.IsEmpty() ) {
            pSysMenu->AppendMenu ( MF_SEPARATOR );
            pSysMenu->AppendMenu ( MF_STRING, IDM_ABOUTBOX, strAboutMenu );
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon ( m_hIcon, TRUE );      // 设置大图标
    SetIcon ( m_hIcon, FALSE );     // 设置小图标
    ShowWindow ( SW_NORMAL );
    // 初始化列表头信息
    m_listCtrl.InsertColumn ( 1, "ID" );        // ID
    m_listCtrl.InsertColumn ( 2, "AccountName" ); // 账号名
    m_listCtrl.InsertColumn ( 3, "AccountPwd" ); // 帐号密码
    m_listCtrl.InsertColumn ( 4, "TeamID" );    // 队伍ID
    m_listCtrl.InsertColumn ( 5, "TeamName" );  // 队伍名
    m_listCtrl.InsertColumn ( 6, "Coin" );      // 银币
    m_listCtrl.InsertColumn ( 7, "Diamond" );   // 钻石
    m_listCtrl.InsertColumn ( 8, "Action" );    // 行为
    m_listCtrl.InsertColumn ( 9, "Upload" );    // 上传
    m_listCtrl.InsertColumn ( 10, "Download" ); // 下载
    m_listCtrl.AutoSize();
    CMyWebSocket web;
    web.Init();
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFootballRobotDlg::OnSysCommand ( UINT nID, LPARAM lParam )
{
    if ( ( nID & 0xFFF0 ) == IDM_ABOUTBOX ) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else {
        CDialogEx::OnSysCommand ( nID, lParam );
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFootballRobotDlg::OnPaint()
{
    if ( IsIconic() ) {
        CPaintDC dc ( this ); // 用于绘制的设备上下文
        SendMessage ( WM_ICONERASEBKGND, reinterpret_cast<WPARAM> ( dc.GetSafeHdc() ), 0 );
        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics ( SM_CXICON );
        int cyIcon = GetSystemMetrics ( SM_CYICON );
        CRect rect;
        GetClientRect ( &rect );
        int x = ( rect.Width() - cxIcon + 1 ) / 2;
        int y = ( rect.Height() - cyIcon + 1 ) / 2;
        // 绘制图标
        dc.DrawIcon ( x, y, m_hIcon );
    }
    else {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFootballRobotDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR> ( m_hIcon );
}
