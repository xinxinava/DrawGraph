
// DrawGraphView.h : CDrawGraphView 类的接口
//



#pragma once
#define PI					3.1415

#define METHOD_DDA			1
#define METHOD_BRESENHAM	2
#define	FILL				3

#define PATTERN_LINE		1
#define PATTERN_CIRCLE		2
#define PATTERN_ELLIPSE		3
#define MIN                 10
const int maxn = 20;


class CDrawGraphView : public CView
{
public:
	CPoint pre_point;
	int method = METHOD_DDA;
	int pattern = PATTERN_LINE;
	bool click = false;
	bool ply = false;

protected: // 仅从序列化创建
	CDrawGraphView();
	DECLARE_DYNCREATE(CDrawGraphView)

// 特性
public:
	CDrawGraphDoc* GetDocument() const;

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
	virtual ~CDrawGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDdaLine();
	afx_msg void OnDdaCricle();
	afx_msg void OnDdaEllipse();
	afx_msg void OnBresenhamLine();
	afx_msg void OnBresenhamEllipse();
	afx_msg void OnBresenhamCircle();
	afx_msg void OnYcoherenceFill();
};

#ifndef _DEBUG  // DrawGraphView.cpp 中的调试版本
inline CDrawGraphDoc* CDrawGraphView::GetDocument() const
   { return reinterpret_cast<CDrawGraphDoc*>(m_pDocument); }
#endif

