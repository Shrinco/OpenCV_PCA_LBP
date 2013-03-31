
// opencvMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "opencvMFC.h"
#include "opencvMFCDlg.h"
#include "afxdialogex.h"
#include "CheckFace.h"
#include "LBP.h"
#include "PCA.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CString GetDirectory();
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopencvMFCDlg �Ի���




CopencvMFCDlg::CopencvMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CopencvMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	imagepath1 = _T("");
	imagepath2 = _T("");
	lastnum = _T("");
}

void CopencvMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, imagepath1);
	DDX_Text(pDX, IDC_EDIT2, imagepath2);
	//  DDX_Control(pDX, IDC_EDIT3, lastnum);
	DDX_Text(pDX, IDC_EDIT3, lastnum);
}

BEGIN_MESSAGE_MAP(CopencvMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CopencvMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CopencvMFCDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CopencvMFCDlg::OnClickedButton3)
END_MESSAGE_MAP()


// CopencvMFCDlg ��Ϣ�������

BOOL CopencvMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CopencvMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CopencvMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CopencvMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvMFCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat ImgFirst1;
	Mat ImgFirst2;
	Mat img;
	Mat ImgLast1;
	Mat ImgLast2;
	img = imread("111.bmp",0);
	//imagepath1 = "E:\\01.png";
	//imagepath2 = "E:\\05.png";
	PhotoCup(ImgFirst1,imagepath1);
	PhotoCup(ImgFirst2,imagepath2);
	ImageMain(img,ImgFirst1,ImgFirst2,ImgLast1,ImgLast2);
	lastnum = test(ImgLast1,ImgLast2).c_str();
	GetDlgItem(IDC_EDIT3)->SetWindowText(lastnum);
	//SetDlgItemText(hWinMain, IDC_EDIT3, lastnum);
}


void CopencvMFCDlg::OnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	imagepath1 = GetDirectory();
	UpdateData(false);
}


void CopencvMFCDlg::OnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	imagepath2 = GetDirectory();
	UpdateData(false);
}
CString GetDirectory()
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "ѡ���ļ���Ŀ¼";
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_BROWSEINCLUDEFILES | BIF_EDITBOX ;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return "";
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if(strDirectoryPath.IsEmpty())
		return "";
	//if(strDirectoryPath.Right(1)!="\\")
	//	strDirectoryPath+="\\";
	
	return strDirectoryPath;
}

