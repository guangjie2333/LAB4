#pragma once

/*
**********************************************************************
* ģ������: USER_FILTER
* ժ    Ҫ: ͼ��������
* ��ǰ�汾: 1.0
* ��    ��: guangjie2333
* �������: 2021-10-30
* ��    ��:
* ע    ��: ����ģ�����RGB��ͨ��bmpͼ
*********************************************************************/

/*
**********************************************************************
*                               ����ͷ�ļ�
**********************************************************************
*/
#include "USER_DEFINE.h"

/*
**********************************************************************
*                               �û��ֶ�����
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
		BYTE* R_array1; //ͼ1 RGB���������ֱ����˲�
		BYTE* G_array1;
		BYTE* B_array1;

		BYTE* R_array2; //ͼ2 RGB���������ֱ����˲�
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

