#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include "Console.h"

#define MAX 8
#define BACKCOLOR 15
#define Speed 90

int g_iScore = 0;
int heart = 3;
struct ST_OBJECT
{
	int x = 0;
	int y = 0;
	bool bActive = false;
};

ST_OBJECT g_stEnemy_UP[MAX];
ST_OBJECT g_stEnemy_Down[MAX];
ST_OBJECT g_stEnemy_Left[MAX];
ST_OBJECT g_stEnemy_Right[MAX];
ST_OBJECT g_stPlayer;

//별 생성
void Spwn()
{
	//위
	for (int i = 0; i < MAX; i++)
	{
		if (!g_stEnemy_UP[i].bActive)
		{
			g_stEnemy_UP[i].x = (rand() % 30) * 2;
			g_stEnemy_UP[i].y = 0;
			g_stEnemy_UP[i].bActive = true;
			break;
		}
	}
	//아래
	for (int i = 0; i < MAX; i++)
	{
		if (!g_stEnemy_Down[i].bActive)
		{
			g_stEnemy_Down[i].x = (rand() % 30) * 2;
			g_stEnemy_Down[i].y = 30;
			g_stEnemy_Down[i].bActive = true;
			break;
		}
	}
	//왼쪽
	for (int i = 0; i < MAX; i++)
	{
		if (!g_stEnemy_Left[i].bActive)
		{
			g_stEnemy_Left[i].y = (rand() % 15) * 2;
			g_stEnemy_Left[i].x = 0;
			g_stEnemy_Left[i].bActive = true;
			break;
		}
	}
	//오른쪽
	for (int i = 0; i < MAX; i++)
	{
		if (!g_stEnemy_Right[i].bActive)
		{
			g_stEnemy_Right[i].y = (rand() % 15) * 2;
			g_stEnemy_Right[i].x = 60;
			g_stEnemy_Right[i].bActive = true;
			break;
		}
	}
}

//별 처리
int EnemyProcess()
{
	int count = 0;
	for (int i = 0; i < MAX; i++)
	{
		//위
		if (g_stEnemy_UP[i].bActive)
		{
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy_UP[i].x, g_stEnemy_UP[i].y);
			printf("★");
			g_stEnemy_UP[i].y++;

			if (g_stEnemy_UP[i].y == g_stPlayer.y)
			{
				if (g_stEnemy_UP[i].x == g_stPlayer.x)
				{
					heart--;
					if (heart == 0) g_stPlayer.bActive = false;
				}
			}
			if ((g_stEnemy_UP[i].y > 30) || (g_stEnemy_UP[i].y < 0) || (g_stEnemy_UP[i].x > 60) || (g_stEnemy_UP[i].x < 0))
			{
				g_stEnemy_UP[i].bActive = false;
			}
		}
		//아래
		if (g_stEnemy_Down[i].bActive)
		{
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy_Down[i].x, g_stEnemy_Down[i].y);
			printf("★");
			g_stEnemy_Down[i].y--;

			if (g_stEnemy_Down[i].y == g_stPlayer.y)
			{
				if (g_stEnemy_Down[i].x == g_stPlayer.x)
				{
					heart--;
					if (heart == 0) g_stPlayer.bActive = false;
				}
			}
			if ((g_stEnemy_Down[i].y > 30) || (g_stEnemy_Down[i].y < 0) || (g_stEnemy_Down[i].x > 60) || (g_stEnemy_Down[i].x < 0))
			{
				g_stEnemy_Down[i].bActive = false;
			}
		}
		//왼쪽
		if (g_stEnemy_Left[i].bActive)
		{
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy_Left[i].x, g_stEnemy_Left[i].y);
			printf("★");
			g_stEnemy_Left[i].x += 2;

			if (g_stEnemy_Left[i].x == g_stPlayer.x)
			{
				if (g_stEnemy_Left[i].y == g_stPlayer.y)
				{
					heart--;
					if (heart == 0) g_stPlayer.bActive = false;
				}
			}
			if ((g_stEnemy_Left[i].y > 30) || (g_stEnemy_Left[i].y < 0) || (g_stEnemy_Left[i].x > 60) || (g_stEnemy_Left[i].x < 0))
			{
				g_stEnemy_Left[i].bActive = false;
			}
		}
		//오른쪽
		if (g_stEnemy_Right[i].bActive)
		{
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy_Right[i].x, g_stEnemy_Right[i].y);
			printf("★");
			g_stEnemy_Right[i].x -= 2;

			if (g_stEnemy_Right[i].x == g_stPlayer.x)
			{
				if (g_stEnemy_Right[i].y == g_stPlayer.y)
				{
					heart--;
					if (heart == 0) g_stPlayer.bActive = false;
				}
			}
			if ((g_stEnemy_Right[i].y > 30) || (g_stEnemy_Right[i].y < 0) || (g_stEnemy_Right[i].x > 60) || (g_stEnemy_Right[i].x < 0))
			{
				g_stEnemy_Right[i].bActive = false;
			}
		}
	}
	return count;
}

//input 처리
void Inputprocess()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_stPlayer.x -= 2;
		if (g_stPlayer.x < 0)g_stPlayer.x = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_stPlayer.x += 2;
		if (g_stPlayer.x > 60)g_stPlayer.x = 60;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		g_stPlayer.y -= 1;
		if (g_stPlayer.y < 0)g_stPlayer.y = 0;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		g_stPlayer.y += 1;
		if (g_stPlayer.y > 30)g_stPlayer.y = 30;
	}
}

//player 출력
void ReanderPlayer()
{
	SetColor(BACKCOLOR, 0);
	if (g_stPlayer.bActive)
	{
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("▲");
	}
	else
	{
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("△");
	}
}

//콘솔
void Init()
{
	g_stPlayer.x = 14;
	g_stPlayer.y = 28;
	g_stPlayer.bActive = true;

	srand(time(NULL));
	SetConsoleSize(60, 30);

	//SetTitle("별피하기");
	SetColor(BACKCOLOR, 0);
}

//스코어
void Score(void)
{
	if (g_stPlayer.bActive) g_iScore++;
	GotoXY(0, 0);
	printf("Score : %d", g_iScore);
	if (g_iScore < 150) {
		GotoXY(0, 1);
		SetColor(BACKCOLOR, 10);
		printf("1단계");
	}
	if (g_iScore >= 150 && g_iScore < 250) {
		GotoXY(0, 1);
		SetColor(BACKCOLOR, 11);
		printf("2단계");
	}
	if (g_iScore >= 250 && g_iScore < 400) {
		GotoXY(0, 1);
		SetColor(BACKCOLOR, 12);
		printf("3단계");
	}
	if (g_iScore >= 400) {
		GotoXY(0, 1);
		SetColor(BACKCOLOR, 13);
		printf("4단계");
	}

	if (heart == 3)
	{
		SetColor(BACKCOLOR, 12);
		GotoXY(0, 2);
		printf("♥ ♥ ♥");
	}
	if (heart == 2)
	{
		SetColor(BACKCOLOR, 12);
		GotoXY(0, 2);
		printf("♥ ♥ ♡");
	}
	if (heart == 1)
	{
		SetColor(BACKCOLOR, 12);
		GotoXY(0, 2);
		printf("♥ ♡ ♡");
	}
}

//시작 메뉴
void StartMenu()
{

	while (1)
	{
		Clear();
		GotoXY(10, 9);
		printf("별 피하기");
		GotoXY(10, 20);
		printf("Press any key ...");

		if (_kbhit()) break;
		Sleep(50);
	}
}

//별 속도
void GameSpeed()
{
	if (g_iScore < 150) {

		Sleep(Speed);
	}
	if (g_iScore >= 150 && g_iScore < 250) {
		Sleep(Speed - 30);
	}
	if (g_iScore >= 250 && g_iScore < 400) {
		Sleep(Speed - 50);
	}
	if (g_iScore >= 400) {
		Sleep(Speed - 70);
	}
}

//게임진행
void GameMain()
{
	g_stPlayer.x = 28;
	g_stPlayer.y = 14;
	g_stPlayer.bActive = true;
	g_iScore = 0;
	int state = 0;
	while (1)
	{
		Clear();
		if (g_stPlayer.bActive)
		{
			Spwn();
			Inputprocess();
		}
		state = EnemyProcess();

		ReanderPlayer();
		Score();
		GameSpeed();
		if (state == 0) break;
	}
}

//결과창
bool ResultMenu()
{
	bool bRet = false;
	while (1)
	{
		Clear();
		SetColor(BACKCOLOR, 0);
		GotoXY(25, 9);
		printf("Result Menu");
		GotoXY(25, 15);
		printf("Score : %d", g_iScore);

		GotoXY(23, 20);
		printf("Continue ... Y/N");
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			bRet = false;
			heart = 3;
			break;
		}
		if (GetAsyncKeyState('N') & 0x8000)
		{
			bRet = true;
			break;
		}
		Sleep(50);
	}
	return bRet;
}

int main()
{
	Init();

	while (1)
	{
		StartMenu();
		GameMain();
		if (ResultMenu()) break;
	}
	system("pause");
	return 0;
}