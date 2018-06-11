
// DrawGraphView.h : CDrawGraphView ��Ľӿ�
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

protected: // �������л�����
	CDrawGraphView();
	DECLARE_DYNCREATE(CDrawGraphView)

// ����
public:
	CDrawGraphDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDrawGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // DrawGraphView.cpp �еĵ��԰汾
inline CDrawGraphDoc* CDrawGraphView::GetDocument() const
   { return reinterpret_cast<CDrawGraphDoc*>(m_pDocument); }
#endif

