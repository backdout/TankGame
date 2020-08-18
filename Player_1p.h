#pragma once
#include "GameNode.h"

class Image;
class MissileManager;
class Animation;
class Player_1p : public GameNode
{
protected:
	Image* image;
	Animation* userTankTop;
	Animation* userTankBottom;
	Animation* userTankLeft;
	Animation* userTankRight;
	bool moveOverlap;
	int currFrameX, currFrameY;
	int updateCount;
	RECT rcTank;


	int size; 
	TILE_INFO* tileInfo;
	float angle;
	float speed;
	int fireDelay;
	int fireCount;

	MOVE movestate;
	bool isColl;
	MissileManager* missileMgr;
	bool ishit;
	bool isdie;
	int LifeCount;

	bool colltop;
	bool collbot;
	bool collleft;
	bool collright;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	RECT GetTankRect() { return rcTank; };
	void SetIsColl(bool _isColl) {  isColl= _isColl;}
	bool GetIsColl() { return isColl; }
	MOVE GetMovestate() { return movestate; }
	MissileManager* GetMissileMgr() {  return missileMgr; }
	bool GetIshit() {return ishit;}
	bool GetIsdie() { return isdie; }
	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	int GetLifeCount() { return LifeCount; }
	void SetIshit(bool _ishit) { ishit = _ishit; }
	//void SetIshit(bool _ishit) { ishit = _ishit; }
	void SetLifeCount(int  _LifeCount) { LifeCount= _LifeCount; }

	void SetCollTop(bool b) { colltop = b; }
	void SetCollBot(bool b) { collbot = b; }
	void SetCollLeft(bool b) { collleft = b; }
	void SetCollRight(bool b) { collright = b; }
	//bool GetIsdie() { return isdie; };


	/*void SetTankAngle(float _angle) { angle = _angle; }
	float GetTankAngle() { return angle; }*/

	Player_1p();
	~Player_1p();


};
