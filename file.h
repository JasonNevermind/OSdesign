/*
�ļ��ṹ



    ע�����Բ������ļ�����֯��ʽ���ⲻ���ҵ����Ҫ��
        ֻ��֪�����ļ������ļ������̿����
*/
#pragma once

#include"stdio.h"
#define MAX_FILE_NUM 5
#include"buffpool.h"

struct File
{
    int FileId;//�ļ�id
    int FileAddr;//�ļ���ַ(��������  ��ʼ+ƫ��)
    int FileText[4];//�ļ�����(һ���ļ�ռ��4�����̿�)
}file[MAX_FILE_NUM];

//�ļ����׸����̿�����������ϵ��

void initFile();
void flushFile();   //�ļ�ˢ��



/*
1
1 2 3 4

process1->file1
inq->hinbuf(buf[i])
buf[i].blocks get file1.text
buf[i]->inq

*/
