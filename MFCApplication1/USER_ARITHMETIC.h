#pragma once

/*
**********************************************************************
* 模块名称: USER_FILTER
* 摘    要: 图像运算类
* 当前版本: 1.0
* 作    者: guangjie2333
* 完成日期: 2021-10-30
* 内    容:
* 注    意: 整个模块基于RGB三通道bmp图
*********************************************************************/

/*
**********************************************************************
*                               包含头文件
**********************************************************************
*/
#include "USER_DEFINE.h"

/*
**********************************************************************
*                               用户字定义类
**********************************************************************
*/
class USER_ARITHMETIC
{
	//variable 
	public:


	protected:

	private:
		BYTE* pixelArray1;
		BYTE* pixelArray2;
		BYTE* pixelArrayNew;
		int  ArraySize;
		BYTE* R_array1; //图1 RGB三个分量分别做滤波
		BYTE* G_array1;
		BYTE* B_array1;

		BYTE* R_array2; //图2 RGB三个分量分别做滤波
		BYTE* G_array2;
		BYTE* B_array2;

	//function
	public:
		USER_ARITHMETIC(BYTE* ARRAY1, BYTE* ARRAY2, int ARRAYSIZE, BYTE* ARRAY3);
		~USER_ARITHMETIC();
		void Add(); // + 
		void Sub(); // -
		void Mul(); // *
		void Div(); // /
	protected:
		void SeparateRGB();

	private:
		void TwoPicAdd();
		void TwoPicSub();
		void TwoPicMul();
		void TwoPicDiv();

};

