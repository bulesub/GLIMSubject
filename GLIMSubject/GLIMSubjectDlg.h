
// GLIMSubjectDlg.h: 헤더 파일
//

#pragma once
#include "CDlgImage.h"
#include <iostream>

// CGLIMSubjectDlg 대화 상자
class CGLIMSubjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CGLIMSubjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
// 변수
	CDlgImage* m_pDlgImage;
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMSUBJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEditCircleSize();
public:
	afx_msg void OnEnChangeEditCircleThickness();
	int m_nSize;
	int m_nThickness;
	afx_msg void OnBnClickedBtnReset();
};
