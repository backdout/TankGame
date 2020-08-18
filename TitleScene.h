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
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	void SetGoToCons(bool _goToCons) { goToCons = _goToCons; }
	bool GetGoToCons() {return goToCons;}

	//void ChangeScene();
	//void CloseBox();

	/*static void ChangeScene() { SceneManager::GetSingleton()->ChangeScene("��Ʋ", "�ε�1"); };
	static void CloseBox()
	{
		if (MessageBox(g_hWnd, "������ ���� �Ͻðڽ��ϱ�?", "�ȳ� �ڽ�", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};*/
	TitleScene();
	virtual ~TitleScene();
};

