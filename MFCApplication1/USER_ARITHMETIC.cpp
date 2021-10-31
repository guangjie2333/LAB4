#include "pch.h"
#include "USER_ARITHMETIC.h"

/*
********************************************************************************
********************************************************************************
*                               构造&析构函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	USER_ARITHMETIC
* 函数功能: 构造（初始化）函数
* 输入参数:	ARRAY1 ：bmp图像的RGB三通道数据, ARRAYSIZE : 数据长度 , ARRAY3 : 生成的新图像的数据
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-30日
* 注    意: ARRAY1和ARRAY2 长度必须一致
*******************************************************************************
*/
USER_ARITHMETIC::USER_ARITHMETIC(BYTE* ARRAY1, BYTE* ARRAY2, int ARRAYSIZE, BYTE* ARRAY3)
{
	pixelArray1 = ARRAY1;
	pixelArray2 = ARRAY2;
	pixelArrayNew = ARRAY3;
	ArraySize = ARRAYSIZE;

	R_array1 = (BYTE*)new char[ArraySize / 3 + 1];
	G_array1 = (BYTE*)new char[ArraySize / 3 + 1];
	B_array1 = (BYTE*)new char[ArraySize / 3 + 1];

	R_array2 = (BYTE*)new char[ArraySize / 3 + 1]; 
	G_array2 = (BYTE*)new char[ArraySize / 3 + 1];
	B_array2 = (BYTE*)new char[ArraySize / 3 + 1];
}

/*
******************************************************************************
* 函数名称:	~USER_HIS_EQU
* 函数功能: 析构函数，将动态开辟的空间清除
* 输入参数:	none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
USER_ARITHMETIC::~USER_ARITHMETIC()
{
	delete[] R_array1;
	delete[] G_array1;
	delete[] B_array1;
	delete[] R_array2;
	delete[] G_array2;
	delete[] B_array2;
}

/*
********************************************************************************
********************************************************************************
*                               接口函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	Add
* 函数功能: 实现两幅图像相加
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-30日
* 注    意:
*******************************************************************************
*/

void USER_ARITHMETIC::Add()
{
	SeparateRGB();
	TwoPicAdd(); //实现两幅图像RGB三通道分别相加
}

/*
******************************************************************************
* 函数名称:	Sub
* 函数功能: 实现两幅图像相减
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::Sub()
{
	SeparateRGB();
	TwoPicSub(); //实现两幅图像RGB三通道分别相加
}

/*
******************************************************************************
* 函数名称:	Mul
* 函数功能: 实现两幅图像相乘
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::Mul()
{
	SeparateRGB();
	TwoPicMul(); //实现两幅图像RGB三通道分别相加
}

/*
******************************************************************************
* 函数名称:	Div
* 函数功能: 实现两幅图像相除
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::Div()
{
	SeparateRGB();
	TwoPicDiv(); //实现两幅图像RGB三通道分别相加
}



/*
********************************************************************************
********************************************************************************
*                               功能函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	SeparateRGB
* 函数功能: 分离RGB分量
* 输入参数:	none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/

void USER_ARITHMETIC::SeparateRGB()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		R_array1[j] = pixelArray1[i + 2];
		G_array1[j] = pixelArray1[i + 1];
		B_array1[j] = pixelArray1[i + 0];

		R_array2[j] = pixelArray2[i + 2];
		G_array2[j] = pixelArray2[i + 1];
		B_array2[j] = pixelArray2[i + 0];

		j++;
	}
}


/*
******************************************************************************
* 函数名称:	TwoPicAdd
* 函数功能: 实现两幅图RGB三通道的分别相加
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::TwoPicAdd()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArrayNew[i + 2] = R_array1[j] + R_array2[j];
		pixelArrayNew[i + 1] = G_array1[j] + G_array2[j];
		pixelArrayNew[i + 0] = B_array1[j] + B_array2[j];
		pixelArrayNew[i + 2] = pixelArrayNew[i + 2] > 255 ? 255 : pixelArrayNew[i + 2];
		pixelArrayNew[i + 1] = pixelArrayNew[i + 1] > 255 ? 255 : pixelArrayNew[i + 1];
		pixelArrayNew[i + 0] = pixelArrayNew[i + 0] > 255 ? 255 : pixelArrayNew[i + 0];
		j++;
	}
}


/*
******************************************************************************
* 函数名称:	TwoPicSub
* 函数功能: 实现两幅图RGB三通道的分别相减
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::TwoPicSub()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArrayNew[i + 2] = R_array1[j] - R_array2[j];
		pixelArrayNew[i + 1] = G_array1[j] - G_array2[j];
		pixelArrayNew[i + 0] = B_array1[j] - B_array2[j];
		pixelArrayNew[i + 2] = pixelArrayNew[i + 2] < 0 ? 0 : pixelArrayNew[i + 2];
		pixelArrayNew[i + 1] = pixelArrayNew[i + 1] < 0 ? 0 : pixelArrayNew[i + 1];
		pixelArrayNew[i + 0] = pixelArrayNew[i + 0] < 0 ? 0 : pixelArrayNew[i + 0];
		j++;
	}
}

/*
******************************************************************************
* 函数名称:	TwoPicMul
* 函数功能: 实现两幅图RGB三通道的分别相乘
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::TwoPicMul()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArrayNew[i + 2] = R_array1[j] * R_array2[j];
		pixelArrayNew[i + 1] = G_array1[j] * G_array2[j];
		pixelArrayNew[i + 0] = B_array1[j] * B_array2[j];
		pixelArrayNew[i + 2] = pixelArrayNew[i + 2] > 255 ? 255 : pixelArrayNew[i + 2];
		pixelArrayNew[i + 1] = pixelArrayNew[i + 1] > 255 ? 255 : pixelArrayNew[i + 1];
		pixelArrayNew[i + 0] = pixelArrayNew[i + 0] > 255 ? 255 : pixelArrayNew[i + 0];
		j++;
	}
}

/*
******************************************************************************
* 函数名称:	TwoPicDiv
* 函数功能: 实现两幅图RGB三通道的分别相除
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_ARITHMETIC::TwoPicDiv()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArrayNew[i + 2] = (BYTE)(R_array1[j] / R_array2[j]);
		pixelArrayNew[i + 1] = (BYTE)(G_array1[j] / G_array2[j]);
		pixelArrayNew[i + 0] = (BYTE)(B_array1[j] / B_array2[j]);
		j++;
	}

}
