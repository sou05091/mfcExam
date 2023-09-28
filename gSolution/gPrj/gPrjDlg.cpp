
// gPrjDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include "Process.h"
#include <chrono>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTSartup /subsystem:console")

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
using namespace std;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CgPrjDlg ��ȭ ����



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
//	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_PROJECT, &CgPrjDlg::OnBnClickedBtnProject)
END_MESSAGE_MAP()


// CgPrjDlg �޽��� ó����

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_DLGIMAGE, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

//void CgPrjDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// �������� �׸��ϴ�.
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialogEx::OnPaint();
//	}
//}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_pDlgImage) delete m_pDlgImage;
	if (m_pDlgImgResult) delete m_pDlgImgResult;
}


void CgPrjDlg::callFunc(int n)
{
	std::cout << n << std::endl;
}

void CgPrjDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth*nHeight);

	for (int k = 0; k < MAX_POINT; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y*nPitch + x] = rand()%0xff;
	}

	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j*nPitch + i] != 0) {
				if (m_pDlgImgResult->m_nDataCount < MAX_POINT) {
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
					cout << nIndex << ":" << i << "," << j << endl;
				}
			}
		}
	}

	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();
}


void CgPrjDlg::OnBnClickedBtnProcess()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CProcess process;

	// ���۽ð�
	auto start = std::chrono::system_clock::now();
	int nRet = process.getStarInfo(&m_pDlgImage->m_Image);
	// ������ �ð�
	auto end = std::chrono::system_clock::now();
	// ������ �ð� - ���۽ð� = �ҿ�ð�
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	
	cout << nRet << "\t" << millisec.count() << endl;
}


void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth*nHeight);

	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j*nPitch + i] = rand()%0xff;
		}
	}
	m_pDlgImage->Invalidate();
}


void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	int nTh = 0x80;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j*nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;

	m_pDlgImage->Invalidate();
}

void CgPrjDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_pDlgImage->m_Image.Draw(dc, 0, 0);

}

void CgPrjDlg::OnBnClickedBtnProject()
{
	//srand((unsigned int)time(NULL));

	int nRadius = 20;	//���� ������

	// �̹��� ũ��
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();

	int nMaxX = nWidth - nRadius * 2;
	int nMaxY = nHeight - nRadius * 2;

	// ������ ��ġ�� ���� �׸��� ���� ���� ��ǥ
	int nSttX = rand()% nMaxX;
	int nSttY = rand()% nMaxY;

	int nGray = 80;
	int nYellow = RGB(200, 200, 0);

	int thickness = 2; // ū���� �β�

	int nPitch = m_pDlgImage->m_Image.GetPitch();

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);

	drawCircle(fm, nSttX, nSttY, nRadius, nGray);
	drawCross(fm, nSttX + nRadius, nSttY + nRadius);
	drawHollowCircle(fm, nSttX + nRadius, nSttY + nRadius, nRadius*2, nRadius, thickness, nYellow); // ū �� �׸���

	
	UpdateDisplay();
	cout << nSttX << "," << nSttY << endl;

}

void CgPrjDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_pDlgImage->m_Image.GetPitch();


	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j*nPitch + i] = nGray;
		}
	}
	cout << nCenterX << "," << nCenterY << endl;

}

bool CgPrjDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
}

void CgPrjDlg::drawCross(unsigned char* fm, int centerX, int centerY)
{
	int width = 640;
	int height = 480;
	int thickness = 2;
	unsigned char color = 0xff;

	// ���μ� �׸���
	for (int y = centerY - thickness / 2; y < centerY + thickness / 2; y++){
		for (int x = centerX - width / 2; x < centerX + width / 2; x++){
			if (x >= 0 && x < width && y >= 0 && y < height){
				fm[y * width + x] = color;
			}
		}
	}

	// ���μ� �׸���
	for (int y = centerY - height / 2; y < centerY + height / 2; y++) {
		for (int x = centerX - thickness / 2; x < centerX + thickness / 2; x++) {
			if (x >= 0 && x < width && y >= 0 && y < height) {
				fm[y * width + x] = color;
			}
		}
	}
}

void CgPrjDlg::drawHollowCircle(unsigned char* fm, int x, int y, int outerRadius, int innerRadius, int thickness, int nYellow)
{
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	int width = m_pDlgImage->m_Image.GetWidth();
	int height = m_pDlgImage->m_Image.GetHeight();

	for (int j = y - outerRadius; j <= y + outerRadius; j++) {
		for (int i = x - outerRadius; i <= x + outerRadius; i++) {
			if (i >= 0 && i < width && j >= 0 && j < height) {
				double dX = i - x;
				double dY = j - y;
				double dDist = dX * dX + dY * dY;

				if (dDist <= outerRadius * outerRadius && dDist >= innerRadius * innerRadius) {
					// ���� �� (innerRadius���� �۰ų� ���� �ݰ�)���� �ܺ� �� (outerRadius���� �۰ų� ���� �ݰ�)������ �ȼ��� ����
					if (dDist >= (outerRadius - thickness) * (outerRadius - thickness) && dDist <= outerRadius * outerRadius) {
						fm[j * nPitch + i] = nYellow;
					}
				}
			}
		}
	}
}


