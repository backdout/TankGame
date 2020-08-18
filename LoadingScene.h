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
	Animation* ani;	// Camel 애니메이션
	HFONT hFont, hOldFont;
	HBRUSH hBrush, hOldBrush;
	int percent;
	//Image* BHP;

public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetPercent(int _percent) { percent = _percent; }
	LoadingScene();
	~LoadingScene();
};

