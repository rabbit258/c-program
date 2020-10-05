#include<stdio.h>
#include"convince.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXTITLE 40
#define MAXAUTL 40
#define MAXBKS 100
char meun(void);
char choice(void);
char select(void);
void function(char choice1);
void showdata(void);
void resume(void);
void rewrite(void);
struct book {
	char title[MAXTITLE];
	char author[MAXAUTL];
	float value;
	char isdelete ;
}library[MAXBKS]={0},judge={0};
int count ;
int main(void)
{
	char choice1,choice3=0;
	FILE* pbooks;
	int size = sizeof(struct book);
	if ((pbooks = fopen("book.dat", "a+b")) == NULL)
	{
		fputs("error in opening file", stderr);
		exit(1);
	}
	while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
	{
		if (count == 0)
			puts("crrenct contents of book.dat:");
		printf("%d: %s by %s: $%.2f\n", count+1,library[count].title, library[count].author, library[count].value);
		count++;
	}
	fclose(pbooks);
	while ((choice1 = meun()) != 'q')
	{
			function(choice1);
			rewrite();
	}
}
char meun(void)
{
	char temp;
	printf("please enter the index of the option you want,q to quit\n"
		   "1)change data           2)delete data        3)add data\n");
	while ((temp = getchar() )!= '1' && temp != '2'&&temp!='3'&&temp!='q')
	{
		puts("please enter a vaild input");
		clear();
	}
	clear();
	return tolower(temp);
}
char choice(void)
{
	int temp;
	printf("please enter the order number you want to manipulate, to return upper level\n");
	while (((scanf("%d", &temp)) == 1 &&( temp<1 || temp>count + 1)))
	{
		puts("please enter a vaild order number");
		clear();
	}
	clear();
	return temp;
}
char select(void)
{
	char temp;
	printf("please enter the index of the target you want to change,q to return upper level\n"
		"1)title                              2)author                          3)prince\n");
	while ((temp = getchar()) != 'q' && (temp < '1' || temp>'3'))
	{
		puts("please enter a vaild order number");
		clear();
	}
	clear();
	return temp;
}
void function(char choice1)
{
	int choice2;
	char choice3;
	switch (choice1)
	{
	case '1':
		
		if (!count)
		{
			puts("no data could be changed");
			break;
		}
		    choice2 = choice();
			choice3 = select();

				puts("please enter a new data");

				switch (choice3)

				{

				case '1':
					s_gets(library[choice2 - 1].title, MAXTITLE);
					break;

				case '2':
					s_gets(library[choice2 - 1].author, MAXAUTL);
					break;

				case'3':
					scanf("%f", &library[choice2-1].value);
					clear();
				
			}
		
		break;

	case'2':
		if (!count)
		{
			puts("no data could be changed");
			break;
		}
		choice2 = choice();
		library[choice2 - 1].isdelete = 1;
		resume();
		break;

	case '3':
		choice2 = count;
		puts("please enter the title of the new book");
		s_gets(library[count ].title, MAXTITLE);
		puts("please enter the author of the new book");
		s_gets(library[count ].author, MAXAUTL);
		puts("now prince");
		scanf("%f", &library[count++ ].value);
		clear();
		break;
	}
	showdata();
}
void showdata(void)
{
	if (count)
		for (int index = 0;index < count;index++)
			printf("%d: % s by % s: $%.2f\n", index + 1, library[index].title, library[index].author, library[index].value);
	else
		puts("no data");
}
void resume(void)
{
	int index,i=count;
	struct book temp[10];
	for (index = count = 0;index < i; index++)
	{
		if (!library[index].isdelete)
			temp[count++] = library[index];
		library[index] = judge;
	}
	for (index = 0;index < i;index++)
		library[index] = temp[index];
}
void rewrite(void)
{
	FILE* ftp;
	if ((ftp = fopen("book.dat", "w+b")) == NULL)
	{
		fputs("error in opening file", stderr);
		exit(1);
	}
	fwrite(&library[0], sizeof(struct book), count , ftp);
	fclose(ftp);
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
