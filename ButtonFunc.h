#pragma once
#include "GameNode.h"
#include"pch.h"

class ButtonFunc : public GameNode
{
public:


	// �ַ� ����ƽ �Լ��� ���� �Լ��� ��� ; ( ���� ��������;
	static void ChangeScene() { SceneManager::GetSingleton()->ChangeScene("��Ʋ", "�ε�1"); };
	static void QuitProgram()
	{
		if (MessageBox(g_hWnd, "������ ���� �Ͻðڽ��ϱ�?", "�ȳ� �ڽ�", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};

	void ChangeScene1() { SceneManager::GetSingleton()->ChangeScene("��Ʋ", "�ε�1"); };
	void QuitProgram1()
	{
		if (MessageBox(g_hWnd, "������ ���� �Ͻðڽ��ϱ�?", "�ȳ� �ڽ�", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};



	void ChangeScene2(const char* filename, const char* filename2) { SceneManager::GetSingleton()->ChangeScene(filename, filename2); };
	void QuitProgram2()
	{
		if (MessageBox(g_hWnd, "������ ���� �Ͻðڽ��ϱ�?", "�ȳ� �ڽ�", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	};

	ButtonFunc() {};
	~ButtonFunc() {};
};


