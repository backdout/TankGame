#include "Player_1p.h"
#include "Image.h"
#include "pch.h"
#include "KeyManager.h"
#include "Animation.h"
#include "MissileManager.h"

HRESULT Player_1p::Init()
{
	tileInfo = new TILE_INFO[TILE_X* TILE_Y];
	ImageManager::GetSingleton()->AddImage("1PTank", "Image/userTank.bmp", pos.x, pos.y, 152, 152, 8, 8, true, RGB(0, 0, 1));
	image = ImageManager::GetSingleton()->FindImage("1PTank");

	userTankTop = new Animation();
	userTankTop->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	userTankTop->SetUpdateTime(FPS / 5.0);
	userTankTop->SetPlayFrame(0, 1, true, true);

	userTankBottom = new Animation();
	userTankBottom->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	userTankBottom->SetUpdateTime(FPS / 5.0);
	userTankBottom->SetPlayFrame(4, 5, true, true);

	userTankLeft = new Animation();
	userTankLeft->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	userTankLeft->SetUpdateTime(FPS / 5.0);
	userTankLeft->SetPlayFrame(2, 3, true, true);

	userTankRight = new Animation();
	userTankRight->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	userTankRight->SetUpdateTime(FPS / 5.0);
	userTankRight->SetPlayFrame(6, 7, true, true);

	currFrameX = currFrameY = 0;
	updateCount = 0;
	pos = { 330,810 };
	movestate = TOP;
	speed = 1.0f;
	moveOverlap = false;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);
	isColl = false;
	angle = 90;
	rcTank = GetRect(pos.x, pos.y, 14 * 4);
	LifeCount = 3;
	ishit = false;;


	colltop = false;
	collbot = false;
	collleft = false;
	collright = false;

	return S_OK;
}

void Player_1p::Release()
{
	SAFE_DELETE(userTankTop);
	SAFE_DELETE(userTankBottom);
	SAFE_DELETE(userTankLeft);
	SAFE_DELETE(userTankRight);

	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void Player_1p::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	{
		missileMgr->SetAngle(angle);
		missileMgr->Fire();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		movestate = MOVE::TOP;
		if (colltop == false)
		{
			if (pos.y >= 34)
			{
				angle = 90;
				pos.y -= 4;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		movestate = MOVE::BOTTOM;
		if (collbot == false)
		{
			if (pos.y <= 810)
			{
				angle = 270;
				pos.y += 4;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		movestate = MOVE::LEFT;
		if (collleft == false)
		{
			if (pos.x >= 68)
			{
				angle = 180;
				pos.x -= 4;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		movestate = MOVE::RIGHT;
		if (collright == false)
		{
			if (pos.x <= 840)
			{
				angle = 360;
				pos.x += 4;
			}
		}
	}
	if (colltop == true)
	{
		if (pos.y >= 34)
		{
			angle = 90;
			pos.y += 4;
			colltop = false;
		}
	}
	if (collbot == true)
	{
		if (pos.y <= 810)
		{
			angle = 270;
			pos.y -= 4;
			collbot = false;
		}
	}
	if (collleft == true)
	{
		if (pos.x >= 68)
		{
			angle = 180;
			pos.x += 4;
			collleft = false;
		}
	}
	if (collright == true)
	{
		if (pos.x <= 840)
		{
			angle = 360;
			pos.x -= 4;
			collright = false;
		}
	}
	rcTank = GetRect(pos.x, pos.y, 14 * 4);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
			
			userTankTop->Start();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{
			
			userTankBottom->Start();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
			
			userTankLeft->Start();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
			
			userTankRight->Start();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
	{
		userTankTop->Stop();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
	{
		userTankBottom->Stop();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
	{
		userTankLeft->Stop();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
	{
		userTankRight->Stop();
	}

	if (missileMgr)
	{
		/*	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
			{
				TimeManager::GetSingleton()->SetIsTestStart(true);
				missileMgr->Fire();
			}*/
		missileMgr->SetTileInfo(tileInfo);
		missileMgr->Update();
	}

	if (userTankTop)userTankTop->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	if (userTankBottom)userTankBottom->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	if (userTankLeft)userTankLeft->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	if (userTankRight)userTankRight->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());



	if (ishit)
	{
		ishit = false;
		if (LifeCount > 0)	LifeCount--;
		else if (LifeCount <= 0) { isdie = true; }
		pos.x = 330;
		pos.y = 810;
	}




}

void Player_1p::Render(HDC hdc)
{
	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
	//Rectangle(hdc, rcTank.left, rcTank.top, rcTank.right, rcTank.bottom);
	//RenderRect()
	if (image)
	{
		switch (movestate)
		{
		case TOP:
			image->AnimationRender(hdc, pos.x, pos.y, userTankTop, 4.0f);
			break;
		case LEFT:
			image->AnimationRender(hdc, pos.x, pos.y, userTankLeft, 4.0f);
			break;
		case RIGHT:
			image->AnimationRender(hdc, pos.x, pos.y, userTankRight, 4.0f);
			break;
		case BOTTOM:
			image->AnimationRender(hdc, pos.x, pos.y, userTankBottom, 4.0f);
			break;
		default:
			break;
		}
	}


}

Player_1p::Player_1p()
{
}

Player_1p::~Player_1p()
{
}
