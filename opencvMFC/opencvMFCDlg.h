
// opencvMFCDlg.h : ͷ�ļ�
//

#pragma once


// CopencvMFCDlg �Ի���
class CopencvMFCDlg : public CDialogEx
{
// ����
public:
	CopencvMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENCVMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString imagepath1;
	CString imagepath2;
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
//	CEdit lastnum;
	CString lastnum;
};
