// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "GLIMSubject.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include "GLIMSubjectDlg.h"

#include <iostream>

#define IMAGE_SIZE_X WINDOW_SIZE_X - 230
#define IMAGE_SIZE_Y WINDOW_SIZE_Y
#define MOUSE_LEFT_CLICK 513

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, WINDOW_SIZE_Y, WINDOW_SIZE_Y);
	InitImage();
	points = std::vector<CPoint>();
	curMousePos = CPoint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CDlgImage::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//std::cout << "Message : " << message << " ";

	if (message == MOUSE_LEFT_CLICK)
	{

		if (points.size() < 3)
			points.push_back(CPoint(curMousePos.x, curMousePos.y));
		else
			bIsMove = true;
		RefreshImage();
	}

	return CDialogEx::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CDlgImage::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnMouseMove(nFlags, point);
	curMousePos = point;

	if (nFlags == 1 && bIsMove)
	{
		int pointIndex = -1;
		for (int i = 0; i < points.size(); i++)
		{
			if (IsInCircle(point.x, point.y, points[i].x, points[i].y, m_nSize))
			{
				pointIndex = i;
				break;
			}
		}

		if (pointIndex != -1)
		{
			points[pointIndex] = point;
			RefreshImage();
		}
	}
	else bIsMove = false;
	
	//std::cout << "Flag : " << nFlags << " Mouse Pos : " << point.x << " " << point.y << std::endl;
}

void CDlgImage::RefreshImage()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	for (const CPoint& point : points)
		DrawPoint(point.x, point.y, m_nSize);

	Invalidate();
	UpdateDisplay();
}

void CDlgImage::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CDlgImage::ResetPoints()
{
	points.clear();
}

void CDlgImage::InitImage()
{
	int nWidth = IMAGE_SIZE_X;
	int nHeight = IMAGE_SIZE_Y;
	int nBpp = 8;

	if (m_image) 
	{
		m_image.Destroy();
	}

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CDlgImage::DrawPoint(int centerX, int centerY, int radius, bool isDraw)
{
	int nPitch = m_image.GetPitch();

	for (int j = centerY - radius; j < centerY + radius; j++)
	{
		for (int i = centerX - radius; i < centerX + radius; i++)
			if (ValidImgPos(i, j) && 
				IsInCircle(i, j, centerX, centerY, m_nSize))
				((unsigned char*)m_image.GetBits())[j * nPitch + i] = (isDraw) ? 0x00 : 0xff;
	}
}

void CDlgImage::DrawCircle()
{
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_image) m_image.Draw(dc, 0, 0);
}

BOOL CDlgImage::ValidImgPos(int x, int y)
{
	BOOL bRect = false;

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

bool CDlgImage::IsInCircle(int i, int j, int centerX, int centerY, int radius)
{
	double dX = i - centerX;
	double dY = j - centerY;
	double dDist = dX * dX + dY * dY;

	if (dDist < radius * radius) return true;

	return false;
}
