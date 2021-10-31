#pragma once
/*
**********************************************************************
* ģ������: USER_FILTER
* ժ    Ҫ: �˲���
* ��ǰ�汾: 1.0
* ��    ��: guangjie2333
* �������: 2021-10-22
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
class USER_FILTER
{
	//variable  
	public:
		BYTE* pixelArray;
		int  ArraySize;
		int  high;
		int  width;
		BYTE* R_array; //RGB���������ֱ����˲�
		BYTE* G_array;
		BYTE* B_array;

	protected:

	private:
		//��ͨ�˲�ģ��
		int lowFilterTemplate[9] = {1 ,1 , 1 , 
									  1 , 1 , 1 , 
			                          1 , 1 , 1 };
		//��ͨ�˲�ģ��
		int HighFilterTemplate[9] = { 0, -1, 0,
									   -1,  5, -1,
									    0, -1, 0 };


	//function
	public:
		USER_FILTER(BYTE* array, int  h, int  w);
		~USER_FILTER();
		void LowFilter();
		void HighFilter();
		void MidFilter();
		void MaxFilter();
		void MinFilter();

	protected:
		void SeparateRGB();
		void UnionRGB();
		
	private:
		void Convolution(int flag);//ͼ��ģ����
		void DealLowConvolution(BYTE** matrix);
		void DealHighConvolution(BYTE** matrix);
		void DealMidConvolution(BYTE** matrix);
		void DealMaxConvolution(BYTE** matrix);
		void DealMinConvolution(BYTE** matrix);
};

