#pragma once



#include <windows.h>
#include <malloc.h>
#include<stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "file.h"

#define EMPTY 0  //缓冲区空
#define FULL 1  //缓冲区满
#define NOTFULL 2   //缓冲区没满
#define WORK 3  //缓冲区工作
#define DIRTY 4 //缓冲区脏，要写回
#define EMPQ -1
#define INQ -2 
#define OUTQ -3
#define MAX_EMPTY_NUM 50
#define MAX_INQ_NUM 10
#define MAX_OUTQ_NUM 10
#define DISK_SIZE 400



void initemq();
void flush();//将缓冲区未满的强制写入
void realse();
void read(struct Buffer buf,struct File file);
bool SearchAndLRU(int address);
void inqLRU(int numb);

bool add_buf(int type, int number);
struct buf_head* take_buf(int type);

void put_buf(int type,int work_buf);
void get_buf(int type);

void printBuffPool();


int disks[DISK_SIZE];

struct Buffer{
    int address;    //首地址
    int blocks[4];  //缓冲存放4个blocks
}Buf[MAX_EMPTY_NUM];//缓冲体 


typedef struct buf_head  //缓冲首部
{
    int bufState;   //缓冲区状态
    int bufNo;    //缓冲区号
    int bufPtr;      //缓冲区内容指针
    int bufSize;    //缓冲区个数
    struct buf_head *next; //缓冲指向下一个指针
}buffer_head;

//三个缓冲队列头与尾指针
buffer_head *hemq, *hinq, *houtq; //队头指针
buffer_head *lemq, *linq, *loutq; //队尾指针


