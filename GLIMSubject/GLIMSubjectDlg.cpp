﻿
// GLIMSubjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIMSubject.h"
#include "GLIMSubjectDlg.h"
#include "afxdialogex.h"

#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CGLIMSubjectDlg 대화 상자



CGLIMSubjectDlg::CGLIMSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMSUBJECT_DIALOG, pParent)
	, m_nSize(0)
	, m_nThickness(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_SIZE, m_nSize);
	//  DDX_Control(pDX, IDC_EDIT_CIRCLE_THICKNESS, m_nThickness);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_THICKNESS, m_nThickness);
}

BEGIN_MESSAGE_MAP(CGLIMSubjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_CIRCLE_SIZE, &CGLIMSubjectDlg::OnEnChangeEditCircleSize)
	ON_EN_CHANGE(IDC_EDIT_CIRCLE_THICKNESS, &CGLIMSubjectDlg::OnEnChangeEditCircleThickness)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGLIMSubjectDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CGLIMSubjectDlg::OnBnClickedBtnRandom)
END_MESSAGE_MAP()


// CGLIMSubjectDlg 메시지 처리기

BOOL CGLIMSubjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 현재 Dialog 크기, 위치 변경
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(nWidth / 2 - WINDOW_SIZE_X / 2, nHeight / 2 - WINDOW_SIZE_Y / 2, 
				WINDOW_SIZE_X, WINDOW_SIZE_Y);

	// Child Dialog 크기, 위치 변경
	m_pDlgImage = new CDlgImage(this);
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, WINDOW_SIZE_X - 230, WINDOW_SIZE_Y - 40);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMSubjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMSubjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGLIMSubjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGLIMSubjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SAFE_DELETE(m_pDlgImage);
}


void CGLIMSubjectDlg::OnEnChangeEditCircleSize()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	m_pDlgImage->m_nSize = m_nSize;
	UpdateData(false);
	m_pDlgImage->RefreshImage();
}

void CGLIMSubjectDlg::OnEnChangeEditCircleThickness()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	m_pDlgImage->m_nThickness = m_nThickness;
	UpdateData(false);
	m_pDlgImage->RefreshImage();
}

void CGLIMSubjectDlg::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	m_nSize = 0;
	m_nThickness = 0;
	UpdateData(false);
	m_pDlgImage->ResetPoints();
	m_pDlgImage->RefreshImage();
}

void RandomPoints(CDlgImage* dlgImage)
{
	dlgImage->RandomPoints();
}

void CGLIMSubjectDlg::OnBnClickedBtnRandom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::thread _thread = std::thread(RandomPoints, m_pDlgImage);
	_thread.detach();
}

void CGLIMSubjectDlg::UpdateStaticInfo(const std::vector<CPoint>& points)
{
	int size = points.size();
	CString info;

	switch (size)
	{
	case 3:
		info.Format(_T("x:%d y:%d"), points[2].x, points[2].y);
		SetDlgItemText(IDC_STATIC_P3_INFO, info);

	case 2:
		info.Format(_T("x:%d y:%d"), points[1].x, points[1].y);
		SetDlgItemText(IDC_STATIC_P2_INFO, info);

	case 1:
		info.Format(_T("x:%d y:%d"), points[0].x, points[0].y);
		SetDlgItemText(IDC_STATIC_P1_INFO, info);
		break;

	default:
		info = _T("x:   y:   ");
		SetDlgItemText(IDC_STATIC_P1_INFO, info);
		SetDlgItemText(IDC_STATIC_P2_INFO, info);
		SetDlgItemText(IDC_STATIC_P3_INFO, info);
	}
}
