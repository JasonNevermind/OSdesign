#include"process.h"


//读写文件------->最终目的！！！

void initProcess()  //一开始都就绪队列
{
    ReadyQueue=(struct Process *)malloc(sizeof(struct Process));//头没用
    ReadyQueue->mod='x';
    ReadyQueue->PID=-1;
    ReadyQueue->Rtime=-1;
    ReadyQueue->state=-1;
    ReadyQueue->time=-1;
    struct Process *s=ReadyQueue;
    for(int i=0;i<MAX_P_NUM;i++){
        struct Process* tmp=(struct Process *)malloc(sizeof(struct Process));
        tmp->PID=i;
        tmp->state=Ready;
        tmp->next=NULL;
        s->next=tmp;
        printf("请输入进程%d的权限(mod),到达时间(Rtime),运行时间(time):\n",i);
        scanf(" %c",&tmp->mod);
        scanf("%d %d",&tmp->Rtime,&tmp->time);
        if(tmp->mod=='r'){
            printf("请写入数据:\n");
            for(int i=0;i<4;i++){
                scanf("%d",&tmp->content[i]);
            }
        }
        s=s->next;
    }
    s=ReadyQueue;
    ReadyQueue=ReadyQueue->next;
    free(s);
}

void printProcess()
{
    struct Process* tmp=ReadyQueue;
    printf("进程ID\t进程状态\t进程权限\t到达时间\t运行时间\t\n");
    while(tmp){
        printf("%d\t%d\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,tmp->state,tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
    tmp=RunningQueue;
    while(tmp){
        printf("%d\t%d\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,tmp->state,tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
    tmp=BlockQueue;
    while(tmp){
        printf("%d\t%d\t\t%c\t\t%d\t\t%d\t\t\n",tmp->PID,tmp->state,tmp->mod,tmp->Rtime,tmp->time);
        tmp=tmp->next;
    }
}


void rwUI()
{
    printFile();
    printf("进程%d想%c文件ID?:",RunningQueue->PID,RunningQueue->mod);
    int numb=0;
    scanf("%d",&numb);
    //system("cls");
    if(RunningQueue->mod=='r'){
        printf("正在读取.....\n");
        readfile(numb);
    }
    else if(RunningQueue->mod=='w'){
        printf("正在写入.....\n");
        writefile(numb);
    }

}

void viewUI()
{
    printf("--------接下来您想进行的操作:--------\n");
    printf("----  1.查看进程状态\t\n");
    printf("----  2.查看文件\n");
    printf("----  3.查看缓冲池\n");
    printf("----  4.查看磁盘使用情况\n");
}


void readfile(int fileNum)
{//process x get file's content which is "x x x x".
    
    bool isFind = SearchAndLRU(file[fileNum].FileAddr);
	if(isFind==false){
		//cant find
		buffer_head *hin = take_buf(EMPQ);
		//hin get disk data
		bool b = add_buf(INQ, hin->bufNo);
		if(!b)
			inqLRU(hin->bufNo);
		free(hin);
		
		buffer_head *sin = take_buf(INQ);
		//process read sin's data
		add_buf(EMPQ, sin->bufNo);
		free(sin);
	}
	else if(isFind==true){
		//can find
		buffer_head *sin = take_buf(INQ);
		//process read sin's data
		add_buf(EMPQ, sin->bufNo);
		free(sin);
	}
    //print file's data

}

void writefile(int fileNum)    //目的是先写到缓冲，再将它写到blocks
{//process wirte file, file content has changed

    buffer_head *hout = take_buf(EMPQ);
	//process write hout
	bool b = add_buf(OUTQ, hout->bufNo);
	if(!b){
		flush();		//延迟写，等缓冲队列满了再写
		add_buf(OUTQ,houtq->bufNo);
	}
	free(hout);

	buffer_head *sout = take_buf(OUTQ); 
	//disk get write-back data
	add_buf(EMPQ, sout->bufNo);
	free(sout);
    //file context has changed
}

/*

int main()
{
    //initProcess();
    //printProcess();
    
    initemq();
    printBuffPool();


    return 0;
}
*/
