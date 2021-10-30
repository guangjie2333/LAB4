#pragma once

/*
**********************************************************************
* 模块名称: USER_PIC_FLIP
* 摘    要: 图像翻转类
* 当前版本: 1.0
* 作    者: guangjie2333
* 完成日期: 2021-10-30
* 内    容:
* 注    意: V1.0版本只包含水平翻转
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

class USER_PIC_FLIP
{
	//variable 
	public:


	protected:

	private:
		BYTE* pixelArray;
		int  ArraySize;
		int  high;
		int  width;
		BYTE* R_array; //RGB三个分量分别做滤波
		BYTE* G_array;
		BYTE* B_array;

	//function
	public:
		USER_PIC_FLIP(BYTE* ARRAY1, int h, int w);
		~USER_PIC_FLIP();
		void Filp();

	protected:
		void SeparateRGB();
		void UnionRGB();

	private:
		void PicFilp(int flag);
};

