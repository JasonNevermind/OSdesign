#include "buffpool.h"
#include"file.c"
#include"process.c"


void read(int bufNum, int fileNum)	//缓冲体读取(从文件里读)
{
	Buf[bufNum].address = file[fileNum].FileAddr;
	for (int i = 0; i < 4; i++)
	{
		Buf[bufNum].blocks[i] = file[fileNum].FileText[i];
	}
}
void write(int bufNum)	//缓冲体写(写到磁盘上)
{

	for (int i = 0; i < 4; i++)
	{
		disks[Buf[bufNum].address+i] = Buf[bufNum].blocks[i] ;
	}
}

void flush() //输出缓冲outq写入disk
{
	buffer_head *tmp = houtq;
	while (tmp)
	{
		int add = Buf[tmp->bufNo].address;
		for (int i = 0; i <= tmp->bufPtr; i++)
		{ //tmp->bufPtr一般等于3，因为提前读要写完了才能挂到inq上
			disks[add + i] = Buf[tmp->bufNo].blocks[i];
		}
		buffer_head *t = tmp;
		tmp = tmp->next;
		free(t);
	}
	//磁盘块内容改了，相应的文件内容也得改
	flushFile();
}

void initemq()
{
	int i = MAX_EMPTY_NUM;
	buffer_head *t;

	if (hemq == NULL)
	{
		hemq = (buffer_head *)malloc(sizeof(buffer_head));
		hemq->bufNo = 0;
		hemq->bufPtr = 0;
		hemq->bufSize = MAX_EMPTY_NUM;
		hemq->bufState = EMPTY;
		hemq->next = NULL;
	}
	t = hemq;
	while (i > 1)
	{
		buffer_head *s = (buffer_head *)malloc(sizeof(buffer_head));
		s->bufNo = MAX_EMPTY_NUM - i + 1;
		s->bufPtr = 0;
		s->bufSize = MAX_EMPTY_NUM;
		s->bufState = EMPTY;
		s->next = NULL;
		t->next = s;

		if (i == 2)
			lemq = s;
		t = t->next;
		i--;
	}
}


//将numb号缓冲加入队列
bool add_buf(int type, int numb)	//返回false,要执行LRU置换
{
	if (type == INQ)
	{
		if(linq!=NULL && linq->bufSize==MAX_INQ_NUM){
			printf("输入缓冲队列已满，请进行LRU置换!");
			return false;
		}
		if (hinq == NULL)
		{ //开始空指针，初始化下
			buffer_head *newp = (buffer_head *)malloc(sizeof(buffer_head));
			newp->bufNo = numb;
			newp->bufPtr = 3;
			newp->bufSize = 1;
			newp->bufState = FULL;
			newp->next = NULL;
			hinq = newp;
			linq = hinq;
			return true;
		}
		//输入队列没装满,插入队尾
		if (linq != NULL && linq->bufSize < MAX_INQ_NUM)
		{ 
			buffer_head *newp = (buffer_head *)malloc(sizeof(buffer_head));
			newp->bufNo = numb;
			newp->bufPtr = 3;
			newp->bufSize = linq->bufSize + 1;
			newp->bufState = FULL;
			newp->next = NULL;
			linq->next = newp;
			linq = linq->next;
			return true;
		}
	}
	else if (type == OUTQ)
	{ //队列满了一次性写入(攒着，延迟写)
		if(loutq!=NULL && loutq->bufSize==MAX_OUTQ_NUM){
			printf("输出缓冲队列已满，请进行写回!");	//写回flush()
			return false;
		}
		if (houtq == NULL)
		{ //开始空指针，初始化下
			buffer_head *newp = (buffer_head *)malloc(sizeof(buffer_head));
			newp->bufNo = numb;
			newp->bufPtr = 3;
			newp->bufSize = 1;
			newp->bufState = FULL;
			newp->next = NULL;
			houtq = newp;
			loutq = houtq;
			return true;
		}
		if(loutq!=NULL && loutq->bufSize<MAX_OUTQ_NUM)
		{//没满，加到队尾
			buffer_head *newp = (buffer_head *)malloc(sizeof(buffer_head));
			newp->bufNo = numb;
			newp->bufPtr = 3;
			newp->bufSize = 1;
			newp->bufState = FULL;
			newp->next = NULL;
			loutq->next = newp;
			loutq = loutq->next;
			return true;
		}
	}
	else if (type == EMPQ)
	{ //归还缓冲区，数据清零
		buffer_head *newp = (buffer_head *)malloc(sizeof(buffer_head));
		newp->bufNo = numb;
		newp->bufPtr = 0;
		newp->bufSize = lemq->bufSize + 1;
		newp->bufState = EMPTY;
		newp->next = NULL;
		lemq->next = newp;
		lemq = lemq->next;
		return true;
	}
}

buffer_head *take_buf(int type) //收容，提取时缓冲区从队列中取出使用(取队头)
{
	if (type == INQ)
	{
		if(hinq==NULL){
			printf("输入缓冲队列已空！");
			return NULL;
		}
		buffer_head *h = hinq;
		hinq = hinq->next;
		linq->bufSize = linq->bufSize - 1;
		return h;
	}
	if (type == EMPQ)
	{
		if(hemq==NULL){
			printf("空闲缓冲队列已空！");
			return NULL;
		}
		buffer_head *h = hemq;
		hemq = hemq->next;
		lemq->bufSize = lemq->bufSize - 1;
		return h;
	}
	if (type == OUTQ)
	{
		if(houtq==NULL){
			printf("输出缓冲队列已空！");
			return NULL;
		}
		buffer_head *h = houtq;
		houtq = houtq->next;
		loutq->bufSize = loutq->bufSize - 1;
		return h;
	}
}

/*
void breada() //提前读
{
}

void brelse() //延时写
{
}
*/
void BufToDisk()
{
    buffer_head *sout = take_buf(OUTQ);
	//disk get write-back data
    write(sout->bufNo);

	add_buf(EMPQ, sout->bufNo);
	free(sout);
}

void DiskToBuf(int fileNum)
{
    buffer_head *hin = take_buf(EMPQ);
	//hin get disk data
    read( hin->bufNo, fileNum );

	bool b = add_buf(INQ, hin->bufNo);
	if(!b)
		inqLRU(hin->bufNo);
	free(hin);
}

void realse() //释放内存
{
	hemq->next = hinq;
	linq->next = houtq;
	buffer_head *tmp = hemq;
	while (tmp)
	{
		buffer_head *t = tmp;
		tmp = tmp->next;
		free(t);
	}
}


void inqLRU(int numb)
{
	if(!SearchAndLRU(Buf[numb].address)){
		buffer_head* b=take_buf(INQ);
		add_buf(EMPQ,b->bufNo);
		read(numb,readP[ReadyQueue->PID]);
		add_buf(INQ,numb);
	}
}

bool Search(int address)
{
	buffer_head* tmp=hinq;
	while(tmp){
		if(Buf[tmp->bufNo].address==address)
			return true;
		tmp=tmp->next;
	}
	return false;
}

//缓冲区寻找，并进行LRU替换，返回值是查询结果
bool SearchAndLRU(int address)
{
	buffer_head* father=hinq;
	if(hinq==NULL)
		return false;
	buffer_head* tmp=father->next;
	if(address==Buf[father->bufNo].address){
		linq->next=father;
		father->next=NULL;
		linq=linq->next;
		return true;
	}
	while(tmp){
		if(tmp->next==NULL)
			break;
		if(address!=Buf[tmp->bufNo].address){
			tmp=tmp->next;
			father=father->next;
			continue;
		}
		else break;
	}
	if(tmp==NULL && address!=Buf[father->bufNo].address)	//没找到
		return false;
	else if(address==Buf[tmp->bufNo].address){		//找到了并LRU
		linq->next=father;
		father->next=NULL;
		linq=linq->next;
		return true;
	}
	
}

