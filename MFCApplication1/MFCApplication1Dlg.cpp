﻿
// MFCApplication1Dlg.cpp: 实现文件

/*
作者 ：guangjie2333
时间 ：2021.10.5
单位 ：SZU
版本 ：V1.0.0
*/

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
**********************************************************************
*                              自定义头文件
**********************************************************************
*/

#include "USER_BAR_CLASS_DLG.h"		//滚动条（UI）
#include "USER_RGB_HSV_CLASS.h"		//HSV-RGB
#include "USER_LINE_CHANGE_Dlg.h"	//线性变换(UI)
#include "USER_HIS_EQU.h"			//直方图均衡化
#include "USER_FILTER.h"			//滤波
#include "USER_ARITHMETIC.h"        //图像运算
//#include "stdlib.h"

/*
**********************************************************************
*                               内部变量（文件内全局）
**********************************************************************
*/

bmpData bmpdata1;
bmpData bmpdata2;
CString BmpName;
CString EntName;

/*
**********************************************************************
*                               内部函数声明
**********************************************************************
*/
void Cal_HSV_Scale(HSV_SLIDER_STRUCT hsv_slider_struct,float *hScale, float* sScale, float* vScale);  //调节滚动条实际上是在调节缩放系数
void Get_PictureContro_RGBdata(HDC hDC, LPRECT lpRect, BYTE* res);




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENBMP, &CMFCApplication1Dlg::OnBnClickedButtonOpenbmp)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_HSV2RGB, &CMFCApplication1Dlg::OnBnClickedButtonHsv2rgb)
	ON_MESSAGE(WM_GET_DIALOG_HSV_SLIDER_VAL, UserMessageHandler) //用户自定义的消息标识和函数的绑定
	ON_COMMAND(ID_32774, &CMFCApplication1Dlg::MEUN_LAB3_Button1_Up)
	ON_COMMAND(ID_32777, &CMFCApplication1Dlg::HistogramEqualization_MenuButtonUp)
	ON_COMMAND(ID_32778, &CMFCApplication1Dlg::LowFilter_MenuButtonUp)
	ON_COMMAND(ID_32779, &CMFCApplication1Dlg::HighFilter_MenuButtonUp)
	ON_COMMAND(ID_32780, &CMFCApplication1Dlg::MidFilter_MenuButtonUp)
	ON_COMMAND(ID_32781, &CMFCApplication1Dlg::MaxFilter_MenuButtonUp)
	ON_COMMAND(ID_32782, &CMFCApplication1Dlg::MinFilter_MenuButtonUp)
	ON_COMMAND(ID_32783, &CMFCApplication1Dlg::EnhanceColor)
	ON_BN_CLICKED(IDC_BUTTON_OPENBMP2, &CMFCApplication1Dlg::OnBnClickedButtonOpenbmp2)
	ON_COMMAND(ID_32784, &CMFCApplication1Dlg::TwoPic_Add)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CMenu menu; //可为局部变量
	menu.LoadMenu(IDR_MENU_MAIN); //加载菜单资源使与CMenu Object相关联
	SetMenu(&menu); // Sets the current menu to the specified menu( 这是CWnd的函数)
	menu.Detach(); //这一步很关键，因为menu为局部变量，使用此函数 Detaches a Windows menu
	//from a CMenu object and returns the handle. 就是说使HMENU与menu这个object相剥离

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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



//读取图片，readBmp1按键按下响应函数

void CMFCApplication1Dlg::OnBnClickedButtonOpenbmp()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//打开文件 
	CString filter = (CString)"图像文件(*.bmp)|*.bmp;*.BMP||";//指明可供选择的文件类型和相应的扩展名
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);  //打开文件

//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//way 1
		//打开对话框获取图像信息
		BmpName = dlg.GetPathName();     //获取文件路径名   
	    EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)  //如果是bmp图片则打开显示
		{
			//定义变量存储图片信息
			BITMAPINFO* pBmpInfo;       //记录图像信息头内容
			

				//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpdata1.bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpdata1.bmpFile.Read(&bmpdata1.bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpdata1.bmpFile.Read(&bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));  //存储图像信息头内容
			DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
			bmpdata1.pBmpData = (BYTE*)new char[dataBytes];
			bmpdata1.bmpFile.Seek(bmpdata1.bmpHeader.bfOffBits,0);//这一步非常重要，必须要把文件指针偏移
			bmpdata1.bmpFile.Read(bmpdata1.pBmpData, dataBytes);  //存储图像数据(以文件指针为起点开始读dataBytes个数据)
			bmpdata1.bmpFile.Close();



			//显示图像1	
			CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE); //获得pictrue控件窗口的句柄			
			CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域			
			CDC* pDC = pWnd->GetDC(); //获得pictrue控件的DC			
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, bmpdata1.pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
	

		}


		//way 2 
	/*	CWnd* m_pWnd;

		m_pWnd = this->GetDlgItem(IDC_STATIC_PICTURE);  //  IDC_PICTURE此为Picture控件ID 

		  //********* 加载图像 ********************

		try {
			// 此类方法即便实现体在OnPaint()外，Picture也可以显示图像，已经过验证
			CRect   rect;
			CImage  image;
			image.Load(dlg.GetPathName().GetBuffer());
			m_pWnd->GetWindowRect(&rect);  //将客户区选中到控件表示的矩形区域内  
			CWnd* pWnd = NULL;
			pWnd = m_pWnd;//获取控件句柄  
			pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  
			CDC* pDc = NULL;
			pDc = pWnd->GetDC();//获取picture的DC  
			pDc->SetStretchBltMode(COLORONCOLOR);
			image.Draw(pDc->m_hDC, rect);
			ReleaseDC(pDc);
		}
		catch (CException* e)
		{
			 TCHAR   szError[1024];

			 e->GetErrorMessage(szError,1024);   //  e.GetErrorMessage(szError,1024); 
			 ::AfxMessageBox(szError);
		}
     */

	}
}

//读取图片，readBmp2按键按下响应函数
void CMFCApplication1Dlg::OnBnClickedButtonOpenbmp2()
{
	//打开文件 
	CString filter = (CString)"图像文件(*.bmp)|*.bmp;*.BMP||";//指明可供选择的文件类型和相应的扩展名
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);  //打开文件

//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//way 1
		//打开对话框获取图像信息
		BmpName = dlg.GetPathName();     //获取文件路径名   
		EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)  //如果是bmp图片则打开显示
		{
			//定义变量存储图片信息
			BITMAPINFO* pBmpInfo;       //记录图像信息头内容

			//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpdata2.bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpdata2.bmpFile.Read(&bmpdata2.bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpdata2.bmpFile.Read(&bmpdata2.bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpdata2.bmpInfo, sizeof(BITMAPINFOHEADER));  //存储图像信息头内容
			DWORD dataBytes = bmpdata2.bmpHeader.bfSize - bmpdata2.bmpHeader.bfOffBits;//图像数据大小，单位为字节
			bmpdata2.pBmpData = (BYTE*)new char[dataBytes];
			bmpdata2.bmpFile.Seek(bmpdata2.bmpHeader.bfOffBits, 0);//这一步非常重要，必须要把文件指针偏移
			bmpdata2.bmpFile.Read(bmpdata2.pBmpData, dataBytes);  //存储图像数据(以文件指针为起点开始读dataBytes个数据)
			bmpdata2.bmpFile.Close();

			//显示图像2	
			CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2); //获得pictrue控件窗口的句柄		
			CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域			
			CDC* pDC = pWnd->GetDC(); //获得pictrue控件的DC		
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata2.bmpInfo.biWidth, bmpdata2.bmpInfo.biHeight, bmpdata2.pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

		}


		//way 2 
	/*	CWnd* m_pWnd;

		m_pWnd = this->GetDlgItem(IDC_STATIC_PICTURE2);  //  IDC_PICTURE此为Picture控件ID 

		  //********* 加载图像 ********************

		try {
			// 此类方法即便实现体在OnPaint()外，Picture也可以显示图像，已经过验证
			CRect   rect;
			CImage  image;
			image.Load(dlg.GetPathName().GetBuffer());
			m_pWnd->GetWindowRect(&rect);  //将客户区选中到控件表示的矩形区域内  
			CWnd* pWnd = NULL;
			pWnd = m_pWnd;//获取控件句柄  
			pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  
			CDC* pDc = NULL;
			pDc = pWnd->GetDC();//获取picture的DC  
			pDc->SetStretchBltMode(COLORONCOLOR);
			image.Draw(pDc->m_hDC, rect);
			ReleaseDC(pDc);

		}
		catch (CException* e)
		{
			TCHAR   szError[1024];

			e->GetErrorMessage(szError, 1024);   //  e.GetErrorMessage(szError,1024); 
			::AfxMessageBox(szError);
		}*/


	}
}


//鼠标在屏幕中移动的事件响应函数
void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//guangjie2333的设计
	//需要注意的是图像存在伸缩，需要更具伸缩比例确定

	CDialogEx::OnMouseMove(nFlags, point);

	CRect pect;

	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE);//IDC_PICTURE为控件ID号

	pWnd->GetClientRect(&pect);

	int high = pect.Height();   //返回高

	int width = pect.Width();   //返回宽


	TRACE("picture 控件长宽高信息  high = %d  width = %d \n\n" , high, width);


	//确保鼠标在图像内移动
	if (1)
	{
		TRACE("捕捉到了鼠标移动，当前位置 X = %d  Y = %d \n\n", point.x, point.y);
		SetDlgItemInt(IDC_EDIT_X, point.x);			 //写入坐标值x
		SetDlgItemInt(IDC_EDIT_Y, point.y);			 //写入坐标值y

		HDC hDC = ::GetDC(NULL);
		GetCursorPos(&point);
		COLORREF rgb = ::GetPixel(hDC, point.x, point.y);  //后两个参数是相对坐标


		RGB_STRUCT rgbStruct;
		rgbStruct.r = GetRValue(rgb);			    //获得灰度分量
		rgbStruct.g = GetGValue(rgb);
		rgbStruct.b = GetBValue(rgb);
		SetDlgItemInt(IDC_EDIT_R, rgbStruct.r);     //写入灰度分量R
		SetDlgItemInt(IDC_EDIT_G, rgbStruct.g);     //写入灰度分量G
		SetDlgItemInt(IDC_EDIT_B, rgbStruct.b);     //写入灰度分量B

		//显示该点的hsv值
		USER_RGB_HSV_CLASS userClass_rgb_hsv;       //用户自定义的 hsv—rgb 转换类
		HSV_STRUCT hsvStruct;
		hsvStruct = userClass_rgb_hsv.RGB2HSV(rgbStruct);

		CString str;
		SetDlgItemInt(IDC_EDIT_H, hsvStruct.h);     //写入灰度分量R
		str.Format(_T("%.5f"), hsvStruct.s);
		SetDlgItemText(IDC_EDIT_S, str);			//写入灰度分量G
		str.Format(_T("%.5f"), hsvStruct.v);
		SetDlgItemText(IDC_EDIT_V, str);			//写入灰度分量B

	}
	else
	{
		SetDlgItemInt(IDC_EDIT_X, 0);				//写入坐标值x
		SetDlgItemInt(IDC_EDIT_Y, 0);				//写入坐标值y
		SetDlgItemInt(IDC_EDIT_R, 0);				//写入灰度分量R
		SetDlgItemInt(IDC_EDIT_G, 0);				//写入灰度分量G
		SetDlgItemInt(IDC_EDIT_B, 0);				//写入灰度分量B
		SetDlgItemInt(IDC_EDIT_H, 0);				//写入灰度分量H
		SetDlgItemInt(IDC_EDIT_S, 0);				//写入灰度分量S
		SetDlgItemInt(IDC_EDIT_V, 0);				//写入灰度分量V
	}
}


//rgb2hsv按键按下响应函数
void CMFCApplication1Dlg::OnBnClickedButtonHsv2rgb()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// guangjie2333的设计
	
	// 按键按下后做两件事 1.读取图像 2.打开新的对话框

	//将按键按下和新的Dialog联系
	USER_BAR_CLASS_DLG dlg;
	dlg.phwnd = m_hWnd;
	dlg.DoModal();


	                                   
}

//用户自定义的消息处理函数
LRESULT CMFCApplication1Dlg::UserMessageHandler(WPARAM w, LPARAM l)
{
	// guangjie2333的设计
	((CStatic*)GetDlgItem(IDC_STATIC_PICTURE2))->SetBitmap(NULL);	//清除原有图像

	/*按理说 WPARAM w应该是一个实际值，但是我通过指针转换的方式传入了地址
	  现在拿到了地址后，我有两件事情要做 ： 
	  1. 把地址的解析方式从(int) 改成 (HSV_SLIDER_STRUCT*)
	  2. 把结构体中的值取出来
	  */
	HSV_SLIDER_STRUCT hsv_slider_val = *(HSV_SLIDER_STRUCT*)w;

	float hScale, sScale, vScale;
	int r, g, b;

	/*为了避免对原数据进行修改，新建一个图像存储结构体
	  
	  之后需要做的就是 ：
	  1.将原数据拷贝一份
	  2.将原rgb数据转换成hsv数据
	  3.再将hsv数据转换成rgb显示
	  
	  需要注意的是：1.我默认bmp图像是真彩色，24bit ，B G R三通道，不带保留项的
					2.图像是每三个数据构成一个像素点，按 B G R顺序组合而成的
					3.适用大部分的bmp图像
	  
	  */

	USER_RGB_HSV_CLASS userClass_rgb_hsv;                           //用户自定义的 hsv—rgb 转换类
	HSV_STRUCT hsv_struct;                                          //用户自定义的 hsv结构体
	RGB_STRUCT rgb_struct;											//用户自定义的 rgb结构体

	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	Cal_HSV_Scale(hsv_slider_val, &hScale, &sScale, &vScale);      //计算缩放系数

	//逐个像素进行转换
	for (int i = 0; i < dataBytes; i = i + 3)
	{
		rgb_struct.b = pixelArray[i + 0];
		rgb_struct.g = pixelArray[i + 1];
		rgb_struct.r = pixelArray[i + 2];

		hsv_struct = userClass_rgb_hsv.RGB2HSV(rgb_struct);			//单像素RGB转HSV

		hsv_struct.h = (int)hsv_struct.h * hScale;					//滚动条的意义在于对原hsv进行缩放
		hsv_struct.s = (float)hsv_struct.s * sScale;
		hsv_struct.v = (float)hsv_struct.v * vScale;

		rgb_struct = userClass_rgb_hsv.HSV2RGB(hsv_struct);         //将缩放后的hsv重新转换成rgb

		pixelArray[i + 0] = rgb_struct.b;							//将rgb数据还原
		pixelArray[i + 1] = rgb_struct.g;
		pixelArray[i + 2] = rgb_struct.r;

	}

	//显示图像2	
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);

	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER)); 
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete []pixelArray;
	return LRESULT();
}


//内部函数实现
void Cal_HSV_Scale(HSV_SLIDER_STRUCT hsv_slider_struct, float* hScale, float* sScale, float* vScale)
{
	// guangjie2333的设计

	*hScale = (float)(hsv_slider_struct.H_slider - 50) / 50 + 1; //50作为基准，小于50就按比例缩小，大于50按比例放大
	*sScale = (float)(hsv_slider_struct.S_slider - 50) / 50 + 1;
	*vScale = (float)(hsv_slider_struct.V_slider - 50) / 50 + 1;
}





//LAB3
/*
******************************************************************************
* 函数名称:	MEUN_LAB3_Button1_Up
* 函数功能: 菜单栏，实验三，线性变换
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void CMFCApplication1Dlg::MEUN_LAB3_Button1_Up()
{
	// TODO: 在此添加命令处理程序代码
	USER_LINE_CHANGE_Dlg dlg;

	dlg.DoModal();
}

/*
******************************************************************************
* 函数名称:	HistogramEqualization_MenuButtonUp
* 函数功能: 菜单栏，实验三，直方图均衡
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void CMFCApplication1Dlg::HistogramEqualization_MenuButtonUp()
{
	// TODO: 在此添加命令处理程序代码
	
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//均衡化
	USER_HIS_EQU user_his_equ(pixelArray, dataBytes);
	user_his_equ.HistogramEqualization();

	//显示图像2	
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	

	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);

	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}

/*
******************************************************************************
* 函数名称:	LowFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，低通滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/

void CMFCApplication1Dlg::LowFilter_MenuButtonUp()
{
   //拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//低通滤波
	USER_FILTER userfilter(pixelArray, bmpdata1.bmpInfo.biHeight, bmpdata1.bmpInfo.biWidth);
	userfilter.LowFilter();

	// 显示图像2
	CWnd * pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}

/*
******************************************************************************
* 函数名称:	HighFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，高通滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void CMFCApplication1Dlg::HighFilter_MenuButtonUp()
{
	// TODO: 在此添加命令处理程序代码
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//高通滤波
	USER_FILTER userfilter(pixelArray, bmpdata1.bmpInfo.biHeight, bmpdata1.bmpInfo.biWidth);
	userfilter.HighFilter();

	// 显示图像2
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}

/*
******************************************************************************
* 函数名称:	MidFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，中值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void CMFCApplication1Dlg::MidFilter_MenuButtonUp()
{
	// TODO: 在此添加命令处理程序代码
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//中值滤波
	USER_FILTER userfilter(pixelArray, bmpdata1.bmpInfo.biHeight, bmpdata1.bmpInfo.biWidth);
	userfilter.MidFilter();

	// 显示图像2
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}

/*
******************************************************************************
* 函数名称:	MaxFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，最大值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void CMFCApplication1Dlg::MaxFilter_MenuButtonUp()
{
	// TODO: 在此添加命令处理程序代码
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//最大值滤波
	USER_FILTER userfilter(pixelArray, bmpdata1.bmpInfo.biHeight, bmpdata1.bmpInfo.biWidth);
	userfilter.MaxFilter();

	// 显示图像2
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}
/*
******************************************************************************
* 函数名称:	MinFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，最小值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/

void CMFCApplication1Dlg::MinFilter_MenuButtonUp()
{
	// TODO: 在此添加命令处理程序代码
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);

	//最小值滤波
	USER_FILTER userfilter(pixelArray, bmpdata1.bmpInfo.biHeight, bmpdata1.bmpInfo.biWidth);
	userfilter.MinFilter();

	// 显示图像2
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
}

/*
******************************************************************************
* 函数名称:	MinFilter_MenuButtonUp
* 函数功能: 菜单栏，实验三，伪彩色增强
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意: 我的都是基于RGB的，这个任务要读256的图，现在不想弄了，暂时搁置吧。
*******************************************************************************
*/
void CMFCApplication1Dlg::EnhanceColor()
{
	// TODO: 在此添加命令处理程序代码
	//拷贝原数据
	DWORD dataBytes = bmpdata1.bmpHeader.bfSize - bmpdata1.bmpHeader.bfOffBits;//图像数据大小，单位为字节
	BYTE* pixelArray = (BYTE*)new char[dataBytes];
	memcpy(pixelArray, bmpdata1.pBmpData, dataBytes);
	BYTE* newPixelArray = (BYTE*)new char[dataBytes * 3];
	for (int i = 0; i < dataBytes ; i++)
	{
		//不好意思，用了这么恶心的else if
		if ((pixelArray[i] >= 0) && (pixelArray[i] < 63))
		{
			newPixelArray[i * 3 + 0] = 255;//B
			newPixelArray[i * 3 + 1] = 254 - 4 * pixelArray[i];//G
			newPixelArray[i * 3 + 2] = 0;//R

		}
		else if ((pixelArray[i] >= 64) && (pixelArray[i] < 127))
		{
			newPixelArray[i * 3 + 0] = 510 - 4 * pixelArray[i];//B
			newPixelArray[i * 3 + 1] = 4 * pixelArray[i] - 254;//G
			newPixelArray[i * 3 + 2] = 0;//R
		}
		else if ((pixelArray[i] >= 128) && (pixelArray[i] < 191))
		{
			newPixelArray[i * 3 + 0] = 0;//B
			newPixelArray[i * 3 + 1] = 255 ;//G
			newPixelArray[i * 3 + 2] = 4 * pixelArray[i] - 510;//R
		}
		else if ((pixelArray[i] >= 192) && (pixelArray[i] < 255))
		{
			newPixelArray[i * 3 + 0] = 0;//B
			newPixelArray[i * 3 + 1] = 1022 - 4 * pixelArray[i];//G
			newPixelArray[i * 3 + 2] = 255;//R
		}
		
	}


	// 显示图像2
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE2);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bmpdata1.bmpInfo, sizeof(BITMAPINFOHEADER));

	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpdata1.bmpInfo.biWidth, bmpdata1.bmpInfo.biHeight, pixelArray, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[]pixelArray;
	delete[]newPixelArray;
}







//LAB4
/*
******************************************************************************
* 函数名称:	TwoPic_Add
* 函数功能: 菜单栏，实验四，两幅图相加
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-31日
* 注    意: 基于RGB三通道图
*******************************************************************************
*/
void CMFCApplication1Dlg::TwoPic_Add()
{
	CWnd* pWnd1 = GetDlgItem(IDC_STATIC_PICTURE); //获得pictrue控件窗口的句柄			
	CRect rect1;
	pWnd1->GetClientRect(&rect1);
	CDC* pDC1 = pWnd1->GetDC(); //获得pictrue控件的DC

	CWnd* pWnd2 = GetDlgItem(IDC_STATIC_PICTURE2); //获得pictrue控件窗口的句柄			
	CRect rect2;
	pWnd2->GetClientRect(&rect2);
	CDC* pDC2 = pWnd2->GetDC(); //获得pictrue控件的DC
	
	/***********************************************

	处理第一幅图

	*************************************************/

	int Width1 = rect1.right - rect1.left;
	int Height1 = rect1.bottom - rect1.top;
	HDC hdc1 = pDC1->GetSafeHdc();
	HDC memDC1 = CreateCompatibleDC(hdc1);//内存DC 
	HBITMAP memBitmap1 = CreateCompatibleBitmap(hdc1, Width1, Height1); //建立和屏幕兼容的bitmap  
	HBITMAP hOldBitmap1 = (HBITMAP)SelectObject(memDC1, memBitmap1);//将memBitmap选入内存DC 
	BitBlt(memDC1, 0, 0, Width1, Height1,hdc1, rect1.left, rect1.top,SRCCOPY);//复制屏幕图像到内存DC 

	  //以下代码保存memDC中的位图到文件 
	BITMAP bmpInfo1;
	GetObject(memBitmap1, sizeof(bmpInfo1), &bmpInfo1);//获得位图信息 

	DWORD bmpBytesSize1 = bmpInfo1.bmWidthBytes * bmpInfo1.bmHeight * 3;

	BITMAPFILEHEADER bfh1 = { 0 };//位图文件头 
	bfh1.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量 
	bfh1.bfSize = bfh1.bfOffBits + bmpBytesSize1;//文件总的大小 
	bfh1.bfType = (WORD)0x4d42;

	BITMAPINFOHEADER bih1 = { 0 };//位图信息头 
	bih1.biBitCount = bmpInfo1.bmBitsPixel;//每个像素字节大小 
	bih1.biCompression = BI_RGB;
	bih1.biHeight = bmpInfo1.bmHeight;//高度 
	bih1.biPlanes = 1;
	bih1.biSize = sizeof(BITMAPINFOHEADER);
	bih1.biSizeImage = bmpBytesSize1;//图像数据大小 
	bih1.biWidth = bmpInfo1.bmWidth;//宽度  

	BYTE* p1 = new BYTE[bmpBytesSize1];//申请内存保存位图数据  
	GetDIBits(memDC1, memBitmap1, 0, Height1,
		p1, (LPBITMAPINFO)&bih1, DIB_RGB_COLORS);//获取位图数据 

	/***********************************************

	处理第二幅图

	*************************************************/

	int Width2 = rect2.right - rect2.left;
	int Height2 = rect2.bottom - rect2.top;
	HDC hDC2 = pDC2->GetSafeHdc();
	HDC memDC2 = CreateCompatibleDC(hDC2);//内存DC 
	HBITMAP memBitmap2 = CreateCompatibleBitmap(hDC2, Width2, Height2); //建立和屏幕兼容的bitmap  
	HBITMAP hOldBitmap2 = (HBITMAP)SelectObject(memDC2, memBitmap2);//将memBitmap选入内存DC 
	BitBlt(memDC2, 0, 0, Width2, Height2,
		hDC2, rect2.left, rect2.top,
		SRCCOPY);//复制屏幕图像到内存DC 

	  //以下代码保存memDC中的位图到文件 
	BITMAP bmpInfo2;
	GetObject(memBitmap2, sizeof(bmpInfo2), &bmpInfo2);//获得位图信息 
	 
	DWORD bmpBytesSize2 = bmpInfo2.bmWidthBytes * bmpInfo2.bmHeight * 3;

	BITMAPFILEHEADER bfh2 = { 0 };//位图文件头 
	bfh2.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量 
	bfh2.bfSize = bfh2.bfOffBits + bmpBytesSize2;//文件总的大小 
	bfh2.bfType = (WORD)0x4d42;

	BITMAPINFOHEADER bih2 = { 0 };//位图信息头 
	bih2.biBitCount = bmpInfo2.bmBitsPixel;//每个像素字节大小 
	bih2.biCompression = BI_RGB;
	bih2.biHeight = bmpInfo2.bmHeight;//高度 
	bih2.biPlanes = 1;
	bih2.biSize = sizeof(BITMAPINFOHEADER);
	bih2.biSizeImage = bmpBytesSize2;//图像数据大小 
	bih2.biWidth = bmpInfo2.bmWidth;//宽度  

	BYTE* p2 = (BYTE*)new char[bmpBytesSize2];//申请内存保存位图数据  
	GetDIBits(memDC2, memBitmap2, 0, Height2,
		p2, (LPBITMAPINFO)&bih2, DIB_RGB_COLORS);//获取位图数据 

	  //正常的还要对256及以下的颜色加颜色映射表，
	  // 但是现在的显示模式基本上都是真彩（24或32位）显示，因此忽略此项



	BYTE* p3 = new BYTE[bmpBytesSize1];
	USER_ARITHMETIC user_arithmetic(p1, p2, bmpBytesSize1, p3);
	user_arithmetic.Add();
	// 显示图像3
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PICTURE3);					//获得pictrue控件窗口的句柄	
	CRect rect;
	pWnd->GetClientRect(&rect);										//获得pictrue控件所在的矩形区域			
	CDC* pDC = pWnd->GetDC();										//获得pictrue控件的DC			
	pDC->SetStretchBltMode(COLORONCOLOR);
	BITMAPINFO* pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(pBmpInfo, &bih1, sizeof(BITMAPINFOHEADER));

	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, bmpInfo1.bmWidth, bmpInfo1.bmHeight, p3, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	/***********************************************

	结束清理工作

	*************************************************/

	delete[] p1;

	SelectObject(memDC1, hOldBitmap1);
	DeleteObject(memBitmap1);
	DeleteDC(memDC1);

	delete[] p2;

	SelectObject(memDC2, hOldBitmap2);
	DeleteObject(memBitmap2);
	DeleteDC(memDC2);

	delete[] p3;
}

