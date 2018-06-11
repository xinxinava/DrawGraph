
// DrawGraphView.cpp : CDrawGraphView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawGraph.h"
#endif

#include "DrawGraphDoc.h"
#include "DrawGraphView.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <stack>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class AE
{
public:
	double x;
	double ymax;
	double dx;
	AE *next;
	AE() {}
	AE(double xa, double ya, double k):x(xa),ymax(ya),dx(k) {next = NULL; }
};

vector<CPoint> V;

// CDrawGraphView

IMPLEMENT_DYNCREATE(CDrawGraphView, CView)

BEGIN_MESSAGE_MAP(CDrawGraphView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DDA_LINE, &CDrawGraphView::OnDdaLine)
	ON_COMMAND(ID_DDA_CRICLE, &CDrawGraphView::OnDdaCricle)
	ON_COMMAND(ID_DDA_ELLIPSE, &CDrawGraphView::OnDdaEllipse)
	ON_COMMAND(ID_BRESENHAM_LINE, &CDrawGraphView::OnBresenhamLine)
	ON_COMMAND(ID_BRESENHAM_ELLIPSE, &CDrawGraphView::OnBresenhamEllipse)
	ON_COMMAND(ID_BRESENHAM_CIRCLE, &CDrawGraphView::OnBresenhamCircle)
	ON_COMMAND(ID_YCOHERENCE_FILL, &CDrawGraphView::OnYcoherenceFill)
END_MESSAGE_MAP()

// CDrawGraphView 构造/析构

CDrawGraphView::CDrawGraphView()
{
	// TODO:  在此处添加构造代码

}

CDrawGraphView::~CDrawGraphView()
{
}

BOOL CDrawGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawGraphView 绘制
void DDA_Line(CDC *, int, int, int, int);

void CDrawGraphView::OnDraw(CDC* pDC)
{
	CDrawGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CDrawGraphView 打印

BOOL CDrawGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CDrawGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CDrawGraphView 诊断

#ifdef _DEBUG
void CDrawGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawGraphDoc* CDrawGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawGraphDoc)));
	return (CDrawGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawGraphView 消息处理程序

void DDA_Line(CDC *p, int xa, int ya, int xb, int yb)
{
	int step, k;
	double xi, yi, x = xa, y = ya;
	int dx = xb - xa, dy = yb - ya;
	int c = RGB(0, 0, 25);
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	xi = dx / (float)step;
	yi = dy / (float)step;

	p->SetPixel(round(x), round(y), c);
	for (k = 0; k < step; k++)
	{
		x += xi;
		y += yi;
		p->SetPixel(round(x), round(y), c);
	}
	// TODO:  在此添加命令处理程序代码
}




void DDA_Circle(CDC *p, int xa, int ya, int xb, int yb)
{
//	p->SelectObject(CPen(PS_DASH, 10, RGB(0, 0, 0)));
	double r = sqrt(pow((double)(xb - xa), 2) + pow((double)(yb - ya), 2));
	double x = xa + r, y = ya;
	double theta, delta = 1.0 / r;
	int c = RGB(0, 0, 0);
	for (theta = 0; theta <= 2 * 3.1416; theta += delta)
	{
		p->SetPixel(round(x), round(y), c);
		x = x - (y - ya) * delta;
		y = y + (x - xa)* delta;
	//	int _ = x;
	}
}

void Bresenham_Line(CDC *p, int xa, int ya, int xb, int yb)
{
	if (xb < xa)
	{
		int t = xb;
		xb = xa;
		xa = t;
		t = ya;
		ya = yb;
		yb = t;
	}
	int dx = xb - xa, dy = yb - ya, step, k;
	double x = xa, y = ya, d;
	k = dy / (double)dx;
	int c = RGB(255, 0, 0);
	p->SetPixel(round(x), round(y), c);

	if (k >= 0 && k <= 1)
	{
		step = abs(xb - xa);
		d = 0.5 - k;
		for (int i = 0; i < step; i++)
		{
			if (d < 0)
			{
				x += 1;
				y += 1;
				d = d + 1 - k;
			}
			else
			{
				x += 1;
				d = d - k;
			}
			p->SetPixel(round(x), round(y), c);
		}
	}
	if (k > 1)
	{
		step = abs(ya - yb);
		d = 1 - 0.5 * k;
		for (int i = 0; i < step; i++)
		{
			if (d < 0)
			{
				y += 1;
				d = d + 1;
			}
			else
			{
				y += 1;
				x += 1;
				d = d + 1 - k;
			}
			p->SetPixel(round(x), round(y), c);
		}
	}
	if (k <= -1)
	{
		step = abs(ya - yb);
		d = -1 - 0.5 * k;
		for (int i = 0; i < step; i++)
		{
			if (d < 0)
			{
				y -= 1;
				x += 1;
				d = d - 1 - k;
			}
			else
			{
				y -= 1;
				d = d - 1;
			}
			p->SetPixel(round(x), round(y), c);
		}
	}
	if (k > -1 && k < 0)
	{
		step = abs(xa - xb);
		d = -0.5 - k;
		for (int i = 0; i < step; i++)
		{
			if (d < 0)
			{
				x += 1;
				d = d - k;
			}
			else
			{
				x += 1;
				y -= 1;
				d = d - 1 - k;
			}
			p->SetPixel(round(x), round(y), c);
		}
	}
}

void Bresenham_Circle(CDC *p, int xa, int ya, int xb, int yb)
{
	double r = sqrt(pow((double)(xa - xb), 2) + pow((double)(ya - yb), 2));
	double x = 0, y = r;
	double d = 1.25 - r;
	int c = RGB(0, 255, 0);
	while (x <= y)
	{
		p->SetPixel(round(x+xa), round(y + ya), c);
		p->SetPixel(round(y + xa), round(x + ya), c);
		p->SetPixel(round(y + xa), round(-x + ya), c);
		p->SetPixel(round(x + xa), round(-y + ya), c);
		p->SetPixel(round(-x + xa), round(-y + ya), c);
		p->SetPixel(round(-y + xa), round(-x + ya), c);
		p->SetPixel(round(-y + xa), round(x + ya), c);
		p->SetPixel(round(-x + xa), round(y + ya), c);
		if (d <= 0)
		{
			d = d + 2 * x - 3;
			x = x + 1;
		}
		else
		{
			d = d + 2 * (x - y) + 5;
			x += 1;
			y -= 1;
		}
	}

}

void Bresenham_Ellipse(CDC *p, int xa, int ya, int xb, int yb)
{
	double a = abs(xb - xa) / 2, b = abs(yb - ya) / 2;
	double x = 0, y = b;
	double d1 = b * b + a * a * (-b + 0.25);
	double d2 = sqrt( b * (x + 0.5)) * 2 + a *(y - 1) * 2 - a * b;
	int c = RGB(255, 0, 255);
	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 <= 0)
		{
			d1 = d1 + b * b * (2 * x + 3);
			x += 1;
		}
		else
		{
			d1 = d1 + b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			x += 1;
			y -= 1;
		}
		p->SetPixel(round(x + xa), round(y + ya), c);
		p->SetPixel(round(-x + xa), round(y + ya), c);
		p->SetPixel(round(x + xa), round(-y + ya), c);
		p->SetPixel(round(-x + xa), round(-y + ya), c);
	}
	while (y >= 0)
	{
		if (d2 <= 0)
		{
			d2 = d2 + b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x += 1;
			y -= 1;
		}
		else
		{
			d2 = d2 + a * a * (-2 * y + 3);
			y -= 1;
		}
		p->SetPixel(round(x + xa), round(y + ya), c);
		p->SetPixel(round(-x + xa), round(y + ya), c);
		p->SetPixel(round(x + xa), round(-y + ya), c);
		p->SetPixel(round(-x + xa), round(-y + ya), c);
	}

}

/**************Y连贯性算法****************/

double distance(CPoint &a, CPoint &b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void insert(vector<AE> &v,CPoint &a,CPoint &b)
{
	CPoint p1, p2;
	if (a.y >= b.y) p1 = b, p2 = a;
	else p1 = a, p2 = b;
	AE x = AE(p1.x, p2.y, double(p1.x - p2.x) / double(p1.y - p2.y));
	v.push_back(x);
}

bool cmp(AE &a, AE &b)
{
	if (a.x != b.x)
		return a.x < b.x;
	return a.dx < b.dx;
}

void YCoherence(CDC *pDC, CPoint point, bool drawing)
{
	int c = RGB(0, 0, 0);
	if (drawing)
	{
		if (V.empty() != true && distance(V.front(), point) <= MIN)
		{
			//填充
			cout << "if" << endl;
			DDA_Line(pDC, point.x, point.y, V.front().x, V.front().y);
			map<int, vector<AE> > ET;
			int y_max = V.front().y, y_min = V.front().y;
			cout << "y_max" << y_max << endl;
			DDA_Line(pDC, V.back().x, V.back().y, V.front().x, V.front().y);

			insert(ET[min(V.front().y, V.back().y)], V.front(), V.back());
			cout << "(" << V.front().x << "," << V.front().y << ")" << endl;

			for (vector<CPoint>::iterator i = V.begin() + 1; i != V.end(); i++)
			{
				cout << "(" << i->x << "," << i->y << ")" << endl;
				y_max = max(y_max, i->y);
				y_min = min(y_min, i->y);

				insert(ET[min((i - 1)->y, i->y)], *i, *(i-1));
			}

			cout << "***************ET*****************start" << endl;

			for (int i = y_min; i < y_max; i++)
			{
				if (ET[i].empty()) continue;
				cout << "y = " << i;
				sort(ET[i].begin(), ET[i].end(), cmp);
				for (vector<AE>::iterator j = ET[i].begin(); j != ET[i].end(); j++)
					cout << "->[" << j->x << "," << j->ymax << "," << j->dx << "]";
				cout << endl;
			}
			cout << "****************ET******************end" << endl;

			vector<AE> AET;
			for (int i = y_min; i < y_max; i++)
			{
				bool draw = false;
				for (vector<AE>::iterator r = AET.begin(); r != AET.end(); r++)
				{
					cout << ";" << endl;
					if (draw)
						DDA_Line(pDC, round(r->x), i, round((r - 1)->x), i);
					draw = !draw;
				}
				cout << "erase" << endl;
				for (vector<AE>::iterator r = AET.begin(); r != AET.end();)
				{
					r->x += r->dx;
					if (r->ymax == i)  
						r = AET.erase(r);
					else
						r++;
				
				}
				cout << "erase_end" << endl;

				if (!ET[i].empty())
				{
					cout << "ET[" << i << "]=" << ET[i].empty() << endl;
					cout << "ET[" << i << "]";
					for (vector<AE>::iterator r = ET[i].begin(); r != ET[i].end(); r++)
						cout << "->(" << r->x << "," << r->ymax << "," << r->dx << ")";
					cout << endl;
				//	cout << "ET_end=[" << ET[i].end()->x << ET[i].end()->ymax << ET[i].end()->dx << "]" << endl;
					for (vector<AE>::iterator r = ET[i].begin(); r != ET[i].end(); r++)
					{
						cout << "r={" <<r->x << "," << r->ymax << "," <<  r->dx << "}" << endl;
						AET.push_back(*r);
					}
					cout << "r_end" << endl;
				}

				cout << "1" << endl;
				sort(AET.begin(), AET.end(), cmp);
				cout << "2" << endl;

				cout << "*******************AET***************start" << endl;
				for (vector<AE>::iterator r = AET.begin(); r != AET.end(); r++)
					cout << "[" << r->x << "," << r->ymax << "," << r->dx << "]";
				cout << endl;
				cout << "*******************AET**************end" << endl;
			}
			V.clear();
			drawing = false;
			
		}
		else
		{
			//加点，连线
			cout << "else" << endl;
			pDC->SetPixel(point , c);
			if (!V.empty())
				DDA_Line(pDC, V.back().x, V.back().y, point.x, point.y);
			V.push_back(point);
			for (vector<CPoint>::iterator i = V.begin(); i != V.end(); i++)
			{
				cout << i->x << "  " << i->y << endl;
			}
		}
	}
	
}

void CDrawGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	pre_point = point;
	click = true;
	CView::OnLButtonDown(nFlags, point);
}

int coodinate[maxn][2];
int c = 0;

void Point(int x, int y)
{
	coodinate[c++][0] = x;
	coodinate[c++][1] = y;
}

void CDrawGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	click = false;
	CDC *pDC = GetDC();

	if (method == METHOD_DDA && pattern == PATTERN_LINE)
		DDA_Line(pDC, pre_point.x, pre_point.y, point.x, point.y);
	if (method == METHOD_DDA && pattern == PATTERN_CIRCLE)
		DDA_Circle(pDC, pre_point.x, pre_point.y, point.x, point.y);
	//if (method == METHOD_DDA && pattern == PATTERN_ELLIPSE)
	//	DDA_Ellipse(pDC, pre_point.x, pre_point.y, point.x, point.y);
	if (method == METHOD_BRESENHAM && pattern == PATTERN_LINE)
		Bresenham_Line(pDC, pre_point.x, pre_point.y, point.x, point.y);
	if (method == METHOD_BRESENHAM && pattern == PATTERN_CIRCLE)
		Bresenham_Circle(pDC, pre_point.x, pre_point.y, point.x, point.y);
	if (method == METHOD_BRESENHAM && pattern == PATTERN_ELLIPSE)
		Bresenham_Ellipse (pDC, pre_point.x, pre_point.y, point.x, point.y);
	if (method == FILL)
		YCoherence(pDC, point, ply);
		
	CView::OnLButtonUp(nFlags, point);
}

void CDrawGraphView::OnDdaLine()
{
	method = METHOD_DDA;
	pattern = PATTERN_LINE;

	// TODO:  在此添加命令处理程序代码
}


void CDrawGraphView::OnDdaCricle()
{
	// TODO:  在此添加命令处理程序代码
	method = METHOD_DDA;
	pattern = PATTERN_CIRCLE;
}


void CDrawGraphView::OnDdaEllipse()
{
	// TODO:  在此添加命令处理程序代码
	method = METHOD_DDA;
	pattern = PATTERN_ELLIPSE;
}


void CDrawGraphView::OnBresenhamLine()
{
	// TODO:  在此添加命令处理程序代码
	method = METHOD_BRESENHAM;
	pattern = PATTERN_LINE;
}

void CDrawGraphView::OnBresenhamCircle()
{
	// TODO:  在此添加命令处理程序代码
	method = METHOD_BRESENHAM;
	pattern = PATTERN_CIRCLE;
}

void CDrawGraphView::OnBresenhamEllipse()
{
	// TODO:  在此添加命令处理程序代码
	method = METHOD_BRESENHAM;
	pattern = PATTERN_ELLIPSE;
}





void CDrawGraphView::OnYcoherenceFill()
{
	// TODO: Add your command handler code here
	method = FILL;
	ply = true;
}
