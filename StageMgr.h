#pragma once
#include "GameNode.h"


class StageMgr : public GameNode
{
private:
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddEnemy(float posX, float posY);

	StageMgr();
	~StageMgr();
};
