#include "pch.h"
#include "USER_ALG.h"

/*
********************************************************************************
********************************************************************************
*                               接口函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	Qsort
* 函数功能: 实现一维数组的快速排序
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_ALG :: QuickSort(int* A, int N)
{
    Qsort(A, 0, N - 1);
}

/*
******************************************************************************
* 函数名称:	Swap
* 函数功能: 实现交换两个数
* 输入参数: 两个int型数
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意: 
*******************************************************************************
*/
void USER_ALG::Swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*
******************************************************************************
* 函数名称:	Swap
* 函数功能: 实现交换两个数
* 输入参数: 两个BYTE型数
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意: 函数的重载
*******************************************************************************
*/
void USER_ALG::Swap(BYTE* a, BYTE* b)
{
    BYTE temp;
    temp = *a;
    *a = *b;
    *b = temp;
}





/*
********************************************************************************
********************************************************************************
*                               内部函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	Qsort
* 函数功能: 默认 0 - N-1 实现一维数组的快速排序
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_ALG:: Qsort(int* A, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int Pivot, low, high;

    //元素多就使用快速排序

    Pivot = Median3(A, left, right);//选基准
    low = left;
    high = right - 1; //high初始位置为基准位置

    if (low >= high)
    {
        return;
    }

    while (1)
    {
        while (A[++low] < Pivot) //从low + 1开始 （从1开始）
        {
            //当A[low] >= Pivot 时自动退出
        }

        while (A[--high] > Pivot) // 从right - 2 开始
        {
            //当A[high] <= Pivot 时自动退出
        }

        if (low < high)//前后交换
        {
            Swap(&A[low], &A[high]);
        }
        else
        {
            break;
        }
    }
    if (right - 1)
    {

    }
    Swap(&A[low], &A[right - 1]);
    Qsort(A, left, low - 1);//比基准小的序列递归
    Qsort(A, low + 1, right);//比基准大的序列递归
}
/*
******************************************************************************
* 函数名称:	Median3
* 函数功能: 三个数找中位数
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
int USER_ALG:: Median3(int* A, int left, int right)
{
    int center = (left + right) / 2;

    if (A[left] > A[center])
    {
        Swap(&A[left], &A[center]);
    }

    if (A[left] > A[right])
    {
        Swap(&A[left], &A[right]);
    }

    if (A[center] > A[right])
    {
        Swap(&A[center], &A[right]);
    }

    Swap(&A[center], &A[right - 1]);//将基准Pivot藏到右边

    return  A[right - 1];
}


