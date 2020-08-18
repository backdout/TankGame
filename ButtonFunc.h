#pragma once
#include "GameNode.h"
#include"pch.h"

class ButtonFunc : public GameNode
{
public:


	// 주로 스택틱 함수나 전역 함수로 사용 ; ( 번잡 스러워서;
	static void ChangeScene() { SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1"); };
	static void QuitProgram()
	{
		if (MessageBox(g_hWnd, "게임을 종료 하시겠습니까?", "안내 박스", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};

	void ChangeScene1() { SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1"); };
	void QuitProgram1()
	{
		if (MessageBox(g_hWnd, "게임을 종료 하시겠습니까?", "안내 박스", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};



	void ChangeScene2(const char* filename, const char* filename2) { SceneManager::GetSingleton()->ChangeScene(filename, filename2); };
	void QuitProgram2()
	{
		if (MessageBox(g_hWnd, "게임을 종료 하시겠습니까?", "안내 박스", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};

	ButtonFunc() {};
	~ButtonFunc() {};
};


