
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "dllmain.cpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 对话框

BOOL CALLBACK KeyboardProc(WPARAM action, KBDLLHOOKSTRUCT* pKeyStruct)

{

	// 判断按键动作

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



	// 返回 true 表示继续传递按键消息

	// 返回 false 表示结束按键消息传递

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


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	
	//设置checkbox为点击状态
	CButton *pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	pBtn->SetCheck(1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	
	
	
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	if (!tag) {
		DWORD dwVK[] = { VK_PRIOR, VK_NEXT };

		int nLength = sizeof(dwVK) / sizeof(DWORD);

		StartMaskKey(dwVK, nLength, KeyboardProc);

		CString cs("恢复使用");
		
		SetDlgItemText(IDC_BUTTON1,cs);

		tag = true;

		if(BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
			ShowWindow(SW_MINIMIZE);
	}
	else {
		DWORD dwVK[] = { VK_PRIOR, VK_NEXT };

		int nLength = sizeof(dwVK) / sizeof(DWORD);

		StopMaskKey();

		CString cs("一键禁用");

		SetDlgItemText(IDC_BUTTON1, cs);

		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
			ShowWindow(SW_MINIMIZE);
		
		tag = false;
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}
