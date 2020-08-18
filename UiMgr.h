#pragma once

#include "GameNode.h"


class UiMgr :public GameNode
{





public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	UiMgr();
	~UiMgr();

};

