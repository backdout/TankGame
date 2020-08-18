#include "LoadingScene.h"

#include <Windows.h>
#include "Animation.h"
#include "Image.h"
HRESULT LoadingScene::Init()
{	
	stage1 = ImageManager::GetSingleton()->AddImage("로딩", "Image/loading.bmp", 1100, 900);
	stage2 = ImageManager::GetSingleton()->AddImage("스테이지2", "Image/stage2.bmp", 1100, 900);
	stage3 = ImageManager::GetSingleton()->AddImage("스테이지3", "Image/stage3.bmp", 1100, 900);
	stage4 = ImageManager::GetSingleton()->AddImage("스테이지4", "Image/stage4.bmp", 1100, 900);

	//percent = 0;
	//// 0 ~ 마지막 프레임까지 순차적으로 진행
	//ani = new Animation();
	//ani->Init(bg->GetWidth(), bg->GetHeight(), bg->GetFrameWidth(), bg->GetFrameHeight());
	//ani->SetUpdateTime(FPS/3.0f);
	//ani->SetPlayFrame(false, true);

	//playAni = ani;
	//playAni->Start();
	return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{

	//if (playAni)
	//{
	//	playAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	//}


}

void LoadingScene::Render(HDC hdc)
{
	if (stage1)
	{
		stage1->Render(hdc, 0, 0);
	}
	else if (stage2)
	{
		stage2->Render(hdc, 0, 0);
	}
	else if (stage3)
	{
		stage3->Render(hdc, 0, 0);
	}
	else if (stage4)
	{
		stage4->Render(hdc, 0, 0);
	}

	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, percent*125, 20);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

}

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}
