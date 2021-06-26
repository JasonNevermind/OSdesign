#include<windows.h>
#include<conio.h>
#include"stdlib.h"
#include"buffpool.c"
#include"print.c"

int OS_TIME=0;

/*
    规定：I/O操作均需要1s

    使用说明:
    
*/

void initialization()
{
    initFile();
    printf("按任意键以继续...");
	getch();
	system("cls");

    initProcess();
    printf("按任意键以继续...");
	getch();
	system("cls");

	initemq();

    rwUI();
    getch();
    printf("按任意键以继续...");
    system("cls");
}

void OS_status()
{
    while(1){
        int choice;
        viewUI();
        scanf("&d",&choice);
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
            default:
                printf("无法识别\n");
                break;
        }
        char c;
        printf("还想查看其他资源吗？(y/n)",&c);
        scanf(" %c",&c);
        if(c=='n')
            break;
    }
    printf("按任意键以继续...");
    getch();
    system("cls");
}

void OS_main()
{
    initialization();
    while(1)
    {
        printf("-------------当前时间:%ds",OS_TIME);
        if( !ReadyQueue && !RunningQueue && !BlockQueue)
            break;


        char c;
        printf("想要查看系统资源吗？(y/n)");
        scanf(" %c",&c);
        if(c=='y'){
            OS_status();
        }

        getch();
        printf("按任意键以继续...");
        OS_TIME++;
        system("cls");
    }
    printf("Brabo！所有工作已做完！\n");
}


int main()
{
/*
	initFile();
	printFile();

	getch();
	system("cls");

    printBlocks();
    getch();
    system("cls");

    initProcess();
	printProcess();

	getch();
	system("cls");

	initemq();
*/
    initialization();
    //模拟进程一次活动
    /*
    if(OS_TIME<RunningQueue->Rtime+RunningQueue->time)
    {
        if(RunningQueue->mod=='r'){
            readfile(readP[RunningQueue->PID]);
        }
        else if(RunningQueue->mod=='w'){
            writefile(readP[RunningQueue->PID]);
        }
    }
	*/
/*
    toRunning();

	readfile(readP[0]);
    printBuffPool();
    getch();
	system("cls");
*/
    toRunning();
    writefile(readP[0]);

	printBuffPool();
    printBlocks();
    printFile();
    
    getch();
	system("cls");

    printBlocks();
    getch();
	system("cls");


    printBlocks();

	return 0;
}