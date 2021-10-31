#pragma once

/*
���� ��guangjie2333
ʱ�� ��2021.10.5
��λ ��SZU
�汾 ��V1.0.0
*/

#include <wingdi.h> 
#include <afx.h>
using namespace std; 

/***********************����ͷ�ļ�******************************/
#include "USER_ALG.h"

/*************************�궨����*******************************/

#define WM_GET_DIALOG_HSV_SLIDER_VAL		(WM_USER + 200)            //�ñ���������������֮�䴫����Ϣ


/***********************�ṹ�嶨����******************************/

//RGB�ṹ�嶨��
typedef struct
{
    int r;
    int g;
    int b;
} RGB_STRUCT;

//HSV�ṹ�嶨��
typedef struct
{
    int h;
    float s;
    float v;
} HSV_STRUCT;

//��������ֵ�ṹ��
typedef struct
{
    int H_slider;
    int S_slider;
    int V_slider;
}HSV_SLIDER_STRUCT;


typedef struct
{
    BYTE* pBmpData;             //ͼ������
    BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
    BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
    CFile bmpFile;              //��¼���ļ�
}bmpData;