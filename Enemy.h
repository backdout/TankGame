#pragma once
#include "GameNode.h"
#include <list>
#include <vector>

class Image;
class Missile;
class MissileManager;
class Animation;
class Astar;
class Player_1p;
class Enemy : public GameNode
{
protected:
	Image* image;
	Animation* enemyTop;
	Animation* enemyBottom;
	Animation* enemyLeft;
	Animation* enemyRight;
	Animation* playAni;
	int currFrameX, currFrameY;
	int updateCount;

	int size;
	float angle;
	float speed;

	int fireDelay;
	int fireCount;
	MOVE enemystate;
	bool turn;
	float fireTime;
	MissileManager* missileMgr;
	MissileManager* tankMissileMgr;
	list<POINT> pathList;
	//TILE_INFO tileInfo[TILE_X* TILE_Y];
	int tiletX;
	int tiletY;
	int tiletX1;
	int  tiletY1;
	FPOINT currTilePos;
	RECT rcTank;

	TILE_INFO* tileInfo;
	Player_1p* tank;
	bool isSetting;

	//vector<Missile*> vecMissiles;
	bool isDie;
	//tileInfo[0].

	//list<Coordinate*> astarListCopy;
public:
	virtual HRESULT Init();
	virtual HRESULT Init(int posX, int posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Load();
	void MovePath(int x, int y);
	void MovePathCheck();

	void SetPlayer_1p(Player_1p* _tank) { tank = _tank; }

	bool GetIsDie() { return isDie; }


	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	//void SetTarget(Tank* tank);
	//FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

