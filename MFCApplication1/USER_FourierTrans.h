// FourierTrans.h: interface for the FourierTrans class.
//
//copy from others

#if !defined(AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_)
#define AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�������ͽṹ��
struct ComplexNumber
{
	float imag;// imaginary�鲿
	float real;//ʵ��
};


class FourierTrans
{

public:

	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char* m_pImgDataOut;

	//���ͼ��Ŀ�
	int m_imgWidthOut;

	//���ͼ��ĸ�
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

	//����Ҷ�任������
	ComplexNumber* m_pFFTBuf;

	//ͼ���Ƿ���չ�ı�־����
	bool m_isExpanded;
public:
	FourierTrans();
	virtual ~FourierTrans();
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();


	//ͼ����Ҷ�任
	void Fourier();

	//����Ҷ���任
	void RevFourier();

public:
	//һά���ٸ���Ҷ���任
	void ImageFFt1D(ComplexNumber* arrayBuf, int n);

	//һά���ٸ���Ҷ���任
	void ImageRevFFt1D(ComplexNumber* arrayBuf, int n);

	//��ά���ٸ���Ҷ�任
	void ImageFFt2D(unsigned char* imgBuf, int width, int height, unsigned char* imgBufOut);

	//��ά���ٸ���Ҷ�任
	void ImageRevFFt2D(unsigned char* imgBufOut, int width, int height);
};

#endif // !defined(AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_)
