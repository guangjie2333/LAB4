#include "pch.h"
#include "USER_BLINE_TRANSFORM.h"
/*
********************************************************************************
********************************************************************************
*                               ����&��������
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* ��������:	USER_BLINE_TRANSFORM
* ��������: ���죨��ʼ��������
* �������:	ARRAY1 ��bmpͼ���RGB��ͨ������, h ��ͼ���  w:ͼ���
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-30��
* ע    ��:
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
* ��������:	~USER_BLINE_TRANSFORM
* ��������: ��������������̬���ٵĿռ����
* �������:	none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-30��
* ע    ��:
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
*                               �ӿں���
********************************************************************************
********************************************************************************
*/


/*
******************************************************************************
* ��������:	BlinearTransform
* ��������: ͼ��˫���Ա任�Ľӿں���
* �������:	none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-30��
* ע    ��:
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
*                               ���ܺ���
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* ��������:	SeparateRGB
* ��������: ����RGB����
* �������:	none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-19��
* ע    ��:
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
* ��������:	UnionRGB
* ��������: RGB��������
* �������: none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-19��
* ע    ��:
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
* ��������:	DealRgbMatrixBlinearTransform
* ��������: RGB��������ֱ���˫���Բ�ֵ
* �������: none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-31��
* ע    ��: �ú����򵥵Ķ����ڵ�Ԫ����ƽ�����õ��Ľ����Ϊ��ֵ���
*******************************************************************************
*/
void USER_BLINE_TRANSFORM::DealRgbMatrixBlinearTransform()
{
	//��̬������ά����
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

	//��ʼ��������ת����
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

	//�з���һ�ײ�ֵ
	for (int i = 1; i < high * 2 - 1; i = i + 2)
	{
		for (int j = 0; j < width * 2 - 1; j = j + 2)
		{
			matrixR[i][j] = (BYTE)((matrixR[i - 1][j] + matrixR[i + 1][j]) / 2);
			matrixG[i][j] = (BYTE)((matrixG[i - 1][j] + matrixG[i + 1][j]) / 2);
			matrixB[i][j] = (BYTE)((matrixB[i - 1][j] + matrixB[i + 1][j]) / 2);
		}
	}

	//�з���һ�ײ�ֵ
	for (int i = 0; i < high * 2 - 1; i++)
	{
		for (int j = 1; j < width * 2 - 1; j = j + 2)
		{
			matrixR[i][j] = (BYTE)((matrixR[i][j - 1] + matrixR[i][j + 1]) / 2);
			matrixG[i][j] = (BYTE)((matrixG[i][j - 1] + matrixG[i][j + 1]) / 2);
			matrixB[i][j] = (BYTE)((matrixB[i][j - 1] + matrixB[i][j + 1]) / 2);
		}
	}

	//����ת����
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

	//�ͷ�
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
