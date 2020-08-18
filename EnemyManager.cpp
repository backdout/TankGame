#include "EnemyManager.h"
#include "Enemy.h"
#include "Player_1p.h"


HRESULT EnemyManager::Init()
{

//	addImg= ImageManager::GetSingleton()->AddImage("에네미생성",)
	vecEnemys.resize(1);
	//tank = new Player_1p();
	vecEnemys[0] = new Enemy();
	//vecEnemys[0]->SetPlayer_1p(tank);
	vecEnemys[0]->Init(6,0);
	isSetting = false;
	dieCount = 0;
	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		SAFE_DELETE((*itEnemys));
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	int die=0;
	if (!isSetting)
	{
		isSetting = true;
		for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
		{
			(*itEnemys)->SetPlayer_1p(tank);
			(*itEnemys)->SetTileInfo(tileInfo);
		}
	}

	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{

		
		(*itEnemys)->Update();
		if ((*itEnemys)->GetIsDie()) 
		{ die++; }

		dieCount = die;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('N'))
	{
		AddEnemy(200, 200);
	}
	

}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}
}

void EnemyManager::AddEnemy(float posX, float posY)
{
	Enemy* enemy = new Enemy();
	enemy->SetPlayer_1p(tank);
	//1번 위치 0,0 2번 6,0 3번 12,0;
	enemy->Init(posX, posY);
	enemy->SetPlayer_1p(tank);
	enemy->SetTileInfo(tileInfo);
	vecEnemys.push_back(enemy);
}

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
