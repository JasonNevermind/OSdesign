#include"process.h"


//读写文件------->最终目的！！！

void initProcess()  //一开始都就绪队列(倒着建立的,先输入的在队列尾)
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
    }
    s=ReadyQueue;
    ReadyQueue=ReadyQueue->next;
    free(s);
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
    for(int i=0;i<4;i++)
    {
        Buf[bufNum].blocks[i]=RunningQueue->content[i];
    }
}


void readfile(int fileNum)
{//process x get file's content which is "x x x x".
    
    bool isFind = SearchAndLRU(file[fileNum].FileAddr);
	if(isFind==false){
		//cant find
		buffer_head *hin = take_buf(EMPQ);
		//hin get disk data
        read( hin->bufNo, fileNum );
		bool b = add_buf(INQ, hin->bufNo);
		if(!b)
			inqLRU(hin->bufNo);
		free(hin);
		
		buffer_head *sin = take_buf(INQ);
		//process read sin's data
        getData(sin->bufNo);
		add_buf(EMPQ, sin->bufNo);
		free(sin);
	}
	else if(isFind==true){
		//can find
		buffer_head *sin = take_buf(INQ);
		//process read sin's data
        getData(sin->bufNo);
		add_buf(EMPQ, sin->bufNo);
		free(sin);
	}
    //print file's data

    //等待时间到
    printf("进程%d读到的内容是：",RunningQueue->PID);
    for(int i=0;i<4;i++){
        printf("%d ",RunningQueue->content[i]);
    }
    printf("\n");

    printf("进程%d任务已结束!\n",RunningQueue->PID);
    struct Process *p=RunningQueue;
    RunningQueue=NULL;
    free(p);
}

void writefile(int fileNum)    //目的是先写到缓冲，再将它写到blocks
{//process wirte file, file content has changed

    buffer_head *hout = take_buf(EMPQ);
	//process write hout
    putData(hout->bufNo);
	bool b = add_buf(OUTQ, hout->bufNo);
	if(!b){
		flush();		//延迟写，等缓冲队列满了再写
		add_buf(OUTQ,houtq->bufNo);
	}
	free(hout);

	buffer_head *sout = take_buf(OUTQ);
	//disk get write-back data
    write(sout->bufNo);
	add_buf(EMPQ, sout->bufNo);
	free(sout);
    //file context has changed

    flushFile();
    printf("进程%d内容已写入文件ID%d!\n",RunningQueue->PID,fileNum);
    struct Process *p=RunningQueue;
    RunningQueue=NULL;
    free(p);
}

void toRunning()
{
    //每次从Ready头部拿一个Running
    struct Process* tmp=ReadyQueue;
    if(!RunningQueue){
        RunningQueue=tmp;
        RunningQueue->next=NULL;
        ReadyQueue=ReadyQueue->next;
    }
    else{
        printf("运行队列已满！");
    }
}

void toBlock()
{
    //每次从Ready头部拿一个放到Block尾部
    struct Process* tmp=ReadyQueue;
    tmp->next=NULL;
    ReadyQueue=ReadyQueue->next;
    struct Process* t=BlockQueue;
    if(t==NULL){
        BlockQueue=tmp;
        return;
    }
    struct Process* f=BlockQueue;
    t=f->next;
    while(t && !t->next){
        f=f->next;
        t=t->next;
    }
    if(!t){
        f->next=tmp;
        return ;
    }
    f->next==NULL;
    t->next=BlockQueue;
    BlockQueue=t;
}

void toReady()
{
    //每次从Block头部拿一个放到Ready尾部
    struct Process* tmp=ReadyQueue;
    tmp->next=NULL;
    ReadyQueue=ReadyQueue->next;
    struct Process* t=BlockQueue;
    if(t==NULL){
        BlockQueue=tmp;
        return;
    }
    struct Process* f=BlockQueue;
    t=f->next;
    while(t && !t->next){
        f=f->next;
        t=t->next;
    }
    if(!t){
        f->next=tmp;
        return ;
    }
    f->next==NULL;
    t->next=BlockQueue;
    BlockQueue=t;
}
