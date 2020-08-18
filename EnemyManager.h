#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Enemy;
class Player_1p;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*>	vecEnemys;
	vector<Enemy*>::iterator	itEnemys;
	TILE_INFO* tileInfo;
	Player_1p* tank;
	bool isSetting;
	Image* addImg;
	int dieCount;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPlayer_1p(Player_1p* _tank) { tank = _tank; }

	int GetDieCount() { return dieCount; }
	void AddEnemy(float posX, float posY);
	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	EnemyManager();
	~EnemyManager();
};

