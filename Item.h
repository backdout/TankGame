#pragma once
#include "GameNode.h"


class Item :public GameNode
{

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Item();
	~Item();

};
