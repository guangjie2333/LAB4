#pragma once

/*
**********************************************************************
* ģ������: USER_PIC_FLIP
* ժ    Ҫ: ͼ��ת��
* ��ǰ�汾: 1.0
* ��    ��: guangjie2333
* �������: 2021-10-30
* ��    ��:
* ע    ��: V1.0�汾ֻ����ˮƽ��ת
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
		BYTE* R_array; //RGB���������ֱ����˲�
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

