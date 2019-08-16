// ViewPortView.h : interface of the CViewPortView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SepDlg.h"
#include "FapDlg.h"
#include "ExpDlg.h"
#include "VisDlg.h"
#include "PlayAniDlg.h"

#include "ViewPortDoc.h"

class CViewPortView : public CView
{
protected: // create from serialization only
	CViewPortView();
	DECLARE_DYNCREATE(CViewPortView)

// Attributes
public:
	CRect m_oldRect;
	CClientDC * m_pDC;
	CString AniFileName;

	CViewPortDoc * GetDocument();

// Operations
public:
	CSepDlg * m_pSepDlg;
	CFapDlg * m_pFapDlg;
	CExpDlg * m_pExpDlg;
	CVisDlg * m_pVisDlg;
	CPlayAniDlg * m_pPlayAniDlg;

	void Init();
	BOOL bSetupPixelFormat(void);
	void DrawScene(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPortView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReDrawScene();
	int GetSep(int i);
	void ResetFaceModel();
	void LoadFaceModel();
	void GetModelSize();
	void DrawFace();
	virtual ~CViewPortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewPortView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMgrid();
	afx_msg void OnUpdateMgrid(CCmdUI* pCmdUI);
	afx_msg void OnMtexture();
	afx_msg void OnUpdateMtexture(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMrott();
	afx_msg void OnUpdateMrott(CCmdUI* pCmdUI);
	afx_msg void OnMorig();
	afx_msg void OnMsep();
	afx_msg void OnMfap();
	afx_msg void OnMexp();
	afx_msg void OnMvis();
	afx_msg void OnAniFileOpen();
	afx_msg void OnPlayAni();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ViewPortView.cpp
inline CViewPortDoc* CViewPortView::GetDocument()
   { return (CViewPortDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
