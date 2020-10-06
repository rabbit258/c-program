#include<stdio.h>
#include"convince.h"
#include<string.h>
#include<stdlib.h>
struct i {
	int num;
	int judge;
	char surname[20];
	char lastname[20];
}flight[4][12], temp[4][12];
char plane[4][4] = { "102","311","444","519" };
int iswrite[4];
void dataload(void);
int function(void);
char menu2(int);
void showcur(int index);
void function1(int judge);
void function2(int judge);
void function3(int judge);
void function4(int judge);
void function5(int judge);
void function6(int judge);
void write(void);
int main(void)
{
	int index;
	char judge2;
	dataload();
	while ((index = function()) != 'q')
	{
		while ((judge2 = menu2(index)) != 'g')
			switch (judge2)
			{
				
			case'a':
				function1(index);
				break;
			case'b':
				function2(index);
				break;
			case'c':
				function3(index);
				break;
			case'd':
				function4(index);
				break;
			case'e':
				function5(index);
				break;
			case'f':
				function6(index);
				write();
				break;
			default:
				puts("error input please try again");
			}
		
	}
	puts("bye!");
	return 0;
}
void dataload(void)
{
	int index1, index2;
	FILE* ftp;
	if ((ftp = fopen("flight.bat", "a+b")) == NULL)
	{
		puts("error in opening flie");
		exit(1);
	}
	fread(flight, sizeof(flight), 1, ftp);
	for (index1 = 0;index1 < 4;index1++)
	{
		int i = 1;
		for (index2 = 0;index2 < 12;index2++, i++)
		{
			flight[index1][index2].num = i;
			temp[index1][index2] = flight[index1][index2];
	    }
	}
}
int function(void)
{
	int index;
	char temp[4];
	while (1)
	{
		puts("please enter the flight you want to manipulate,q to quit");
		puts("available flight num:102,311,444,519");
		s_gets(temp, 4);
		if (!strcmp(temp, "q"))
				return 'q';
		for (index = 0;index < 4;index++)
		   if (!strcmp(temp, plane[index]))
			return index;
		puts("please enter a vaild flight num or q");
	}
}
char menu2(int index)
{
	char judge;
	showcur(index);
	puts("please select the function you want");
	printf(
		"a) show numer of empty seats\n"
		"b) show list of empty seats\n"
		"c) show alphabetical list of seats\n"
		"d) assign a customer to a seat assignment\n"
		"e) delete a seat assignment\n"
		"f) confirm current situation of seats\n"
		"g) quit\n");
	while ((judge = getchar()) < 'a' || judge > 'g')
	{
		puts("error input!please enter again");
		clear();
	}
	clear();
	return judge;
}
void showcur(int index)
{
	printf("the current manipulated flight:%s\n", plane[index]);
}
void function1(int judge)
{
	int count, index = 0;
	for (count = 0;count < 12;count++)
		if (!flight[judge][count].judge)
			index++;
	if (index)
		printf("well ,the number of vaccant %s is %d\n", index == 1 ? "seat" : "seats", index);
	else
		puts("no availble seat");
}
void function2(int judge)
{
	int temp[12], count, index;
	for (count = index = 0;count < 12;count++)
		if (!flight[judge][count].judge)
			temp[index++] = flight[judge][count].num;
	if (index)
	{
		printf("here is the list of vacant %s\n", index == 1 ? "seat" : "seats");
		for (count = 0;count < index;count++)
			printf(" %d", temp[count]);
		puts("");
	}
	else
		puts("no availble seat");
}
void function3(int judge)
{
	int index;
	puts("here is the list of seats sorted by order number");
	for (index = 0;index < 12;index++)
		if (flight[judge][index].judge)
			printf("seat %d is reserved by %s %s\n", flight[judge][index].num, flight[judge][index].surname, flight[judge][index].lastname);
		else
			printf("seat %d is availble\n", flight[judge][index].num);
}
void function4(int judge)
{
	int number;
	iswrite[judge] = 0;
		puts("please enter the order number of the seat you want to reserve");
		if((scanf("%d", &number)) != 1 || number < 0 || number>12)
		{
			puts("please enter a vaild order number,try again");
			clear();
			goto end;
		}
		number--;
		if (flight[judge][number].judge)
		{
			puts("this seat has been reserved");
			goto end;
		}
		clear();
		puts("please enter the surname of reserver");
		s_gets(flight[judge][number].surname, 20);
		puts("last name please");
		s_gets(flight[judge][number].lastname, 20);
		puts("the reservation is confrimed");
		flight[judge][number].judge = 1;
	end:;
}
void function5(int judge)
{
	int number;
	iswrite[judge] = 0;
	puts("please enter the number of the seat you want to cancel reservation");
	if ((scanf("%d", &number)) != 1 || number < 0 || number>12)
	{
		puts("please enter a vaild order number,try again");
		clear();
		goto end;
	}
	clear();
	number--;
	if(!flight[judge][number].judge)
	{
		puts("this seat is not reserved actually");
		goto end;
	}
	flight[judge][number].judge = 0;
	strcpy(flight[judge][number].surname, "");
	strcpy(flight[judge][number].lastname, "");
	puts("request confirmed");
 end:;
}
void function6(int judge)
{
	puts("this function will save all the action have been done in the flight");
	iswrite[judge] = 1;
}
void write(void)
{
	FILE* ftp;
	if ((ftp = fopen("flight.bat", "w+b")) == NULL)
	{
		puts("error in opening file");
		exit(1);
	}
	int index;
	for (index = 0;index < 4;index++)
		if (iswrite[index])
			fwrite(&flight[index], sizeof(struct i), 12, ftp);
		else
			fwrite(&temp[index], sizeof(struct i), 12, ftp);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
