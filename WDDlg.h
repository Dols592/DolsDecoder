
// WDDlg.h : header file
//

#pragma once

#include <stdint.h>

#include "Controller.h"
#include "ControlHWBase.h"
#include "ControlConnection.h"

#include "MainInterface.h"

class CWDDlg : public CDialogEx, public CControlHWBase
{
public: // Constructor
	CWDDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WD_DIALOG };
#endif

protected: //CDialogEx Overrides
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
  virtual BOOL OnInitDialog();

public: //CControlHWBase virtuals
  virtual void AddOutgoingByte(char Byte);
  virtual void AddOutgoingString(char* String);

protected: //Help functions
  void AppedLog(CString text, COLORREF color, bool bold, bool italic);

protected: //Messages
  DECLARE_MESSAGE_MAP()
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnBnClickedButtonSend();

protected: //Dialog Items
  CRichEditCtrl mLogCtrl;
  CEdit mSendText;

protected: //controls
  CController mController;
  CControlConnection mControlConnection;
  CMainInterface mMainInterface;

protected: //Variables
	HICON m_hIcon;
  uint32_t mMaxNumberOfLogLines;

};
