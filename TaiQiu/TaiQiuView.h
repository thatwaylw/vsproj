// TaiQiuView.h : CTaiQiuView 类的接口
//


#pragma once
#include "atltypes.h"
#include "TaiQiuDoc.h"

#include "MyASock.h"
#include "LoginDlg.h"
#include "PlayNetDlg.h"

#define BALLNUM 16
typedef struct
{
	float xpos;
	float ypos;
	float Mat[3][3];
	float speed;
	float dir;
	BOOL bUP;
}TBall;

class CTaiQiuView : public CView
{
protected: // 仅从序列化创建
	CTaiQiuView();
	DECLARE_DYNCREATE(CTaiQiuView)

// 属性
public:
	CTaiQiuDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTaiQiuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Init(void);
	BOOL bSetupPixelFormat(void);
	void DrawScene(void);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CRect m_oldRect;
	CClientDC * m_pDC;

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL bPlaying, bNewGame;
	float XRot, YRot, ZRot;
	TBall Balls[BALLNUM];
	BOOL pre_bs[BALLNUM];
	BOOL bAllStop;
	BOOL haveCrossing(int i);
	void DrawBall(int ballNum);
	void RollBall(int ballNum, float alfa, float beta);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawHit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	void DrawStat(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTable(void);
	void DrawPartTable(void);
	void DoGodJob();
	void NewGame();
	void HitingBall();
	void DrawArc(float r, float s, float a, float x, float y);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	void ShowHints(char * hints);
	void PlayEffect(int idx);
	DWORD Eff_t;
	afx_msg void OnDestroy();

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void AddChat(char * str);
	afx_msg void OnPlaynet();

	CMyASock * pSock;
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);

	CLoginDlg * m_pLoginDlg;
	CPlayNetDlg * m_pPlayNetDlg;
	void InitConnection(void);
	CSockAddr Serverpsa;
	CString userid;
	void DoLogin(char * buf);
	void DoRegister(char * buf);
	void DoUserList(char * buf);
	void DoMoreList(char * buf);
	void DoChat(char * buf);
	void DoGameSetup(char * buf);
	int cur_desk;
	char p_side;
	char win_side;
	BOOL bSelfBegin, bOthrBegin;
	BOOL timetosendmove;
	BOOL your_turn;
	void DoGameStart(char * buf);
	void DoMoveInfo(char * buf);
	void DoHitBall(char * buf);
	void SendBallPos(char msgtype);
	void DoBallPos(char * buf);
	void NewHiting(void);
};

#ifndef _DEBUG  // TaiQiuView.cpp 的调试版本
inline CTaiQiuDoc* CTaiQiuView::GetDocument() const
   { return reinterpret_cast<CTaiQiuDoc*>(m_pDocument); }
#endif

