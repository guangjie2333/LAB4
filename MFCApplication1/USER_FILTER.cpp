#include "pch.h"
#include "USER_FILTER.h"


/*
********************************************************************************
********************************************************************************
*                               ����&��������
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* ��������:	USER_FILTER
* ��������: ���죨��ʼ��������
* �������:	array ��bmpͼ���RGB��ͨ������, h ��ͼ���  w:ͼ���
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-19��
* ע    ��:
*******************************************************************************
*/
USER_FILTER::USER_FILTER(BYTE* array, int  h, int  w)
{
	pixelArray = array;
	high = h;
	width = w;
	ArraySize = high * width * 3;

	R_array = (BYTE*)new char[ArraySize / 3 + 1];
	G_array = (BYTE*)new char[ArraySize / 3 + 1];
	B_array = (BYTE*)new char[ArraySize / 3 + 1];
}
/*
******************************************************************************
* ��������:	~USER_HIS_EQU
* ��������: ��������������̬���ٵĿռ����
* �������:	none
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-19��
* ע    ��:
*******************************************************************************
*/
USER_FILTER::~USER_FILTER()
{
	delete[] R_array;
	delete[] G_array;
	delete[] B_array;
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
* ��������:	LowFilter
* ��������: ʵ��һ��ͼ��ĵ�ͨ�˲�
* �������: none
* �������:	none
* �� �� ֵ: void
* ��������: 2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::LowFilter()
{
	SeparateRGB();//����RGB�ֱ����˲�
	Convolution(0);//0�����ͨ�˲����
	UnionRGB();
}

/*
******************************************************************************
* ��������:	HighFilter
* ��������: ʵ��һ��ͼ��ĸ�ͨ�˲�
* �������: none
* �������:	none
* �� �� ֵ: void
* ��������: 2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::HighFilter()
{
	SeparateRGB();//����RGB�ֱ����˲�
	Convolution(1);//1�����ͨ�˲����
	UnionRGB();
}

/*
******************************************************************************
* ��������:	MidFilter
* ��������: ʵ��һ��ͼ�����ֵ�˲�
* �������: none
* �������:	none
* �� �� ֵ: void
* ��������: 2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::MidFilter()
{
	SeparateRGB();//����RGB�ֱ����˲�
	Convolution(2);//2������ֵ�˲����
	UnionRGB();
}

/*
******************************************************************************
* ��������:	MaxFilter
* ��������: ʵ��һ��ͼ������ֵ�˲�
* �������: none
* �������:	none
* �� �� ֵ: void
* ��������: 2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::MaxFilter()
{
	SeparateRGB();//����RGB�ֱ����˲�
	Convolution(3);//3�������ֵ�˲����
	UnionRGB();
}

/*
******************************************************************************
* ��������:	MinFilter
* ��������: ʵ��һ��ͼ�����Сֵ�˲�
* �������: none
* �������:	none
* �� �� ֵ: void
* ��������: 2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::MinFilter()
{
	SeparateRGB();//����RGB�ֱ����˲�
	Convolution(4);//4������Сֵ�˲����
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

void USER_FILTER::SeparateRGB()
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
void USER_FILTER::UnionRGB()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArray[i + 2] = R_array[j];
		pixelArray[i + 1] = G_array[j];
		pixelArray[i + 0] = B_array[j];

		j++;
	}
}

/*
******************************************************************************
* ��������:	Convolution
* ��������: RGB ʵ��ͼ����
* �������: flag �� 0 ��ͨ�˲�ģ���� 
*				    1 ��ͨ�˲�ģ���� 
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:��ֵ��max��min�ı������������㷨
		   �������������󣬵�������Ϊ�����㷨��ѡȡ����Ҫ������Ĺ���ʦ�ܾ�ð�� 
		   ���½���һ������㷨�࣬�������Ҵ���ʱ��д�Ŀ���������㷨�����ھ���ʵ��������hhh��
*******************************************************************************
*/
void USER_FILTER::Convolution(int flag)
{
	//��̬������ά����
	BYTE** matrixR;
	BYTE** matrixG;
	BYTE** matrixB;
	matrixR = new BYTE * [high];
	matrixG = new BYTE * [high];
	matrixB = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixR[j] = new BYTE[width];
		matrixG[j] = new BYTE[width];
		matrixB[j] = new BYTE[width];
	}

	//��ʼ��
	int k = 0;
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixR[i][j] = R_array[k];
			matrixG[i][j] = G_array[k];
			matrixB[i][j] = B_array[k];
			k++;
		}
	}

	//ģ���� &MAX &MIN &MID�˲�
	switch (flag)
	{
		case 0 :
			DealLowConvolution(matrixR); //��ʵ��һ������ʵ��Ҳ���ԣ��������뱣�������Ĵ�����
			DealLowConvolution(matrixG);
			DealLowConvolution(matrixB);
			break;
		case 1 :
			DealHighConvolution(matrixR);
			DealHighConvolution(matrixG);
			DealHighConvolution(matrixB);
			break;
		case 2:
			DealMidConvolution(matrixR); 
			DealMidConvolution(matrixG);
			DealMidConvolution(matrixB);
			break;
		case 3:
			DealMaxConvolution(matrixR);
			DealMaxConvolution(matrixG);
			DealMaxConvolution(matrixB);
			break;
		case 4:
			DealMinConvolution(matrixR);
			DealMinConvolution(matrixG);
			DealMinConvolution(matrixB);
			break;
		default:
			break;
	}

	//�������ش�
    k = 0;
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			R_array[k] = matrixR[i][j];
			G_array[k] = matrixG[i][j];
			B_array[k] = matrixB[i][j];
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


/*
******************************************************************************
* ��������:	DealLowConvolution
* ��������: �����ͨ�˲�
* �������:  matrix����ά����
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER :: DealLowConvolution(BYTE** matrix)
{
	//��̬������ά����
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//��ʼ��
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//���
	for (int i = 1; i < high - 1 ; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] =  matrixNew[i - 1][j - 1] * lowFilterTemplate[0] +
							matrixNew[i - 1][j - 0] * lowFilterTemplate[1] +
							matrixNew[i - 1][j + 1] * lowFilterTemplate[2] +
							matrixNew[i - 0][j - 1] * lowFilterTemplate[3] +
							matrixNew[i - 0][j - 0] * lowFilterTemplate[4] +
							matrixNew[i - 0][j + 1] * lowFilterTemplate[5] +
							matrixNew[i + 1][j - 1] * lowFilterTemplate[6] +
							matrixNew[i + 1][j - 0] * lowFilterTemplate[7] +
							matrixNew[i + 1][j + 1] * lowFilterTemplate[8] ;
			matrix[i][j] /= 9;
			matrix[i][j] = matrix[i][j] < 0 ? 0 : matrix[i][j];
			matrix[i][j] = matrix[i][j] > 255 ? 255 : matrix[i][j];
		}
	}

	//�ͷ�
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;

}

/*
******************************************************************************
* ��������:	DealHighConvolution
* ��������: �����ͨ�˲�
* �������:  matrix����ά����
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::DealHighConvolution(BYTE** matrix)
{
	//��̬������ά����
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//��ʼ��
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//���
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] =  matrixNew[i - 1][j - 1] * HighFilterTemplate[0] +
							matrixNew[i - 1][j - 0] * HighFilterTemplate[1] +
							matrixNew[i - 1][j + 1] * HighFilterTemplate[2] +
							matrixNew[i - 0][j - 1] * HighFilterTemplate[3] +
							matrixNew[i - 0][j - 0] * HighFilterTemplate[4] +
							matrixNew[i - 0][j + 1] * HighFilterTemplate[5] +
							matrixNew[i + 1][j - 1] * HighFilterTemplate[6] +
							matrixNew[i + 1][j - 0] * HighFilterTemplate[7] +
							matrixNew[i + 1][j + 1] * HighFilterTemplate[8] ;

			matrix[i][j] = matrix[i][j] < 0 ? 0 : matrix[i][j];
			matrix[i][j] = matrix[i][j] > 255 ? 255 : matrix[i][j];
		}
	}

	//�ͷ�
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}


/*
******************************************************************************
* ��������:	DealMidConvolution
* ��������: ������ֵ�˲�
* �������:  matrix����ά����
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::DealMidConvolution(BYTE** matrix)
{
	//��̬������ά����
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//��ʼ��
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//���
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//����
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray,9);
			//��λ��
			matrix[i][j] = TmpArray[(int)9/2];

		}
	}

	//�ͷ�
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}

/*
******************************************************************************
* ��������:	DealMaxConvolution
* ��������: �������ֵ�˲�
* �������:  matrix����ά����
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::DealMaxConvolution(BYTE** matrix)
{
	//��̬������ά����
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//��ʼ��
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//���
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//����
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray, 9);
			//���ֵ
			matrix[i][j] = TmpArray[8];

		}
	}

	//�ͷ�
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}

/*
******************************************************************************
* ��������:	DealMinConvolution
* ��������: ������Сֵ�˲�
* �������:  matrix����ά����
* �������:	none
* �� �� ֵ:  void
* ��������:  2021��-10��-22��
* ע    ��:
*******************************************************************************
*/
void USER_FILTER::DealMinConvolution(BYTE** matrix)
{
	//��̬������ά����
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//��ʼ��
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//���
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//����
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray, 9);
			//��Сֵ
			matrix[i][j] = TmpArray[0];

		}
	}

	//�ͷ�
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}