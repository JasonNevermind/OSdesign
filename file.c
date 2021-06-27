
#include"file.h"

//文件初始化
void initFile()
{
    for(int i=0;i<MAX_FILE_NUM;i++){
        file[i].FileId=i;
        printf("请输入文件%d起始地址，内容(4 int):",i);
        scanf("%d",&file[i].FileAddr);
        for(int j=0;j<4;j++){
            scanf("%d",&file[i].FileText[j]);
        }
    }
}

void initFile1()
{
    for(int i=0;i<MAX_FILE_NUM;i++){
        file[i].FileId=i;
        file[i].FileAddr=rand()%300;
        for(int j=0;j<4;j++){
            file[i].FileText[j]=rand()%10;
        }
    }
    flushBlock();
}

void flushFile()
{
    for(int i=0;i<MAX_FILE_NUM;i++){
        for(int j=0;j<4;j++){
            file[i].FileText[j]=disks[file[i].FileAddr+j];
        }
    }
}

void flushBlock()
{
    for(int i=0;i<MAX_FILE_NUM;i++){
        for(int j=0;j<4;j++){
            disks[file[i].FileAddr+j]=file[i].FileText[j];
        }
    }
}
