#include"process.h"


//读写文件------->最终目的！！！

void initProcess()  //一开始都就绪队列(先输入的在队列尾)
{
    ReadyQueue=(struct Process *)malloc(sizeof(struct Process));//虚拟头结点
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
        for(int j=0;j<4;j++)
            tmp->content[j]=0;
        tmp->next=NULL;
        s->next=tmp;
        printf("请输入进程%d的权限(mod),到达时间(Rtime),运行时间(time):\n",i);
        scanf(" %c",&tmp->mod);
        scanf("%d",&tmp->Rtime);
        scanf("%d",&tmp->time);

        //scanf("%c %d %d",&tmp->mod,&tmp->Rtime,&tmp->time);
        if(tmp->mod=='w'){
            printf("请写入数据:\n");
            for(int i=0;i<4;i++){
                scanf("%d",&tmp->content[i]);
            }
        }
        s=s->next;
        lReady=s;
    }
    s=ReadyQueue;
    ReadyQueue=ReadyQueue->next;
    free(s);
}

void initProcess1()
{
    ReadyQueue=(struct Process *)malloc(sizeof(struct Process));//虚拟头结点
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
        for(int j=0;j<4;j++)
            tmp->content[j]=0;
        tmp->next=NULL;
        s->next=tmp;
        
        int r=rand()%100;
        if(r>50)    tmp->mod='r';
        else tmp->mod='w';

        tmp->Rtime=rand()%30;
        tmp->time=rand()%10;

        if(tmp->mod=='w'){
            for(int i=0;i<4;i++){
                tmp->content[i]=rand()%10;
            }
        }
        s=s->next;
        lReady=s;
    }
    s=ReadyQueue;
    ReadyQueue=ReadyQueue->next;
    free(s);
}

void sortPQue()//(early-->late)
{
    struct Process* p,*q;
    p=ReadyQueue;
    for(;p!=NULL;p=p->next)//选定的位置，从第一个位置开始
    {
        for(q=p->next;q!=NULL;q=q->next)//每次遍历一遍链表，只要比选定位置的数据小就交换
        {
            if(q->Rtime<p->Rtime)
            {
                struct Process* tmp=(struct Process*)malloc(sizeof(struct Process));
                tmp->PID=q->PID;
                tmp->Rtime=q->Rtime;
                tmp->time=q->time;
                q->PID=p->PID;
                q->Rtime=p->Rtime;
                q->time=p->time;
                p->PID=tmp->PID;
                p->Rtime=tmp->Rtime;
                p->time=tmp->time;
                free(tmp);
            }
        }
    }
}


void getData(int bufNum)    //Running Process get data from buf[bufNum]
{
    for(int i=0;i<4;i++)
    {
        RunningQueue->content[i]=Buf[bufNum].blocks[i];
    }
}
void putData(int bufNum)    //Running Process put data into buf[bufNum]
{
    Buf[bufNum].address=file[readP[RunningQueue->PID]].FileAddr;
    for(int i=0;i<4;i++)
    {
        Buf[bufNum].blocks[i]=RunningQueue->content[i];
    }
}


void BufToPro()
{
    buffer_head *sin = take_buf(INQ);
	//process read sin's data
    getData(sin->bufNo);

	add_buf(EMPQ, sin->bufNo);
	free(sin);
}

void ProToBuf()
{
    buffer_head *hout = take_buf(EMPQ);
	//process write hout
    putData(hout->bufNo);

	bool b = add_buf(OUTQ, hout->bufNo);
	if(!b){
		flush();		//延迟写，等缓冲队列满了再写
		add_buf(OUTQ,houtq->bufNo);
	}
	free(hout);
}



void toRunning()
{
    if(!ReadyQueue)
        return;
    //每次从Ready头部拿一个Running
    struct Process* tmp=ReadyQueue;
    if(!RunningQueue){
        RunningQueue=tmp;
        RunningQueue->state=Running;
        ReadyQueue=ReadyQueue->next;
        RunningQueue->next=NULL;
    }
    else{
        printf("运行队列已满！");
    }
}

void toBlock()
{
    //每次从Ready头部拿一个放到Block尾部
    if(!ReadyQueue)
        return;
    struct Process* tmp=ReadyQueue;
    ReadyQueue=ReadyQueue->next;
    tmp->next=NULL;
    if(!BlockQueue){
        BlockQueue=tmp;
        BlockQueue->state=block;
        lBlock=BlockQueue;
    }
    else{
        lBlock->next=tmp;
        lBlock=lBlock->next;
        lBlock->state=block;
    }
}

void toReady()
{
    //每次从Block头部拿一个放到Ready头部
    if(!BlockQueue)
        return;
    struct Process* tmp=BlockQueue;
    BlockQueue=BlockQueue->next;
    tmp->next=NULL;
    if(!ReadyQueue){
        ReadyQueue=tmp;
        ReadyQueue->state=Ready;
        lReady=ReadyQueue;
    }
    else{
        tmp->next=ReadyQueue;
        tmp->state=Ready;
        ReadyQueue=tmp;
    }
}
