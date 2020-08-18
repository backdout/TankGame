#include "MissileManager.h"
#include "Missile.h"
#include "Player_1p.h"

HRESULT MissileManager::Init()
{
	//vecMissiles.reserve(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	Missile* missile = new Missile();
	//	missile->Init();
	//	vecMissiles.push_back(missile);
	//}
	isSetting = false;
	tileInfo = new TILE_INFO[TILE_X* TILE_Y];
	tank = new Player_1p();

	vecMissiles.resize(10);
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i] = new Missile();
		vecMissiles[i]->Init();
		//vecMissiles[i]->SetPlayer_1p(tank);
		//vecMissiles[i]->SetisEnemy(isEnemy);
	}
	
	owner = nullptr;
	return S_OK;
}

void MissileManager::Release()
{
	for (auto& it : vecMissiles)
	{
		it->Release();
		SAFE_DELETE(it);
	}
	vecMissiles.clear();
}
void MissileManager::Update()
{
	if (!isSetting)
	{
		for (auto& it : vecMissiles)
		{
			it->SetTileInfo(tileInfo);
			it->SetPlayer_1p(tank);
			it->SetisEnemy(isEnemy);
		}
	}
	for (auto& it : vecMissiles)
	{	
		//it->SetTileInfo(tileInfo);
		it->Update();
	}
}
void MissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}
void MissileManager::SetPlayer()
{
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->SetPlayer_1p(tank);
		vecMissiles[i]->SetisEnemy(isEnemy);
	}
}
bool MissileManager::Fire()
{
	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			break;
		}

		it->SetIsFire(true);
		it->SetAngle(DEGREE_TO_RADIAN(angle));
		returnPos = owner->GetPos();
		returnPos.x += 20;
		returnPos.y += 20;
		it->SetPos(returnPos);
		if (angle == 90)
		{
			it->SetFrame(0);
		}
		if (angle == 180)
		{
			it->SetFrame(1);
		}
		if (angle == 270)
		{
			it->SetFrame(2);
		}
		if (angle == 360)
		{
			it->SetFrame(3);
		}
		return true;
	}

	return false;
}

MissileManager::MissileManager()
{
}


MissileManager::~MissileManager()
{
}
