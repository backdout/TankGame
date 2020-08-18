#include "BattleScene.h"
#include "Image.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "LoadingScene.h"
#include "Player_1p.h"

HRESULT BattleScene::Init()
{
	Sleep(1000);
	
	scale = 4.0f;
	bg = ImageManager::GetSingleton()->AddImage("BattleBG", "Image/bg.bmp", 0, 0, 1100, 900, 1, 1);
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/tileMap.bmp", 0, 0, 96, 48, SAMPLETILE_X, SAMPLETILE_Y);
	gameOver = ImageManager::GetSingleton()->AddImage("gameOver", "Image/gameover.bmp", 0, 0, 31, 15, 1, 1, true,RGB(0,0,1));
	clear= ImageManager::GetSingleton()->AddImage("clearBG", "Image/clear.bmp", 0, 0, 1100, 900, 1, 1);


	Load();
	for (int i = 0; i < 3; i++)
	{
		tileInfo[i*12].frameX = 0; tileInfo[i*12].frameY = 0; tileInfo[i*12].terrain = TR_NONE;
		tileInfo[(i * 12) + (1)].frameX = 0; tileInfo[(i * 12) + (1 )].frameY = 0; tileInfo[(i * 12) + (1)].terrain = TR_NONE;
		tileInfo[(i * 12)+ (1*26)].frameX = 0; tileInfo[(i * 12) + (1 * 26)].frameY = 0; tileInfo[(i * 12) + (1 * 26)].terrain = TR_NONE;
		tileInfo[(i * 12) + (1 * 26) + 1].frameX = 0; tileInfo[(i * 12) + (1 * 26) + 1].frameY = 0; tileInfo[(i * 12) + (1 * 26) + 1].terrain = TR_NONE;
	}
	// 적
	enemyMgr = new EnemyManager();
	
	enemyMgr->Init();
	
	Tank1p = new Player_1p();
	Tank1p->Init();
	tankRect = Tank1p->GetTankRect();
	enemyMgr->SetPlayer_1p(Tank1p);
	//enemyMgr->SetPlayer_1p(Tank1p);
	enemyShowTime=0.0f;
	enemyShowTimeCount =rand()%200+300.0f ;
	enemyCount=1;
	enemyDieCount=12;
	isGameOver = false;
	return S_OK;
}

HRESULT BattleScene::Init(bool goToCons)
{


	scale = 4.0f;
	bg = ImageManager::GetSingleton()->AddImage("BattleBG", "Image/bg.bmp", 0, 0, 1100, 900, 1, 1);
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/tileMap.bmp", 0, 0, 96, 48, SAMPLETILE_X, SAMPLETILE_Y);
	gameOver = ImageManager::GetSingleton()->AddImage("gameOver", "Image/gameover.bmp", 0, 0, 31, 15, 1, 1, true, RGB(0, 0, 1));
	clear = ImageManager::GetSingleton()->AddImage("clearBG", "Image/clear.bmp", 0, 0, 1100, 900, 1, 1);
	if (goToCons)
	{
		Load();
	}
	else
	{
		stageLoad(3);
		Save();
	}
	for (int i = 0; i < 3; i++)
	{
		tileInfo[i * 12].frameX = 0; tileInfo[i * 12].frameY = 0; tileInfo[i * 12].terrain = TR_NONE;
		tileInfo[(i * 12) + (1)].frameX = 0; tileInfo[(i * 12) + (1)].frameY = 0; tileInfo[(i * 12) + (1)].terrain = TR_NONE;
		tileInfo[(i * 12) + (1 * 26)].frameX = 0; tileInfo[(i * 12) + (1 * 26)].frameY = 0; tileInfo[(i * 12) + (1 * 26)].terrain = TR_NONE;
		tileInfo[(i * 12) + (1 * 26) + 1].frameX = 0; tileInfo[(i * 12) + (1 * 26) + 1].frameY = 0; tileInfo[(i * 12) + (1 * 26) + 1].terrain = TR_NONE;
	}
	// 적
	enemyMgr = new EnemyManager();
	stageNum = 1;
	enemyMgr->Init();

	Tank1p = new Player_1p();
	Tank1p->Init();
	tankRect = Tank1p->GetTankRect();
	enemyMgr->SetPlayer_1p(Tank1p);
	//enemyMgr->SetPlayer_1p(Tank1p);
	enemyShowTime = 0.0f;
	enemyShowTimeCount = rand() % 200 + 300.0f;
	enemyCount = 1;
	enemyDieCount = 12;
	isGameOver = false;
	return S_OK;
}



void BattleScene::Release()
{
	Tank1p->Release();
	SAFE_DELETE(Tank1p);

	enemyMgr->Release();
	SAFE_DELETE(enemyMgr);
}

void BattleScene::Update()
{
	enemyShowTime += TimeManager::GetSingleton()->GetDeltaTime();
	SoundManager::GetSingleton()->Update();

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RETURN))
	{
		SceneManager::GetSingleton()->ChangeScene("타이틀");
		return;	//체인지되며 밑에있는 애들 랜더 안시키기위해 리턴해버리자
	}

	

	if (enemyMgr)
	{
		enemyMgr->SetTileInfo(tileInfo);
		enemyMgr->Update();
		if (enemyShowTimeCount <=enemyShowTime*100)
		{
			if (enemyCount < 6)
			{
				int a = rand() % 2;
				if (a == 0)
				{
					enemyMgr->AddEnemy(0, 0);

				}
				else if (a == 1)
				{
					enemyMgr->AddEnemy(6, 0);
				}
				
				enemyCount++;
			}
			enemyShowTime = 0.0f;
			enemyShowTimeCount = rand() % 200 + 300.0f;
		}



		if (enemyMgr->GetDieCount() == 6)
		{
			//isGameOver = true;
			isGameClear = true;
		}
	}

	if (!isGameOver)
	{
		if (Tank1p)
		{
			Tank1p->SetTileInfo(tileInfo);
			Tank1p->Update();
			tankRect = Tank1p->GetTankRect();
			isGameOver = Tank1p->GetIsdie();
		}
		
		if (tileInfo[663].terrain == TR_NONE || tileInfo[662].terrain == TR_NONE
			|| tileInfo[637].terrain == TR_NONE || tileInfo[636].terrain == TR_NONE)
		{
			isGameOver = true;
		}
		
		if (isGameOver)
		{
			SoundManager::GetSingleton()->Play("게임오버");
		}



	}

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (!(tileInfo[i].terrain == 0 || tileInfo[i].terrain == 3 || tileInfo[i].terrain == 5))
		{
			if (CheckRectCollision(tileInfo[i].rcTile, tankRect))
			{
				if (Tank1p->GetMovestate() == TOP)
				{
					Tank1p->SetCollTop(true);
				}
				else if (Tank1p->GetMovestate() == BOTTOM)
				{
					Tank1p->SetCollBot(true);
				}
				else if (Tank1p->GetMovestate() == LEFT)
				{
					Tank1p->SetCollLeft(true);
				}
				else if (Tank1p->GetMovestate() == RIGHT)
				{
					Tank1p->SetCollRight(true);
				}
				break;
			}
		}

	}



	if (isGameClear==true)
	{
		if (isGameClear&&stageNum == 1)
		{
			stageNum++;
			isGameClear = false;

			stageLoad(stageNum);
			Save();
			for (int i = 0; i < 3; i++)
			{
				tileInfo[i * 12].frameX = 0; tileInfo[i * 12].frameY = 0; tileInfo[i * 12].terrain = TR_NONE;
				tileInfo[(i * 12) + (1)].frameX = 0; tileInfo[(i * 12) + (1)].frameY = 0; tileInfo[(i * 12) + (1)].terrain = TR_NONE;
				tileInfo[(i * 12) + (1 * 26)].frameX = 0; tileInfo[(i * 12) + (1 * 26)].frameY = 0; tileInfo[(i * 12) + (1 * 26)].terrain = TR_NONE;
				tileInfo[(i * 12) + (1 * 26) + 1].frameX = 0; tileInfo[(i * 12) + (1 * 26) + 1].frameY = 0; tileInfo[(i * 12) + (1 * 26) + 1].terrain = TR_NONE;
			}

			enemyMgr->Init();
			Tank1p->Init();
			tankRect = Tank1p->GetTankRect();
			enemyMgr->SetPlayer_1p(Tank1p);
			//enemyMgr->SetPlayer_1p(Tank1p);
			enemyShowTime = 0.0f;
			enemyShowTimeCount = rand() % 200 + 300.0f;
			enemyCount = 1;
			enemyDieCount = 6;
			isGameOver = false;


		}
		else if (stageNum == 2)
		{
			stageNum++;
			isGameClear = false;

			stageLoad(1);
			Save();
			for (int i = 0; i < 3; i++)
			{
				tileInfo[i * 12].frameX = 0; tileInfo[i * 12].frameY = 0; tileInfo[i * 12].terrain = TR_NONE;
				tileInfo[(i * 12) + (1)].frameX = 0; tileInfo[(i * 12) + (1)].frameY = 0; tileInfo[(i * 12) + (1)].terrain = TR_NONE;
				tileInfo[(i * 12) + (1 * 26)].frameX = 0; tileInfo[(i * 12) + (1 * 26)].frameY = 0; tileInfo[(i * 12) + (1 * 26)].terrain = TR_NONE;
				tileInfo[(i * 12) + (1 * 26) + 1].frameX = 0; tileInfo[(i * 12) + (1 * 26) + 1].frameY = 0; tileInfo[(i * 12) + (1 * 26) + 1].terrain = TR_NONE;
			}

			enemyMgr->Init();
			Tank1p->Init();
			tankRect = Tank1p->GetTankRect();
			enemyMgr->SetPlayer_1p(Tank1p);
			//enemyMgr->SetPlayer_1p(Tank1p);
			enemyShowTime = 0.0f;
			enemyShowTimeCount = rand() % 200 + 300.0f;
			enemyCount = 1;
			enemyDieCount = 6;
			isGameOver = false;


		}
		if (stageNum == 3)
		{
			//stageNum++;
			//isGameClear = false;

		}


	}

}

void BattleScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_Y, BLACKNESS);
	if (bg)
	{
		bg->Render(hdc, 0, 0);
	}
	
	
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (!(tileInfo[i].terrain == TR_WEED))
		{
			sampleTileImage->FrameRender(hdc, tileInfo[i].rcTile.left + (TILESIZE / 2), tileInfo[i].rcTile.top + (TILESIZE / 2), tileInfo[i].frameX, tileInfo[i].frameY, scale);
		}
		/*if (tileInfo[i].terrain == TR_OBJ)
			objTileImage->FrameRender(hdc, tileInfo[i].rcTile.left + (TILESIZE / 2)+68, tileInfo[i].rcTile.top + (TILESIZE / 2)+34, tileInfo[i].objFrameX, tileInfo[i].objFrameY, scale);*/
		/*if (!(tileInfo[i].terrain == 0 || tileInfo[i].terrain == 3 || tileInfo[i].terrain == 5))
		{
			Rectangle(hdc, tileInfo[i].rcTile.left, tileInfo[i].rcTile.top, tileInfo[i].rcTile.right, tileInfo[i].rcTile.bottom);
		}*/


	}
	if (Tank1p)
	{
		Tank1p->Render(hdc);
	}
	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if ((tileInfo[i].terrain == TR_WEED))
		{
			sampleTileImage->FrameRender(hdc, tileInfo[i].rcTile.left + (TILESIZE / 2), tileInfo[i].rcTile.top + (TILESIZE / 2), tileInfo[i].frameX, tileInfo[i].frameY, scale);
		}
	}
	
	if (isGameOver)
	{
		gameOver->Render(hdc, 350, 350, 5.0f);
	}

	if (isGameClear&&stageNum == 3)
	{
		clear->Render(hdc, 0, 0);
	}


}

void BattleScene::Load()
{
	DWORD readByte;
	HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void BattleScene::stageLoad(int num)
{

	DWORD readByte;
	if (num == 1)
	{
		HANDLE hFile = CreateFile("Save/stage1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}
	else if (num == 2)
	{
		HANDLE hFile = CreateFile("Save/stage2.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}
	else if (num == 3)
	{
		HANDLE hFile = CreateFile("Save/stage3.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}

	


}

void BattleScene::Save()
{

	DWORD writtenByte;
	HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &writtenByte, NULL);
	CloseHandle(hFile);

}



BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}
