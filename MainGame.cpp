#include "MainGame.h"
#include "macroFunction.h"
#include "Image.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "Construction.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SoundManager::GetSingleton()->AddSound("스테이지", "Sound/BattleCityStage.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("게임오버", "Sound/BattleCityGameOver.mp3", false, false);

	stage1 = new LoadingScene;
	SceneManager::GetSingleton()->AddLoadScene("로딩1", stage1);

	stage2 = new LoadingScene;
	SceneManager::GetSingleton()->AddLoadScene("로딩2", stage2);

	stage3 = new LoadingScene;
	SceneManager::GetSingleton()->AddLoadScene("로딩3", stage3);

	stage4 = new LoadingScene;
	SceneManager::GetSingleton()->AddLoadScene("로딩4", stage4);
	
	battleScene = new BattleScene;
	
	battleScene->SetLoadingScene((LoadingScene*)stage1);
	SceneManager::GetSingleton()->AddScene("배틀", battleScene);

	titleScene = new TitleScene;
	SceneManager::GetSingleton()->AddScene("타이틀", titleScene);

	construction = new Construction;
	SceneManager::GetSingleton()->AddScene("타일맵툴", construction);

	SceneManager::GetSingleton()->LoadingChangeScene("타이틀", "로딩1");

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();
	
	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{	
	TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());

	SceneManager::GetSingleton()->Render(backBuffer->GetMemDC());

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{

	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
	
		case VK_SPACE:
			break;
		case VK_LEFT:
			
			break;
		case VK_RIGHT:
		
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

float MainGame::GetAngle(float x1, float y1, float x2, float y2)
{
	

	return atan2((y2 - y1), (x2 - x1));
}

float MainGame::GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}



MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
