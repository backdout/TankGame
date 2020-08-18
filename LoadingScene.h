#pragma once
#include "GameNode.h"

class Animation;
class LoadingScene : public GameNode
{
private:
	Image* stage1;
	Image* stage2;
	Image* stage3;
	Image* stage4;
	Animation* playAni;
	Animation* ani;	// Camel �ִϸ��̼�
	HFONT hFont, hOldFont;
	HBRUSH hBrush, hOldBrush;
	int percent;
	//Image* BHP;

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetPercent(int _percent) { percent = _percent; }
	LoadingScene();
	~LoadingScene();
};

