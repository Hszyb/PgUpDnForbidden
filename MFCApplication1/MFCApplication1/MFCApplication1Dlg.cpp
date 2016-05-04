
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "dllmain.cpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg �Ի���

BOOL CALLBACK KeyboardProc(WPARAM action, KBDLLHOOKSTRUCT* pKeyStruct)

{

	// �жϰ�������

	switch (action)

	{

	case WM_KEYDOWN:



		break;

	case WM_KEYUP:



		break;

	case WM_SYSKEYDOWN:



		break;

	case WM_SYSKEYUP:



		break;



	}



	// ���� true ��ʾ�������ݰ�����Ϣ

	// ���� false ��ʾ����������Ϣ����

	return false;

}


CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	//����checkboxΪ���״̬
	CButton *pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	pBtn->SetCheck(1);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	
	
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	if (!tag) {
		DWORD dwVK[] = { VK_PRIOR, VK_NEXT };

		int nLength = sizeof(dwVK) / sizeof(DWORD);

		StartMaskKey(dwVK, nLength, KeyboardProc);

		CString cs("�ָ�ʹ��");
		
		SetDlgItemText(IDC_BUTTON1,cs);

		tag = true;

		if(BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
			ShowWindow(SW_MINIMIZE);
	}
	else {
		DWORD dwVK[] = { VK_PRIOR, VK_NEXT };

		int nLength = sizeof(dwVK) / sizeof(DWORD);

		StopMaskKey();

		CString cs("һ������");

		SetDlgItemText(IDC_BUTTON1, cs);

		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
			ShowWindow(SW_MINIMIZE);
		
		tag = false;
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
