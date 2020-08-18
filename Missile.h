#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Image;
class Player_1p;
class MissileManager;
class Missile : public GameNode
{
private:

	int size;
	float angle;
	float speed;
	bool isFire;
	float adjustAngle;

	int currFrameX;
	int currFrameY;

	Enemy* target;
	bool isEnemy;

	
	Player_1p* tank;
	Image* img;
	TILE_INFO* tileInfo;
	RECT rcMi;

	/*Player_1p* test;*/
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTarget(Enemy* enemy) { target = enemy; }

	void SetPlayer_1p(Player_1p* _tank) { tank = _tank; }
	void SetIsFire(bool b) { isFire = b; }
	bool GetIsFire() { return isFire; }
	void SetAngle(float angle) { this->angle = angle; }
	float GetSize() { return size; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetFrame(float currFrameX) { this->currFrameX = currFrameX; }
	
	void SetisEnemy(bool _isEnemy) { isEnemy = _isEnemy; }
	
	
	
	float GetFrame() { return currFrameX; }



	RECT GetRcMi() { return rcMi; }



	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	Missile();
	~Missile();
};

