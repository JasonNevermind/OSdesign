/*
文件结构



    注：可以不考虑文件的组织形式，这不是我的设计要求
        只用知道这文件包含哪几个磁盘块就行
*/
#pragma once

#include"stdio.h"
#include"buffpool.h"
#define MAX_FILE_NUM 5

struct File
{
    int FileId;//文件id
    int FileAddr;//文件地址(连续分配  起始+偏移)
    int FileText[4];//文件内容(一个文件占用4个磁盘块)
}file[MAX_FILE_NUM];

//文件到底跟磁盘块怎样建立联系？

void initFile();
void initFile1();
void flushFile();   //文件刷新
void flushBlock();  //磁盘刷新


/*
1
1 2 3 4

process1->file1
inq->hinbuf(buf[i])
buf[i].blocks get file1.text
buf[i]->inq

*/
