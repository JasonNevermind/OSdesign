/*
���̽ṹ��
����
�ͷ�
��д����

	����inq��ouq�ǻ����
	��д�ļ��Ƿ񻥳⣿
	��ʵ�ֽ���ͬ�����⡣���������鷳
	�������ģ�ⷽ��(��ǰ��ѯ)��֮ǰ�븴���ˡ���������ģ��
		��ʼ���Ǿ���״̬
		Ȼ����ļ���������û�оͱ������״̬(ģ����ʵOS--I/O)
		I/O�����󣬼������״̬
		ȡ����ͷ������ִ��״̬ 	WTIME>Rtime
		ִ����һ��������ִ����һ������	(����Ϊʲô��ʹ�����ȼ��㷨���Ҹɴ���һ������ϵͳ���ˡ�����)
*/
#pragma once

#include<malloc.h>
#include"file.h"
#include"buffpool.h"
#include"stdio.h"
//ģ����̵Ļ���״̬
#define Ready 	1
#define Running	2
#define block 	3	
#define MAX_P_NUM 4	//��������

//��Ҫ��ֵ:mod,Rtime,time
struct Process {	
	int PID;//����ID
	int state;//���̵�״̬��������ִ�С�����
	char mod;//����Ȩ�ޣ�����д��
	int Rtime;//����ʱ��
	int time;//����ʱ��
	int content[4];//��������
	struct Process* next;
}*ReadyQueue,*RunningQueue,*BlockQueue;//�������С�ִ�ж��С���������



void initProcess();
void printProcess();
void readfile(int fileNum);
void writefile(int fileNum);
void rwUI();
void viewUI();