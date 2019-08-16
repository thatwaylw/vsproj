#pragma once
#include "afxcmn.h"


// CPlayNetDlg �Ի���
#define MAXPAIR 20

class CPlayNetDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayNetDlg)

public:
	CPlayNetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlayNetDlg();

// �Ի�������
	enum { IDD = IDD_PLAYNETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	int m_nID;						//For Modalless
	CWnd * m_pParent;				//For Modalless

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL Create(void);
protected:
	virtual void PostNcDestroy();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CImageList m_ImgList;
	CListCtrl m_desk;
	CListCtrl m_lobby;
	CString m_uid;
	CString m_info;
	CString m_talk;
	afx_msg void OnBnClickedJoin();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedSendtalk();
	void AppendMesg(CString mesg);
	afx_msg void OnBnClickedRefresh();
	virtual BOOL OnInitDialog();
};
