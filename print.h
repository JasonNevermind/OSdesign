/*
显示程序
    磁盘块是否在缓冲池
    进程状态表
    空闲队列状态表
    输入队列状态表
    输出队列状态表
*/
#pragma once

#include"stdio.h"
#include"buffpool.h"


void printBlocks();

void printFile(struct File *file,int num);

void printBuffPool();


