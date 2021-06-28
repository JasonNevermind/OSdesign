
#include"print.h"

void printBlocks()
{
    printf("------位示图法显示磁盘块------\n磁盘块  ");

    for (int i = 0; i < 8; i++)
    {
        printf("%d  ",i);
    }
    printf("\n0\t");
    for(int i=0;i<DISK_SIZE;i++){
        printf("%d  ",disks[i]);
        if(i!=0 && (i+1)%8==0 && i!=DISK_SIZE-1)
            printf("\n%d\t",(i/8)+1);
    }
    printf("\n");
}

void printFile()
{
    printf("文件ID\t起始地址\t文件内容\n");
    for(int i=0;i<MAX_FILE_NUM;i++){
        printf("%d\t%d\t\t",file[i].FileId,file[i].FileAddr);
        for(int j=0;j<4;j++){
            printf("%d  ",file[i].FileText[j]);
        }
        printf("\n");
    }
}

char *s[]={"EMPTY","FULL","NOTFULL","WORK","DIRTY"};

void printBuffPool()
{
    
	buffer_head *tmp = hinq;
	printf("缓冲队列类型\t缓冲区号\t缓冲区状态\t缓冲队列大小\t\n");
	while (tmp)
	{
		printf("inq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], linq->bufSize);
		tmp = tmp->next;
	}
	tmp = houtq;
	while (tmp)
	{
		printf("outq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], loutq->bufSize);
		tmp = tmp->next;
	}
	tmp = hemq;
	while (tmp)
	{
		printf("emq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], lemq->bufSize);
		tmp = tmp->next;
	}
}

void printProcess()
{
    char *state[]={"null","Ready","Running","Block"};
    struct Process* tmp=RunningQueue;
    printf("进程ID\t进程状态\t进程权限\t到达时间\t运行时间\t\n");
    while(tmp){
        printf("%d\t%s\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,state[tmp->state],tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
    tmp=ReadyQueue;
    while(tmp){
        printf("%d\t%s\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,state[tmp->state],tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
    tmp=BlockQueue;
    while(tmp){
        printf("%d\t%s\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,state[tmp->state],tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
}

void printInq()
{
    buffer_head *tmp = hinq;
	printf("缓冲队列类型\t缓冲区号\t缓冲区状态\t缓冲队列大小\t\n");
	while (tmp)
	{
		printf("inq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], linq->bufSize);
		tmp = tmp->next;
	}
}

void printOutq()
{
    buffer_head *tmp = houtq;
	printf("缓冲队列类型\t缓冲区号\t缓冲区状态\t缓冲队列大小\t\n");
	while (tmp)
	{
		printf("outq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], loutq->bufSize);
		tmp = tmp->next;
	}
}

void printEmq()
{
    buffer_head *tmp = hemq;
	printf("缓冲队列类型\t缓冲区号\t缓冲区状态\t缓冲队列大小\t\n");
	while (tmp)
	{
		printf("emq\t\t%d\t\t%s\t\t\t%d\t\t\n", tmp->bufNo,s[tmp->bufState], lemq->bufSize);
		tmp = tmp->next;
	}
}

void printFileToP()
{
    printf("进程ID\t\t文件ID\t\t读写权限\t进程内容\t文件内容\n");
    struct Process* tmp=ReadyQueue;
    for(;tmp;tmp=tmp->next){
        printf("%d\t\t%d\t\t%c\t\t",tmp->PID,readP[tmp->PID],tmp->mod);
        for(int i=0;i<4;i++)
            printf("%d ",tmp->content[i]);
        printf("\t");
        for(int i=0;i<4;i++)
            printf("%d ",file[readP[tmp->PID]].FileText[i]);
        printf("\n");
    }
}

void rwUI()
{
    printFile();
    struct Process *tmp=ReadyQueue;
    for(int i=0;i<MAX_P_NUM;i++){
        printf("进程%d想%c文件ID?:",i,tmp->mod);
        scanf("%d",&readP[i]);
        tmp=tmp->next;
    }
}
void rwUI1()
{
    struct Process *tmp=ReadyQueue;
    for(int i=0;i<MAX_P_NUM;i++){
        //srand((unsigned)time(NULL));
        readP[i]=rand()%MAX_FILE_NUM;
        tmp=tmp->next;
    }
}

void viewUI()
{
    printf("--------任务资源管理器:--------\n");
    printf("----  1.查看进程状态\t\n");
    printf("----  2.查看文件\n");
    printf("----  3.查看缓冲池\n");
    printf("----  4.查看磁盘使用情况\n");
    printf("----  5.进程想要读写文件\n");
}