#include<stdio.h>
#include<string.h>
#include<ctype.h>
char * s_gets(char* phrase, int limit)
{
	char * temp;
	char * find;
	temp = fgets(phrase, limit, stdin);
	if (temp)
	{
		find = strchr(phrase, '\n');
		if (find)
			*find = '\0';
		else while (getchar() != '\n');
		
	}

	return temp;
}
void clear(void)
{
	while (getchar() != '\n');
}
int mod(int get, int rod)
{
	int index,total;
	for (index = total = 1;index <= rod;index++)
		total *= get;
	return total;
}
int transfer(char* get)
{
	int length = strlen(get)-1,total,index;
	for (total = index = 0;length >= 0;length--)
		total += (get[index]-48) * mod(10, length);
	return total;
}