
// WDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WD.h"
#include "WDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWDDlg dialog

CWDDlg::CWDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WD_DIALOG, pParent)
  , mControlConnection(&mController)
  , CControlHWBase(&mControlConnection)  
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  mMaxNumberOfLogLines = 25;

  
}

void CWDDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_RICHEDIT21, mLogCtrl);
  DDX_Control(pDX, IDC_EDIT_SEND, mSendText);
}

BEGIN_MESSAGE_MAP(CWDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON_SEND, &CWDDlg::OnBnClickedButtonSend)
  ON_WM_TIMER()
END_MESSAGE_MAP()


// CWDDlg message handlers

BOOL CWDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

  CDDConfig NewConfig;
  mController.Init(NewConfig);
  mControlConnection.Init();
  mControlConnection.SetControlHardware(this);
  mController.mControlInterfaces[0] = &mControlConnection;

  SetTimer(592, 100, NULL);

#if(0)
  CString WndTxt;
  AppedLog(_T("Regel A"), RGB(255, 0, 0), false, false);
  AppedLog(_T("Regel B"), RGB(0, 255, 0), false, false);
  AppedLog(_T("Regel C"), RGB(0, 0, 255), false, false);
  AppedLog(_T("Regel D"), RGB(127, 127, 127), false, false);

  for (int i = 1; i < 1130; i++)
  {
    WndTxt.Format(_T("Regel %d"), i);
    AppedLog(WndTxt, RGB(127, 127, 127), false, false);
  }
#endif


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWDDlg::OnTimer(UINT_PTR nIDEvent)
{
  mController.Heartbeat();

  __super::OnTimer(nIDEvent);
}

void CWDDlg::AddOutgoingByte(char Byte)
{
  AppedLog(CString(Byte, 1), RGB(0, 0, 255), false, false);
}

void CWDDlg::AddOutgoingString(char* String)
{
  AppedLog(CString(String), RGB(0, 0, 255), false, false);
}

void CWDDlg::OnBnClickedButtonSend()
{
  CString WndTxt;
  mSendText.GetWindowText(WndTxt);

  CStringA WndTxtA(WndTxt);
  WndTxtA.Append("\r\n");

  AppedLog(CString(WndTxtA), RGB(255, 0, 0), false, false);
  for (int i = 0; i < WndTxtA.GetLength(); i++)
  {  
    mParentControl->AddIncommingByte(WndTxtA.GetAt(i));
  }  
}


void CWDDlg::AppedLog(CString text, COLORREF color, bool bold, bool italic)
{
  CHARFORMAT cf = { 0 };
  cf.cbSize = sizeof(cf);
  cf.dwMask = (bold ? CFM_BOLD : 0) | (italic ? CFM_ITALIC : 0) | CFM_COLOR;
  cf.dwEffects = (bold ? CFE_BOLD : 0) | (italic ? CFE_ITALIC : 0) | ~CFE_AUTOCOLOR;
  cf.crTextColor = color;

  mLogCtrl.SetSel(-1, -1); // Set the cursor to the end of the text area and deselect everything.
  long nStartChar, nEndChar;
  mLogCtrl.GetSel(nStartChar, nEndChar);
  //mLogCtrl.ReplaceSel((nStartChar < 1 ? L"" : L"\r\n") + text); // Inserts when nothing is selected.
  mLogCtrl.ReplaceSel(text); // Inserts when nothing is selected.
  
  mLogCtrl.SetSel(nStartChar, -1);
  mLogCtrl.SetSelectionCharFormat(cf);

  //roll of extra linex
  uint32_t NrOfLines = mLogCtrl.GetLineCount();
  if (NrOfLines > mMaxNumberOfLogLines)
  {
    long TrunkEnd = mLogCtrl.LineIndex(NrOfLines - mMaxNumberOfLogLines);
    mLogCtrl.SetSel(0, TrunkEnd);
    mLogCtrl.ReplaceSel(_T("")); // Inserts when nothing is selected.
  }
}

