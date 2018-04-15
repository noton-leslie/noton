#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
using namespace std;

struct node
{
	int col, row;
}zero[81];

int outarr[9][9];
int shuduku[9][9];
int A33[6][3] = { { 0,1,2 },{ 0,2,1 },{ 1,0,2 },{ 1,2,0 },{ 2,1,0 },{ 2,0,1 } };
int seedshuduku[9][9] =
{ 
{ '3','9','4','5','7','1','6','2','8' },
{ '2','6','8','4','3','9','7','5','1' },
{ '7','5','1','8','6','2','3','9','4' },
{ '5','8','3','1','2','6','9','4','7' },
{ '9','4','7','3','5','8','1','6','2' },
{ '6','1','2','7','9','4','8','3','5' },
{ '1','3','5','9','4','7','2','8','6' },
{ '4','7','6','2','8','3','5','1','9' },
{ '8','2','9','6','1','5','4','7','3' },
};

FILE *a;
FILE *b;
int cout = 0;
int flag = 0;
int n = 0;
int shudukuIsOk = 0;
int boder = 0;

void Exechage(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void OutBreak()
{
	//	fprintf(a, "%d\n", cout+1);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j <8)
			{
				fputc(outarr[i][j] , a);
				fputc(' ', a);
			}
			else
			{
				fputc(outarr[i][j], a);
				fputc('\n', a);
			}
		}
	}
	cout++;
	if (cout<n)
	{
		fputc('\n', a);
	}
	else
	{
		flag = 1;
	}
}

void Ex(int a, int b, int c, int cur)
{
	for (int i = 0; i < 9; i++)
	{
		outarr[cur][i] = seedshuduku[a + cur][i];
		outarr[cur + 1][i] = seedshuduku[b + cur][i];
		outarr[cur + 2][i] = seedshuduku[c + cur][i];
	}
}
int juge(int col, int row)
{
	int temp[10];
	int row9 = row / 3 * 3;
	int col9 = col / 3 * 3;
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<9; i++)
	{
		temp[shuduku[col][i]]++;
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<9; i++)
	{
		temp[shuduku[i][row]]++;
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			temp[shuduku[i + col9][j + row9]]++;
		}
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	return 1;
}
void Soluve(int x)
{
	if (x >= boder)
	{
		shudukuIsOk = 1;
		return;
	}
	for (int i = 1; i <= 9 && !shudukuIsOk; i++)
	{
		shuduku[zero[x].col][zero[x].row] = i;
		if (juge(zero[x].col, zero[x].row))
		{
			Soluve(x + 1);
		}
	}
}
int seedarr[8] = { '1','2','4','5','6','7','8','9', };
int startads = 7, curads = 0, changeads;
void caozuo1(int i,int j)
{
	seedshuduku[i][j] = '3';
	outarr[i][j] = '3';
}
void caozuo2(int i,int j,int temp)
{
	seedshuduku[i][j] = seedarr[temp - 2];
	outarr[i][j] = seedarr[temp - 2];
}
void caozuo3(int i,int j,int temp)
{
	seedshuduku[i][j] = seedarr[temp - 1];
	outarr[i][j] = seedarr[temp - 1];
}

int main(int argc,char* argv[])
{
	if (strcmp(argv[1], "-c") == 0)
	{
		int len = strlen(argv[2]);
		a = fopen("shuduku.txt", "w");
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i] >= '0'&&argv[2][i] <= '9')
				continue;
			else return 0;
		}
		for (int i = 0; i < len; i++)
		{
			n *= 10;
			n += argv[2][i] - '0';
		}
		while (startads != 0 && !flag)
		{
			curads = startads;
			startads--;
			if (seedarr[curads] >seedarr[startads])
			{
				changeads = 7;
				while (seedarr[startads] >= seedarr[changeads])
					changeads--;
				Exechage(seedarr[startads], seedarr[changeads]);
				for (int i = startads + 1, j = 7; i < j; i++, j--)
				{
					Exechage(seedarr[i], seedarr[j]);
				}
				startads = 7;
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						int temp = seedshuduku[i][j]-'0';
						if (temp == 3)
						{
							caozuo1(i,j);
							continue;
						}
						else if (temp>3)
						{
							caozuo2(i,j,temp);
						}
						else
						{
							caozuo3(i,j,temp);
						}
					}
				}
				for (int i = 0; i < 6 && !flag; i++)
				{
					Ex(A33[i][0], A33[i][1], A33[i][2], 3);
					for (int j = 0; j < 6 && !flag; j++)
					{
						Ex(A33[j][0], A33[j][1], A33[j][2], 6);
						OutBreak();
					}
				}
			}
			if (startads == 0 && !flag)
				break;
		}
		fclose(a);
		return 0;
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		a = fopen("shuduku.txt", "w");
		b = fopen(argv[2], "r");
		int temp;
		int num = 0, t = 0;
		while (~fscanf(b, "%d", &temp))
		{
			int y = num % 9;
			int x = num / 9;
			num++;
			shuduku[x][y] = temp;
			if (temp == 0)
			{
				zero[boder].col = x;
				zero[boder].row = y;
				boder++;
			}
			if (num == 81)
			{
				num = 0;
				Soluve(0);
				boder = 0;
				shudukuIsOk = 0;
				if (t != 0)
				{
					fprintf(a, "\n");
				}
				t++;
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (j <8)
						{
							fprintf(a, "%d ", shuduku[i][j]);
						}
						else
						{
							fprintf(a, "%d\n", shuduku[i][j]);
						}
					}
				}
			}
		}
		fclose(a);
		fclose(b);
		return 0;
	}
}
