#pragma once



#include <windows.h>
#include <malloc.h>
#include<stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "file.h"

#define EMPTY 0  //��������
#define FULL 1  //��������
#define NOTFULL 2   //������û��
#define WORK 3  //����������
#define DIRTY 4 //�������࣬Ҫд��

#define EMPQ -1
#define INQ -2 
#define OUTQ -3
#define MAX_EMPTY_NUM 50
#define MAX_INQ_NUM 10
#define MAX_OUTQ_NUM 10
#define DISK_SIZE 400



void initemq();
void flush();//��������δ����ǿ��д��
void realse();
void read(int bufNum,int fileNum);
void write(int bufNum);
bool SearchAndLRU(int address);
void inqLRU(int numb);

bool add_buf(int type, int number);
struct buf_head* take_buf(int type);

void BufToDisk();
void DiskToBuf(int fileNum);


int disks[DISK_SIZE];

struct Buffer{
    int address;    //�׵�ַ
    int blocks[4];  //������4��blocks
}Buf[MAX_EMPTY_NUM];//������ 


typedef struct buf_head  //�����ײ�
{
    int bufState;   //������״̬
    int bufNo;    //��������
    int bufPtr;      //����������ָ��
    int bufSize;    //����������
    struct buf_head *next; //����ָ����һ��ָ��
}buffer_head;

//�����������ͷ��βָ��
buffer_head *hemq, *hinq, *houtq; //��ͷָ��
buffer_head *lemq, *linq, *loutq; //��βָ��


