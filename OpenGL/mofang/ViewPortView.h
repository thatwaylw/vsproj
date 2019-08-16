// ViewPortView.h : interface of the CViewPortView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CViewPortView : public CView
{
protected: // create from serialization only
	CViewPortView();
	DECLARE_DYNCREATE(CViewPortView)

// Attributes
public:
	CRect m_oldRect;
	CClientDC * m_pDC;

	CViewPortDoc* GetDocument();

// Operations
public:

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
	void DrawM0(short dir,short pos);
	void DrawM1(short dir,short pos);
	void DrawM2(short dir,short pos);
	void DrawM3(short dir,short pos);
	void DrawM4(short dir,short pos);
	void DrawM5(short dir,short pos);
	void DrawPM(short dir,short pos);
	void DrawAll(short dir);

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
	afx_msg void OnSszQ();
	afx_msg void OnSszH();
	afx_msg void OnSszZ();
	afx_msg void OnNszH();
	afx_msg void OnNszQ();
	afx_msg void OnNszZ();
	afx_msg void OnSszAll();
	afx_msg void OnNszAll();
	afx_msg void OnSzLeft();
	afx_msg void OnSzMid();
	afx_msg void OnSzRight();
	afx_msg void OnSzAll();
	afx_msg void OnXzLeft();
	afx_msg void OnXzMid();
	afx_msg void OnXzRight();
	afx_msg void OnXzAll();
	afx_msg void OnZzS();
	afx_msg void OnZzZ();
	afx_msg void OnZzX();
	afx_msg void OnZzAll();
	afx_msg void OnYzS();
	afx_msg void OnYzZ();
	afx_msg void OnYzX();
	afx_msg void OnYzAll();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUndo();
	afx_msg void OnReset();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSlow();
	afx_msg void OnUpdateSlow(CCmdUI* pCmdUI);
	afx_msg void OnHlp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_busy;
	BOOL m_complete;
	BOOL m_undo;
};

#ifndef _DEBUG  // debug version in ViewPortView.cpp
inline CViewPortDoc* CViewPortView::GetDocument()
   { return (CViewPortDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORTVIEW_H__E4FB22F5_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
