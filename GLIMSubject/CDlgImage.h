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
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void RefreshImage();
	void UpdateDisplay();
	void ResetPoints();
	void RandomPoints();
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
private:
	/// <summary>
	/// 화면에 다시 그리기
	/// </summary>
	void InitImage();
	afx_msg void OnPaint();
	BOOL ValidImgPos(int x, int y);
	/// <summary>
	/// 현재 점이 원 내부에 있는지 확인
	/// </summary>
	/// <param name="i">확인할 점 X</param>
	/// <param name="j">확인할 점 Y</param>
	/// <param name="CenterX">원의 중심 X</param>
	/// <param name="CenterY">원의 중심 Y</param>
	/// <param name="radius">원의 반지름</param>
	/// <returns></returns>
	bool IsInCircle(int i, int j, int CenterX, int CenterY, int radius);
	/// <summary>
	/// 세 점을 지나는 원의 중심과 반지름을 구하는 함수
	/// </summary>
	/// <param name="p1">첫 번째 점</param>
	/// <param name="p2">두 번째 점</param>
	/// <param name="p3">세 번째 점</param>
	/// <param name="center">원의 중심 점 결과를 받을 인수</param>
	/// <param name="radius">원의 반지름 결과를 받을 인수</param>
	/// <returns></returns>
	bool FindCircle(const std::vector<CPoint>& points, CPoint& center, int& radius);

private:
	CImage m_image;
	CWnd* m_pParent;
	std::vector<CPoint> points;
	CPoint curMousePos;
	bool bIsMove = false;
};
