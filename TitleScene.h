#pragma once
#include "GameNode.h"
#include "pch.h"
class Button;
class ButtonFunc;
class TitleScene : public GameNode
{
private:
	Image* bg;
	Image* tank;
	Image* loading;


	Button* bt1;
	Button* bt2;
	ButtonFunc* btFunc;
	int tankFramY[2] = {675, 732};
	int tankFramYIndex;
	ARG_INFO* args;
	ARG_INFO* args2;

	bool isInit;
	bool isTile;
	bool isBattle;
	float loadingTime;

	bool isLoading;
	bool goToCons;


public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)


	void SetGoToCons(bool _goToCons) { goToCons = _goToCons; }
	bool GetGoToCons() {return goToCons;}

	//void ChangeScene();
	//void CloseBox();

	/*static void ChangeScene() { SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1"); };
	static void CloseBox()
	{
		if (MessageBox(g_hWnd, "게임을 종료 하시겠습니까?", "안내 박스", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};*/
	TitleScene();
	virtual ~TitleScene();
};

