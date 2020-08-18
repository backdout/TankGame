#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunc.h"


HRESULT TitleScene::Init()
{
	if (tankFramYIndex == 0)
	{
		loadingTime = 0;
		goToCons = false;
	}
	SoundManager::GetSingleton()->AddSound("Dark Waltz.mp3", "Sound/Dark Waltz.mp3",
		true, true);
	
	tankFramYIndex = 0;
	ImageManager::GetSingleton()->AddImage("��Ʋ��ư", "Image/player1.bmp", 0.0f, 0.0f, 200, 47, 1, 1);
	ImageManager::GetSingleton()->AddImage("��Ÿ�Ϲ�ư", "Image/cons.bmp", 0.0f, 0.0f, 242, 47, 1, 1);
	tank = ImageManager::GetSingleton()->AddImage("1PTank", "Image/userTank.bmp", 0, 0, 152, 152, 8, 8, true, RGB(0, 0, 1));
	bg = ImageManager::GetSingleton()->AddImage("titleBG", "Image/TitleStage.bmp", WINSIZE_X, WINSIZE_Y);
	loading = ImageManager::GetSingleton()->AddImage("��������1", "Image/stage1.bmp", 1100, 900);
	POINT upFramePoint = { 0, 0 };
	POINT downFramePoint = { 0, 1 };
	btFunc = new ButtonFunc();
	bt1 = new Button();
	args= new ARG_INFO;
	args->loadingName = "�ε�1";
	args->sceneName = "��Ʋ";
	//void(ButtonFunc::*pchange) (void) = &ButtonFunk::ChangeScene;
	bt1->Init("��Ʋ��ư", 540, 680, downFramePoint, upFramePoint);
	bt1->SetButtonFunc(btFunc, nullptr, &ButtonFunc::ChangeScene2, args);

	args2 = new ARG_INFO;

	args2->loadingName = "�ε�1";
	args2->sceneName = "Ÿ�ϸ���"; //

	bt2 = new Button();
	bt2->Init("��Ÿ�Ϲ�ư", 560, 740, downFramePoint, upFramePoint);
	bt2->SetButtonFunc(btFunc, nullptr, &ButtonFunc::ChangeScene2, args2);
	if (isInit)
	{
		isTile = true;
		isBattle = true;
	}
	isInit = true;
	isLoading = false;
	return S_OK;
}

void TitleScene::Release()
{

	bt1->Release();
	SAFE_DELETE(bt1);
	bt2->Release();
	SAFE_DELETE(bt2);
	SAFE_DELETE(btFunc);
	SAFE_DELETE(args);
	SAFE_DELETE(args2);

}

void TitleScene::Update()
{
	SoundManager::GetSingleton()->Update();
	loadingTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (!isLoading)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RETURN))
		{
			SoundManager::GetSingleton()->Play("��������");
			if (tankFramYIndex == 0)
			{
				if (!goToCons)
				{

					loadingTime = 0;
					isLoading = true;
				}
				else
				{
					SceneManager::GetSingleton()->LoadingChangeScene("��Ʋ", "�ε�1");
				}

				isBattle = true;
				isTile = false;
				goToCons = false;
				return;	//ü�����Ǹ� �ؿ��ִ� �ֵ� ���� �Ƚ�Ű������ �����ع�����
			}
			else if (tankFramYIndex == 1)
			{

				SceneManager::GetSingleton()->LoadingChangeScene("Ÿ�ϸ���", "�ε�1");
				isTile = true;
				goToCons = true;
				return;	//ü�����Ǹ� �ؿ��ִ� �ֵ� ���� �Ƚ�Ű������ �����ع�����
			}
		}


		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
		{
			if (tankFramYIndex == 0)tankFramYIndex = 1;
			else tankFramYIndex = 0;

		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
		{
			if (tankFramYIndex == 0)tankFramYIndex = 1;
			else tankFramYIndex = 0;

		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
		{
			if (tankFramYIndex == 0)tankFramYIndex = 1;
			else tankFramYIndex = 0;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
		{
			if (tankFramYIndex == 0)tankFramYIndex = 1;
			else tankFramYIndex = 0;
		}

	}
	else
	{
		if (loadingTime >= 1.5f)
		{
			SceneManager::GetSingleton()->ChangeScene("��Ʋ", false);
		}
	}
	/*if (bt1) bt1->Update();
	if (bt2) bt2->Update();
	*/


}

void TitleScene::Render(HDC hdc)
{
	if (!isLoading)
	{
		bg->Render(hdc, 0, 0);

		if (bt1) bt1->Render(hdc);
		if (bt2) bt2->Render(hdc);
		if (tank) tank->FrameRender(hdc, 400, tankFramY[tankFramYIndex], 6, 1, 2.0);
	}
	else
	{
		if (loading) loading->Render(hdc, 0, 0);
	}


}

//void TitleScene::ChangeScene()
//{
//	SceneManager::GetSingleton()->ChangeScene("��Ʋ", "�ε�1");
//}

//void TitleScene::CloseBox()
//{
//}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
