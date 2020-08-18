#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Player_1p;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator itMissiles;

	GameNode*	owner;

	float angle;
	FPOINT returnPos;
	TILE_INFO* tileInfo;

	bool isEnemy;
	Player_1p* tank;
	bool isSetting;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPlayer();
	bool Fire();
	void SetOwner(GameNode* gameNode) { owner = gameNode; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	void SetPlayer_1p(Player_1p* _tank) { tank = _tank; }
	vector<Missile*> GetMissile() { return vecMissiles; }
	void SetisEnemy(bool _isEnemy) { isEnemy = _isEnemy; }
	MissileManager();
	~MissileManager();
};

