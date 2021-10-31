#pragma once
/*
**********************************************************************
* ģ������: USER_BLINE_TRANSFORM
* ժ    Ҫ: ˫���Ա任��
* ��ǰ�汾: 1.0
* ��    ��: guangjie2333
* �������: 2021-10-31
* ��    ��:
* ע    ��: ����RGB��ͨ��ͼ
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
		BYTE* R_array; //RGB��������
		BYTE* G_array;
		BYTE* B_array;
		BYTE* newR_array; //˫���Բ�ֵ���RGB��������
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

