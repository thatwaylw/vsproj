#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	int m_nID;						//For Modalless
	CWnd * m_pParent;				//For Modalless

	DECLARE_MESSAGE_MAP()
public:
	CString m_userid;
	CString m_passwd;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL Create(void);
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedRegister();
	CString m_serverIP;
	UINT m_serverPT;
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDeluser();
};
