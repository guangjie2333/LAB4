#pragma once
/*
���� ��guangjie2333
ʱ�� ��2021.10.5
��λ ��SZU
�汾 ��V1.0.0
*/

#include <iostream>
#include "USER_DEFINE.h"
using namespace std;


/********************�ඨ����*********************/

class USER_RGB_HSV_CLASS
{
    public:
        //��ʼ��&�˳�
        USER_RGB_HSV_CLASS(void);//���캯������
        ~USER_RGB_HSV_CLASS(void);//������������

        //�û��Զ��庯�� 
        HSV_STRUCT RGB2HSV(RGB_STRUCT rgb);
        RGB_STRUCT HSV2RGB(HSV_STRUCT hsv);

};

