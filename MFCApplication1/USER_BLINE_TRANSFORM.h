#pragma once
/*
**********************************************************************
* 模块名称: USER_BLINE_TRANSFORM
* 摘    要: 双线性变换类
* 当前版本: 1.0
* 作    者: guangjie2333
* 完成日期: 2021-10-31
* 内    容:
* 注    意: none
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
class USER_BLINE_TRANSFORM
{
	//variable 
	public:

	protected:

	private:
		BYTE* pixelArray;
		BYTE* newPixelArray;
		int  ArraySize;
		long newArraySize;
		int  high;
		int  width;
		BYTE* R_array; //RGB三个分量
		BYTE* G_array;
		BYTE* B_array;
		BYTE* newR_array; //双线性插值后的RGB三个分量
		BYTE* newG_array;
		BYTE* newB_array;

	//function
	public:
		USER_BLINE_TRANSFORM(BYTE* ARRAY1, int h, int w, BYTE* ARRAY2);
		~USER_BLINE_TRANSFORM();
		void BlinearTransform();

	protected:
		void SeparateRGB();
		void UnionRGB();

	private:
		void DealRgbMatrixBlinearTransform();
};

