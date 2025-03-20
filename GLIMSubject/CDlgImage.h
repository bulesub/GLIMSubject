#pragma once
#include "afxdialogex.h"
#include <vector>

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	int m_nSize = 0;
	int m_nThickness = 0;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void RefreshImage();
	void UpdateDisplay();
	void ResetPoints();
private:
	/// <summary>
	/// 화면에 다시 그리기
	/// </summary>
	void InitImage();
	/// <summary>
	/// point 그리기
	/// </summary>
	/// <param name="centerX">점 중심좌표 X</param>
	/// <param name="centerY">점 중심좌표 Y</param>
	/// <param name="radius">점 반지름</param>
	void DrawPoint(int centerX, int centerY, int radius, bool isDraw = true);
	/// <summary>
	/// circle 그리기
	/// </summary>
	void DrawCircle();
	afx_msg void OnPaint();
	BOOL ValidImgPos(int x, int y);
	bool IsInCircle(int i, int j, int CenterX, int CenterY, int radius);

private:
	CImage m_image;
	CWnd* m_pParent;
	std::vector<CPoint> points;
	CPoint curMousePos;
	bool bIsMove = false;
};
