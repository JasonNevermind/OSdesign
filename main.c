#include<windows.h>
#include<conio.h>
#include"stdlib.h"
#include"buffpool.c"
#include"print.c"

int OS_TIME=0;

/*
    �涨��I/O��������Ҫ1s

    ʹ��˵��:
    
*/

void initialization()
{
    initFile();
    printf("��������Լ���...");
	getch();
	system("cls");

    initProcess();
    printf("��������Լ���...");
	getch();
	system("cls");

	initemq();

    rwUI();
    getch();
    printf("��������Լ���...");
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
                printf("�޷�ʶ��\n");
                break;
        }
        char c;
        printf("����鿴������Դ��(y/n)",&c);
        scanf(" %c",&c);
        if(c=='n')
            break;
    }
    printf("��������Լ���...");
    getch();
    system("cls");
}

void OS_main()
{
    initialization();
    while(1)
    {
        printf("-------------��ǰʱ��:%ds",OS_TIME);
        if( !ReadyQueue && !RunningQueue && !BlockQueue)
            break;


        char c;
        printf("��Ҫ�鿴ϵͳ��Դ��(y/n)");
        scanf(" %c",&c);
        if(c=='y'){
            OS_status();
        }

        getch();
        printf("��������Լ���...");
        OS_TIME++;
        system("cls");
    }
    printf("Brabo�����й��������꣡\n");
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
    //ģ�����һ�λ
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