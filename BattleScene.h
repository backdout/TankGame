#pragma once
#include "GameNode.h"
#include "pch.h"


class Missile;
class Enemy;
class EnemyManager;
class LoadingScene;
class Player_1p;
class BattleScene : public GameNode
{
private:
	
	Image* bg;
	Image* gameOver;

	Image* clear;

	LoadingScene* load;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	Image* sampleTileImage;
	TILE_INFO tileInfo[TILE_X* TILE_Y];
	//Enemy* enemy;
	float scale;
	RECT totalTileSize;
	EnemyManager* enemyMgr;
	Player_1p * Tank1p;
	RECT tankRect;
	float enemyShowTime;
	float enemyShowTimeCount;
	int enemyCount;
	int enemyDieCount;
	bool isGameOver;
	bool isGameClear;
	int stageNum;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(bool goToCons); // 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	 void SetLoadingScene(LoadingScene* _load) { load = _load; }
	 void Load();
	 void stageLoad(int num);
	 void Save();


	BattleScene();
	virtual ~BattleScene();
};

