/*
进程结构体
创建
释放
读写缓冲

	访问inq和ouq是互斥的
	读写文件是否互斥？
	先实现进程同步互斥。。。。好麻烦
	答：用软件模拟方法(访前先询)，之前想复杂了。。反正是模拟
		开始都是就绪状态
		然后读文件，缓冲区没有就变成阻塞状态(模拟真实OS--I/O)
		I/O结束后，加入就绪状态
		取就绪头部进入执行状态 	WTIME>Rtime
		执行完一个进程再执行下一个进程	(别问为什么不使用优先级算法，我干脆做一个操作系统算了。。。)
*/
#pragma once

#include<malloc.h>
#include"file.h"
#include"buffpool.h"
#include"stdio.h"
//模拟进程的基本状态
#define Ready 	1
#define Running	2
#define block 	3	
#define MAX_P_NUM 4	//进程数量

//需要的值:mod,Rtime,time
struct Process {	
	int PID;//进程ID
	int state;//进程的状态：就绪、执行、阻塞
	char mod;//进程权限：读？写？
	int Rtime;//到达时间
	int time;//运行时间
	int content[4];//进程内容
	struct Process* next;
}*ReadyQueue,*RunningQueue,*BlockQueue;//就绪队列、执行队列、阻塞队列

int readP[MAX_P_NUM];

//RunningQueue就放一个进程

void initProcess();

void toRunning();	//就绪->运行
void toBlock();	//就绪->阻塞(I/O)
void toReady();	//阻塞->就绪(I/O完成)

void readfile(int fileNum);
void writefile(int fileNum);
void getData(int bufNum);//Running Process get data from buf[bufNum]
void putData(int bufNum);//Running Process put data into buf[bufNum]
