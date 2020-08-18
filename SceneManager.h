#pragma once
#include "SingletonBase.h"
#include <Windows.h>
#include <map>

using namespace std;

class GameNode;
class SceneManager : public SingletonBase<SceneManager>	// �̱��� ���̽��� ��ӹ޾Ƽ� �ŸŴ����� �Ѱ��ش�
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;
	//static���� : �޸𸮰� ������ ������ ���������� �������� �ʴ´�. 
				// ���������� �ٸ����� scenemanager��������� ����ֱ⶧���� �����Ҷ� ����� �ٸ���.
	
public:
	static GameNode* currentScene;
	static GameNode* loadingScene;
	static GameNode* readyScene;

	HRESULT Init();			//virtual�� �Ⱦ����� GameNode�� ��ӹ��� �ʾƼ�.
	void Release();	
	void Update();	
	void Render(HDC hdc);	
	
	//�� �߰�
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadScene(string key, GameNode* scene);

	//�� ü����
	HRESULT ChangeScene(string sceneName);	// ���� �ٲٴ°�
	HRESULT ChangeScene(string sceneName, bool goToCons);	// ���� �ٲٴ°�
	
	HRESULT LoadingChangeScene(string sceneName, string loadingSceneName);	//���̶� �ε����̶� ���� ����ϴ°�
	HRESULT LoadingChangeScene(string sceneName, string loadingSceneName, bool goToCons);

	SceneManager();
	virtual ~SceneManager();
};

