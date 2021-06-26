
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

/*
    int main()
{

    initFile();
    printFile();
    return 0;
}

*/
