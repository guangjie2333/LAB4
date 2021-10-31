#include "pch.h"
#include "USER_BLINE_TRANSFORM.h"
/*
********************************************************************************
********************************************************************************
*                               构造&析构函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	USER_BLINE_TRANSFORM
* 函数功能: 构造（初始化）函数
* 输入参数:	ARRAY1 ：bmp图像的RGB三通道数据, h ：图像高  w:图像宽
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
USER_BLINE_TRANSFORM::USER_BLINE_TRANSFORM(BYTE* ARRAY1, int h, int w, BYTE* ARRAY2)
{
	pixelArray = ARRAY1;
	newPixelArray = ARRAY2;
	high = h;
	width = w;
	ArraySize = high * width * 3;
	newArraySize = ((high * 2 - 1) * (width * 2 - 1)) * 3;

	R_array = (BYTE*)new char[ArraySize / 3 + 1];
	G_array = (BYTE*)new char[ArraySize / 3 + 1];
	B_array = (BYTE*)new char[ArraySize / 3 + 1];

	newR_array = (BYTE*)new char[newArraySize / 3 + 1];
	newG_array = (BYTE*)new char[newArraySize / 3 + 1];
	newB_array = (BYTE*)new char[newArraySize / 3 + 1];
}

/*
******************************************************************************
* 函数名称:	~USER_BLINE_TRANSFORM
* 函数功能: 析构函数，将动态开辟的空间清除
* 输入参数:	none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
USER_BLINE_TRANSFORM::~USER_BLINE_TRANSFORM()
{
	delete[] R_array;
	delete[] G_array;
	delete[] B_array;
	delete[] newR_array;
	delete[] newG_array;
	delete[] newB_array;
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
* 函数名称:	BlinearTransform
* 函数功能: 图像双线性变换的接口函数
* 输入参数:	none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-30日
* 注    意:
*******************************************************************************
*/
void USER_BLINE_TRANSFORM::BlinearTransform()
{
	SeparateRGB();
	DealRgbMatrixBlinearTransform();
	UnionRGB();
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
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
void USER_BLINE_TRANSFORM::SeparateRGB()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		R_array[j] = pixelArray[i + 2];
		G_array[j] = pixelArray[i + 1];
		B_array[j] = pixelArray[i + 0];

		j++;
	}
}

/*
******************************************************************************
* 函数名称:	UnionRGB
* 函数功能: RGB分量整合
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
void USER_BLINE_TRANSFORM::UnionRGB()
{
	int j = 0;
	for (int i = 0; i < newArraySize; i = i + 3)
	{
		newPixelArray[i + 2] = newR_array[j];
		newPixelArray[i + 1] = newG_array[j];
		newPixelArray[i + 0] = newB_array[j];

		j++;
	} 
}

/*
******************************************************************************
* 函数名称:	DealRgbMatrixBlinearTransform
* 函数功能: RGB分量矩阵分别做双线性插值
* 输入参数: none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-31日
* 注    意: 该函数简单的对相邻的元素做平均，得到的结果作为插值结果
*******************************************************************************
*/
void USER_BLINE_TRANSFORM::DealRgbMatrixBlinearTransform()
{
	//动态建立二维数组
	BYTE** matrixR;
	BYTE** matrixG;
	BYTE** matrixB;
	matrixR = new BYTE * [high * 2 - 1];
	matrixG = new BYTE * [high * 2 - 1];
	matrixB = new BYTE * [high * 2 - 1];
	for (int j = 0; j < high * 2 - 1; j++)
	{
		matrixR[j] = new BYTE[width * 2 - 1];
		matrixG[j] = new BYTE[width * 2 - 1];
		matrixB[j] = new BYTE[width * 2 - 1];
	}

	//初始化，向量转矩阵
	int k = 0;
	for (int i = 0; i < high * 2 - 1; i = i + 2)
	{
		for (int j = 0; j < width * 2 - 1; j = j + 2)
		{
			matrixR[i][j] = R_array[k];
			matrixG[i][j] = G_array[k];
			matrixB[i][j] = B_array[k];
			k++;
		}
	}

	//列方向一阶插值
	for (int i = 1; i < high * 2 - 1; i = i + 2)
	{
		for (int j = 0; j < width * 2 - 1; j = j + 2)
		{
			matrixR[i][j] = (BYTE)((matrixR[i - 1][j] + matrixR[i + 1][j]) / 2);
			matrixG[i][j] = (BYTE)((matrixG[i - 1][j] + matrixG[i + 1][j]) / 2);
			matrixB[i][j] = (BYTE)((matrixB[i - 1][j] + matrixB[i + 1][j]) / 2);
		}
	}

	//行方向一阶插值
	for (int i = 0; i < high * 2 - 1; i++)
	{
		for (int j = 1; j < width * 2 - 1; j = j + 2)
		{
			matrixR[i][j] = (BYTE)((matrixR[i][j - 1] + matrixR[i][j + 1]) / 2);
			matrixG[i][j] = (BYTE)((matrixG[i][j - 1] + matrixG[i][j + 1]) / 2);
			matrixB[i][j] = (BYTE)((matrixB[i][j - 1] + matrixB[i][j + 1]) / 2);
		}
	}

	//矩阵转向量
	k = 0;
	for (int i = 0; i < high * 2 - 1; i++)
	{
		for (int j = 0; j < width * 2 - 1; j++)
		{
			newR_array[k] = matrixR[i][j];
			newG_array[k] = matrixG[i][j];
			newB_array[k] = matrixB[i][j];
			k++;
		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixR[j];
		delete[] matrixG[j];
		delete[] matrixB[j];
	}
	delete[] matrixR;
	delete[] matrixG;
	delete[] matrixB;
}
