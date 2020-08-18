#pragma once
#include "GameNode.h"

class TitleScene;
class BattleScene;
class LoadingScene;
class Image;
class Construction;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	Image* bg;
	Image* backBuffer;

	//Scene
	BattleScene* battleScene;
	GameNode* titleScene;
	GameNode* stage1;
	GameNode* stage2;
	GameNode* stage3;
	GameNode* stage4;
	GameNode* construction;
	
	


	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);
	/*bool CheckCollision(Missile* m1, Missile* m2);*/

	MainGame();
	~MainGame();
};

