#include "SDL.h"
#include<iostream>
#include <math.h>
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")
using namespace std;

void Init();
void Input();
void Render();
void Tick();
void Term();
SDL_Window* MyWindow;
SDL_Renderer* MyRenderer;
SDL_Event MyEvent;
bool IsRunning;

int SDL_main(int argc, char* argv[])
{
	Init();
	while (IsRunning) // 처리를 해줘야해 프레임마다 다했냐? 물어봐줌 -> 폴링 이라고 한다.
	{
		Input();
		Tick();
		Render();

	}
	Term();







	/*char Chess[50][50] = { 0, };

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		string k;
		cin >> k;
		for (int j = 0; j < M; j++)
		{
			Chess[i][j] = k[j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (i != N - 1)
		{
			if (Chess[i][0] == Chess[i + 1][0])
			{
				if (Chess[i + 1][0] == 'B')
				{
					Chess[i + 1][0] = 'W';
				}
				else
				{
					Chess[i + 1][0] = 'B';
				}
			}
		}



		for (int j = 0; j < M - 1; j++)
		{
			if (Chess[i][j] == Chess[i][j + 1])
			{
				if (Chess[i][j + 1] == 'B')
				{
					Chess[i][j + 1] = 'W';
				}
				else
				{
					Chess[i][j + 1] = 'B';
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{

		for (int j = 0; j < M; j++)
		{
			cout << Chess[i][j] << " ";
		}
		cout << endl;
	}*/


	return 0;


}

void Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Init error" << endl;
		return;
	}

	MyWindow = SDL_CreateWindow("Simple GameEngine", 100, 100, 640, 480, SDL_WINDOW_OPENGL);

	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	// -1넣으면 하나만 씀 ? 이러한 기능들을 만들어서 나에게 제어권을 줘
	IsRunning = true;
}

void Input()
{
	SDL_PollEvent(&MyEvent);
}

void Render()
{
	int R = rand() % 256;
	int G = rand() % 256;
	int B = rand() % 256;



	SDL_SetRenderDrawColor(MyRenderer, 0, 0, 0, 0);
	SDL_RenderClear(MyRenderer);

	SDL_SetRenderDrawColor(MyRenderer, R, G, B, 0);
	SDL_Rect MyRect;
	MyRect.x = rand() % 640;
	MyRect.y = rand() % 480;
	MyRect.w = rand() % 640;
	MyRect.h = rand() % 480;
	//SDL_RenderFillRect(MyRenderer, &MyRect);

	//원 그리기
	int X1 = 0;
	int Y1 = 0; 
	int X2 = 0;
	int Y2 = 0;

	int CenterOfCircleX = 320;
	int CenterOfCircleY = 240;
	int Radius = 110;

	for (int Size = 0; Size < Radius; ++Size)
	{
		for (int Angle = 0; Angle < 360; ++Angle)
		{
			X1 = static_cast<int>(SDL_sin(3.14f * 180 * Angle) * Size);
			Y1 = static_cast<int>(SDL_cos(3.14f * 180 * Angle) * Size);
			X2 = static_cast<int>(SDL_sin(3.14f * 180 * Angle + 1) * Size);
			Y2 = static_cast<int>(SDL_cos(3.14f * 180 * Angle + 1) * Size);

			SDL_RenderDrawLine(MyRenderer, X1+ CenterOfCircleX, Y1+ CenterOfCircleY, X2+ CenterOfCircleX, Y2+ CenterOfCircleY);
		}
	}




	
	
	//sin(θ) = y / d == y = sin(θ) * d
	//cos(θ) = x / d == x = cos(θ) * d
	SDL_RenderPresent(MyRenderer);
}

void Tick()
{
	switch (MyEvent.type)
	{
	case SDL_QUIT:
		IsRunning = false;
		break;
	case SDL_WINDOWEVENT:
		cout << "Event" << endl;
		break;
	case SDL_MOUSEBUTTONDOWN:
		cout << "Click" << endl;
		break;
	case SDL_KEYDOWN:
		switch (MyEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			IsRunning = false;
			break;
		}
	}
}

void Term()
{
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);

	SDL_Quit();
}
