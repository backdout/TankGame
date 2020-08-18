#include "Button.h"
#include "Image.h"
#include "pch.h"
#include "TitleScene.h"
#include "ButtonFunc.h"
#include "Construction.h"


HRESULT Button::Init(const char* imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	state = BUTTON_STATE::NONE;
	pos.x = posX;
	pos.y = posY;
	this->btnDownFramePoint = btnDownFramePoint;
	this->btnUpFramePoint = btnUpFramePoint;
	openObj = false;
	isSaveBt = false;
	isLoadBt = false;
	tile = nullptr;
	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 

	rc = GetRectToCenter(pos.x, pos.y,
		image->GetFrameWidth(), image->GetFrameHeight());

	return S_OK;
}

//HRESULT Button::Init(const char* imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint, void (ButtonFunk::*ButtonFunc1)(const char*), ButtonFunk* btnfunc)
//{
//	state = BUTTON_STATE::NONE;
//	pos.x = posX;
//	pos.y = posY;
//	this->btnDownFramePoint = btnDownFramePoint;
//	this->btnUpFramePoint = btnUpFramePoint;
//
//
//	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
//
//	rc = GetRectToCenter(pos.x, pos.y,
//		image->GetFrameWidth(), image->GetFrameHeight());
//	this->btnfunc = btnfunc;
//	this->ButtonFunc = nullptr;
//	this->ButtonFunc1 = ButtonFunc1;
//	return S_OK;
//}
//
//HRESULT Button::Init(const char * imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint, void(ButtonFunk::* ButtonFun1)(const char*), ButtonFunk * btnfunc, const char * filename)
//{
//	state = BUTTON_STATE::NONE;
//	pos.x = posX;
//	pos.y = posY;
//	this->btnDownFramePoint = btnDownFramePoint;
//	this->btnUpFramePoint = btnUpFramePoint;
//
//
//	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
//
//	rc = GetRectToCenter(pos.x, pos.y,
//		image->GetFrameWidth(), image->GetFrameHeight());
//	this->btnfunc = btnfunc;
//	this->ButtonFunc = nullptr;
//	this->ButtonFunc1 = ButtonFunc1;
//	this->sceneName = filename;
//	return S_OK;
//}


void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse)) //Point가 Rect안에 들어가있으면 True를 반환해서 아래가 실행된다.
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTON_STATE::DOWN;
			
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && state == BUTTON_STATE::DOWN)
		{
			state = BUTTON_STATE::UP;
			if (btnfunc&&ButtonFunc1)
			{
				(btnfunc->*ButtonFunc1)();
			}
			else if (btnfunc&&ButtonFunc2)
			{
				(btnfunc->*ButtonFunc2)(args->sceneName, args->loadingName);
			}

			if (!(btnfunc)&&tile)
			{
				
				if (isSaveBt)
				{
					tile->Save();
				}
				if (isLoadBt)
				{
					tile->Load();
				}

				if (openObj)
				{
					btnUpFramePoint.y = 1;
					openObj = false;
				}
				else if (!openObj && !isLoadBt & !isSaveBt)
				{
					btnUpFramePoint.y = 0;
					openObj = true;
				}
			}
			
		}
	}
	else
	{
		state = BUTTON_STATE::NONE;
	}

}

void Button::Render(HDC hdc)
{

	switch (state)
	{
	case BUTTON_STATE::DOWN:
		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnDownFramePoint.x, btnDownFramePoint.y);
		break;

	case BUTTON_STATE::NONE:
	case BUTTON_STATE::UP:

		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnUpFramePoint.x, btnUpFramePoint.y);

		break;
	}

	//RenderRectToCenter(hdc, pos.x, pos.y, image->GetFrameWidth(), image->GetFrameHeight());
}

void Button::ChangeScene()
{
	SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1");
}

void Button::CloseBox()
{
}

Button::Button()
{
}

Button::~Button()
{
}
