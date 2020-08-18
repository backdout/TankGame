#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Animation.h"
#include "Astar.h"
#include "pch.h"
#include "Player_1p.h"
#include "Missile.h"

HRESULT Enemy::Init()
{
	isSetting = false;
	isDie = false;
	image = ImageManager::GetSingleton()->AddImage("EnemyTank", "Image/enemyTank", pos.x, pos.y, 152, 152, 8, 8, true, RGB(0, 0, 1));

	enemyTop = new Animation();
	enemyTop->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyTop->SetUpdateTime(FPS / 10.0);
	enemyTop->SetPlayFrame(0, 1, true, true);

	enemyBottom = new Animation();
	enemyBottom->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyBottom->SetUpdateTime(FPS / 10.0);
	enemyBottom->SetPlayFrame(4, 5, true, true);

	enemyLeft = new Animation();
	enemyLeft->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyLeft->SetUpdateTime(FPS / 5.0);
	enemyLeft->SetPlayFrame(2, 3, true, true);

	enemyRight = new Animation();
	enemyRight->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyRight->SetUpdateTime(FPS / 5.0);
	enemyRight->SetPlayFrame(6, 7, true, true);

	pos = { 0, 0 };
	tileInfo = new TILE_INFO[TILE_X* TILE_Y];
	currFrameX = currFrameY = 0;
	updateCount = 0;
	speed = 1.0f;
	size = 40;
	fireDelay = rand() % 200 + 300;
	fireCount = 0;
	fireTime = 0;
	turn = false;
	
	missileMgr = new MissileManager();
	//tank = new Player_1p();
	missileMgr->SetisEnemy(true);
	missileMgr->Init();
	missileMgr->SetPlayer_1p(tank);
	missileMgr->SetPlayer();
	missileMgr->SetOwner(this);
	missileMgr->SetTileInfo(tileInfo);
	//vecMissiles= 
	enemystate = BOTTOM;
	angle = 270;
	playAni = enemyBottom;
	playAni->Start();

	Load();
	pos.x = tileInfo[0].rcTile.left; 
	pos.y=tileInfo[0].rcTile.top ;
	MovePath(0,0);

	//
	
	return S_OK;
}

HRESULT Enemy::Init(int posX, int posY)
{
	isSetting = false;
	isDie = false;
	//pos.x = posX;
	//pos.y = posY;
	tileInfo = new TILE_INFO[TILE_X* TILE_Y];
	Load();
	pos.x = tileInfo[posX*2].rcTile.left;
	pos.y = tileInfo[posY*2].rcTile.top;

	image = ImageManager::GetSingleton()->AddImage("EnemyTank", "Image/enemyTank.bmp", pos.x, pos.y, 152, 152, 8, 8, true, RGB(0, 0, 1));

	enemyTop = new Animation();
	enemyTop->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyTop->SetUpdateTime(FPS / 5.0);
	enemyTop->SetPlayFrame(0, 1, true, true);

	enemyBottom = new Animation();
	enemyBottom->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyBottom->SetUpdateTime(FPS / 5.0);
	enemyBottom->SetPlayFrame(4, 5, true, true);

	enemyLeft = new Animation();
	enemyLeft->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyLeft->SetUpdateTime(FPS / 5.0);
	enemyLeft->SetPlayFrame(2, 3, true, true);

	enemyRight = new Animation();
	enemyRight->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	enemyRight->SetUpdateTime(FPS / 5.0);
	enemyRight->SetPlayFrame(6, 7, true, true);

	
	currFrameX = currFrameY = 0;
	updateCount = 0;

	speed = 1.0f;
	angle = PI;
	size = 40;

	fireDelay = rand() % 200 + 200.0f;
	fireCount = 0;
	fireTime = 0;
	
	tank = new Player_1p();
	rcTank = GetRect(pos.x, pos.y, 14 * 4);

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);
	
   
	enemystate = BOTTOM;
	playAni = enemyBottom;
	angle = 270;
	playAni->Start();

	MovePath(posX, posY);
	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);

	SAFE_DELETE(enemyTop);
	SAFE_DELETE(enemyBottom);
	SAFE_DELETE(enemyLeft);
	SAFE_DELETE(enemyRight);
}

void Enemy::Update()
{
	if (!isSetting)
	{
		isSetting = true;
		missileMgr->SetisEnemy(true);
		missileMgr->SetPlayer();
		missileMgr->SetTileInfo(tileInfo);
		missileMgr->SetPlayer_1p(tank);
		missileMgr->SetTileInfo(tileInfo);
		tankMissileMgr = tank->GetMissileMgr();
	}

	if(!isDie)
	{
		updateCount++;
		fireTime += TimeManager::GetSingleton()->GetDeltaTime();
		if (pathList.size() < 1)
		{
			if (enemystate == RIGHT)
			{
				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					pos.x += 4;

				}
			}
			else if (enemystate == LEFT)
			{

				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					pos.x -= 4;
				}
			}
			else if (enemystate == TOP)
			{

				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					pos.y -= 4;

				}

			}
			else if (enemystate == BOTTOM)
			{

				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					pos.y += 4;

				}
			}

			rcTank = GetRect(pos.x, pos.y, 14 * 4);
			for (int i = 0; i < TILE_X*TILE_Y; i++)
			{
				if (!(tileInfo[i].terrain == 0 || tileInfo[i].terrain == 3 || tileInfo[i].terrain == 5))
				{
					if (CheckRectCollision(tileInfo[i].rcTile, rcTank))
					{
						int a = rand() % 4;
						enemystate = static_cast<MOVE>(a);
						if (a == 0) { playAni = enemyTop; angle = 90; }
						else if (a == 1) { playAni = enemyLeft; angle = 180; }
						else if (a == 2) { playAni = enemyRight; angle = 360; }
						else if (a == 3) { playAni = enemyBottom; angle = 270; }
						playAni->Start();
						missileMgr->Fire();
						break;
					}

				}

			}

			if (pos.x > 840)
			{
				int a = rand() % 4;
				enemystate = static_cast<MOVE>(a);
				if (a == 0) {
					playAni = enemyTop; angle = 90;
				}
				else if (a == 1) {
					playAni = enemyLeft; angle = 180;
				}
				else if (a == 2) {
					playAni = enemyLeft; enemystate = static_cast<MOVE>(1); angle = 180;
				}
				else if (a == 3) {
					playAni = enemyBottom; angle = 270;
				}
				playAni->Start();
			}
			else if (pos.x < 68)
			{
				int a = rand() % 4;
				enemystate = static_cast<MOVE>(a);
				if (a == 0) {
					playAni = enemyTop; angle = 90;
				}
				else if (a == 1) {
					playAni = enemyRight; enemystate = static_cast<MOVE>(2); angle = 360;
				}
				else if (a == 2) {
					playAni = enemyRight; angle = 360;
				}
				else if (a == 3) {
					playAni = enemyBottom; angle = 270;
				}
				playAni->Start();

			}
			else if (pos.y > 810)
			{
				int a = rand() % 3;
				enemystate = static_cast<MOVE>(a);

				if (a == 0) { playAni = enemyTop; angle = 90; }
				else if (a == 1) {
					playAni = enemyLeft; angle = 180;
				}
				else if (a == 2) {
					playAni = enemyRight; angle = 360;
				}
				playAni->Start();
			}
			else if (pos.y < 34)
			{
				int a = rand() % 3;
				enemystate = static_cast<MOVE>(a + 1);
				if (a == 0)
				{
					playAni = enemyLeft; angle = 90;
				}
				else if (a == 1)
				{
					playAni = enemyRight; angle = 3600;
				}
				else if (a == 2)
				{
					playAni = enemyBottom; angle = 270;
				}
				playAni->Start();
			}

			MovePath((pos.x - 67) / 64, (pos.y - 33) / 64);
		}

		else if (pathList.size() > 1)
		{
			if (enemystate == RIGHT)
			{
				if (updateCount % 2 == 1)
				{
					updateCount = 0;

					if ((currTilePos.x) > pos.x)
					{
						pos.x += 4;
					}
					else MovePathCheck();
				}
			}
			else if (enemystate == LEFT)
			{
				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					if (currTilePos.x < pos.x)
					{
						pos.x -= 4;
					}
					else  MovePathCheck();
				}
			}
			else if (enemystate == TOP)
			{
				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					if (currTilePos.y < pos.y)
					{
						pos.y -= 4;
					}
					else  MovePathCheck();
				}
			}
			else if (enemystate == BOTTOM)
			{
				if (updateCount % 2 == 1)
				{
					updateCount = 0;
					if ((currTilePos.y) > pos.y)
					{
						pos.y += 4;
					}
					else  MovePathCheck();
				}
			}

		}

		if (playAni)playAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		if (pathList.size() == 1)
		{
			MovePath(pathList.front().x, pathList.front().y);

		}

		rcTank = GetRect(pos.x, pos.y, 14 * 4);

		if (missileMgr)
		{
			if (fireDelay <= (fireTime * 100))
			{
				//TimeManager::GetSingleton()->SetIsTestStart(true);
				missileMgr->SetAngle(angle);
				missileMgr->Fire();
				fireTime = 0;
			}
			missileMgr->SetPlayer();
			missileMgr->SetTileInfo(tileInfo);
			missileMgr->Update();	



		}
		if (tank)
		{
			for (auto it : tankMissileMgr->GetMissile())
			{
				if (CheckRectCollision(this->rcTank, it->GetRcMi()))
				{
					if (it->GetIsFire())
					{
						FPOINT posMi = { 0,0 };
						it->SetIsFire(false);
						it->SetPos(posMi);
						this->isDie = true;
						pos.x = 0;
						pos.y = 0;
						break;
					}
				}
			}
		}
	}
}

void Enemy::Render(HDC hdc)
{
	if (!isDie)
	{
		if (missileMgr)
		{
			missileMgr->Render(hdc);
		}
		if (image)
		{
			image->AnimationRender(hdc, pos.x, pos.y, playAni, 4.0f);
		}
	}
	//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
}


void Enemy::Load()
{

	DWORD readByte;
	HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void Enemy::MovePath(int x, int y)
{
	Astar::Coordinate A(x, y);
	Astar::Coordinate B(6, 13);
	Astar astar(A, B);
	int size = astar.GetPath().size();
	if (size > 1)
	{
		astar.GetPath().pop_front();


		for (int i = 1; i < size; i++)
		{
			POINT a = { astar.GetPos(i).x, astar.GetPos(i).y };
			pathList.push_back(a);
		}
		tiletX = 0;
		tiletY = 0;
		if (tiletX > pathList.front().x && tiletY == pathList.front().y)
		{
			enemystate = LEFT;
			angle = 180;
			playAni = enemyLeft;
			playAni->Start();
		}
		else if (tiletX < pathList.front().x &&tiletY == pathList.front().y)
		{
			enemystate = RIGHT;
			angle = 360;
			playAni = enemyRight;
			playAni->Start();
		}
		else if (tiletX == pathList.front().x&&tiletY > pathList.front().y)
		{
			enemystate = TOP;
			angle = 90;
			playAni = enemyTop;
			playAni->Start();
		}
		else if (tiletX == pathList.front().x&&tiletY < pathList.front().y)
		{
			enemystate = BOTTOM;
			angle = 270;
			playAni = enemyBottom;
			playAni->Start();
		}
		tiletX = pathList.front().x;
		tiletY = pathList.front().y;
		currTilePos.x = tileInfo[tiletX * 2 + (tiletY * 2 * TILE_X)].rcTile.left;
		currTilePos.y = tileInfo[tiletX * 2 + (tiletY * 2 * TILE_X)].rcTile.top;
	}
}

void Enemy::MovePathCheck()
{
	if (pathList.size() > 1)
	{
		pathList.pop_front();
		tiletX1 = pathList.front().x;
		tiletY1 = pathList.front().y;

		if (tiletX > tiletX1)
		{
			enemystate = LEFT;
			angle = 180;
			playAni = enemyLeft;
			playAni->Start();

		}
		else if (tiletX < tiletX1)
		{
			enemystate = RIGHT;
			angle = 360;
			playAni = enemyRight;
			playAni->Start();

		}
		else if (tiletY > tiletY1)
		{
			enemystate = TOP;
			angle = 90;
			playAni = enemyTop;
			playAni->Start();

		}
		else if (tiletY < tiletY1)
		{
			enemystate = BOTTOM;
			angle = 270;
			playAni = enemyBottom;
			playAni->Start();

		}
		tiletX = pathList.front().x;
		tiletY = pathList.front().y;
		currTilePos.x = tileInfo[tiletX * 2 + (tiletY * 2 * TILE_X)].rcTile.left;
		currTilePos.y = tileInfo[tiletX * 2 + (tiletY * 2 * TILE_X)].rcTile.top;
	}
	
	return;
}



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
