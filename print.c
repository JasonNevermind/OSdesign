
#include"print.h"

void printBlocks()
{
    printf("------?????????------\n???? ");

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
}
void printFile(struct File f[],int num)
{
    for(int i=0;i<num;i++){
        printf("fileId:%d   fileAddress:%d      \n",f[i].FileId,f[i].FileAddr);
        
    }
}
void printBuffPool()
{
    buffer_head *tmp = hinq;
	printf("??????\t????\t?????\t??????\t\n");
	while (tmp)
	{
		printf("inq\t\t%d\t\t%d\t\t\t%d\t\t\n", tmp->bufNo, tmp->bufState, linq->bufSize);
		tmp = tmp->next;
	}
    tmp=houtq;
    while (tmp)
    {
        printf("outq\t\t%d\t\t%d\t\t\t%d\t\t\n",tmp->bufNo,tmp->bufState, loutq->bufSize);
        tmp=tmp->next;
    }
    tmp=hemq;
    while (tmp)
    {
        printf("emq\t\t%d\t\t%d\t\t\t%d\t\t\n",tmp->bufNo,tmp->bufState, lemq->bufSize);
        tmp=tmp->next;
    }
}

void printInq()
{
    buffer_head *tmp = hinq;
	printf("??????\t????\t?????\t??????\t\n");
	while (tmp)
	{
		printf("inq\t\t%d\t\t%d\t\t\t%d\t\t\n", tmp->bufNo, tmp->bufState, linq->bufSize);
		tmp = tmp->next;
	}
}

void printOutq()
{
    buffer_head *tmp = houtq;
	printf("??????\t????\t?????\t??????\t\n");
	while (tmp)
	{
		printf("outq\t\t%d\t\t%d\t\t\t%d\t\t\n", tmp->bufNo, tmp->bufState, loutq->bufSize);
		tmp = tmp->next;
	}
}

void printEmq()
{
    buffer_head *tmp = hemq;
	printf("??????\t????\t?????\t??????\t\n");
	while (tmp)
	{
		printf("emq\t\t%d\t\t%d\t\t\t%d\t\t\n", tmp->bufNo, tmp->bufState, lemq->bufSize);
		tmp = tmp->next;
	}
}