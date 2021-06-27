#include<windows.h>
#include<conio.h>
#include"stdlib.h"
#include"buffpool.c"
#include"print.c"

int OS_TIME=0;
int runP_TIME=0;
int initmod=0;
char tmod;




/*
    规定：I/O操作均需要1s

    使用说明:
    
*/

void OS_status();

void menu()
{
    printf("---面向磁盘文件系统的磁盘高速缓存系统---\n");
    printf("---初始化选项:                     ---\n");
    printf("---1)自动产生                      ---\n");
    printf("---2)手动输入                      ---\n");
    printf("---时间流逝方式:                    ---\n");
    printf("---a)按键                           ---\n");
    printf("---b)WM_TIMER自动流逝               ---\n");
    printf("---请选择您想要的方式(示例：1 a)     ---\n");
    printf("---请输入:");
    scanf("%d %c",&initmod,&tmod);
    system("cls");
}

void initialization()
{
    initFile();
    flushBlock();
    printf("\n按任意键以继续...");
	getch();
	system("cls");

    initProcess();
    sortPQue();
    printf("\n按任意键以继续...");
	getch();
	system("cls");

	initemq();

    rwUI();
    printf("\n按任意键以继续...");
    getch();
    system("cls");
}

void initialization1()
{
    printf("随机生成中...\n");
    initFile1();
    initProcess1();
    initemq();
    rwUI1();
    sortPQue();
    printf("随机生成成功！\n");
    printf("是否要查看生成的项目？(y/n)");
    char c;
    scanf("%c",&c);
    if(c=='y'){
        OS_status();
    }
    system("cls");
}

void OS_status()
{
    printf("-------------当前时间:%ds(暂停)\n",OS_TIME);
    while(1){
        int choice;
        viewUI();
        printf("输入编号以继续...");
        scanf("%d",&choice);
        system("cls");
        switch (choice)
        {
            case 1:
                printProcess();
                break;
            case 2:
                printFile();
                break;
            case 3:
                printBuffPool();
                break;
            case 4:
                printBlocks();
                break;
            case 5:
                printFileToP();
            default:
                printf("无法识别\n");
                break;
        }
        printf("\n");
        
        char c;
        printf("还想查看其他资源吗？(y/n)",&c);
        printf("输入编号以继续...");
        scanf(" %c",&c);
        system("cls");
        if(c=='n')
            break;
    }
    printf("\n按任意键以继续...");
    getch();
    system("cls");
}

void OS_main()
{
    initialization();
    while(1)
    {
        printf("-------------当前时间:%ds(运行)\n",OS_TIME);
        if( !ReadyQueue && !RunningQueue && !BlockQueue)
            break;
        //判断当前时间是否有阻塞-->就绪的进程


        if(BlockQueue && BlockQueue->mod=='r'){        //有阻塞,每一秒执行一次IO(读进程)
            DiskToBuf(readP[BlockQueue->PID]);

            if(Search(file[readP[BlockQueue->PID]].FileAddr)){
                printf("阻塞进程%d已进入就绪！\n",BlockQueue->PID);
                toReady();
            }
        }

        if(!RunningQueue){
            if(OS_TIME>=ReadyQueue->Rtime){
                
                if(!Search(file[readP[ReadyQueue->PID]].FileAddr) && ReadyQueue->mod=='r'){    //没找到
                    toBlock();
                    printf("当前已阻塞进程ID%d！\n",lBlock->PID);
                }
                else{
                    toRunning();
                    if(RunningQueue->mod=='w')
                        ProToBuf();
                    runP_TIME=OS_TIME;
                    printf("当前开始运行进程ID%d！\n",RunningQueue->PID);
                }
            }
            else{
                printf("当前未有进程到达...\n");
            }
        }
        else{
            if(ReadyQueue && !Search(file[readP[ReadyQueue->PID]].FileAddr) && ReadyQueue->mod=='r'){    //没找到
                toBlock();
                printf("当前已阻塞进程ID%d！\n",lBlock->PID);
            }
            

            if(OS_TIME >= RunningQueue->time+runP_TIME ){

                if(RunningQueue->mod=='r'){

                    BufToPro();

                    printf("进程%d读到的内容是：",RunningQueue->PID);
                    for(int i=0;i<4;i++){
                        printf("%d ",RunningQueue->content[i]);
                    }
                    printf("\n");
                    free(RunningQueue);
                    RunningQueue=NULL;
                }
                else if(RunningQueue->mod=='w'){
                    printf("进程ID%d写入磁盘，请查看磁盘及文件资源！\n",RunningQueue->PID);
                    BufToDisk();
                    //file context has changed
                    flushFile();
                    free(RunningQueue);
                    RunningQueue=NULL;
                }
            }
            else    printf("当前运行进程ID%d\n",RunningQueue->PID);
        }
        printProcess();
        char c;
        printf("想要查看更多系统资源吗？(y/n)");
        scanf(" %c",&c);
        if(c=='y'){
            system("cls");
            OS_status();
        }

        printf("按任意键以继续...");
        getch();
        OS_TIME++;
        system("cls");
    }
    printf("Brabo！所有工作已做完！\n");
    getch();
}


int main()
{
    //OS_main();
	initialization1();
    return 0;
}