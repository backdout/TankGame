#pragma once
#include "SingletonBase.h"
#include <Windows.h>
#include <map>

using namespace std;

class GameNode;
class SceneManager : public SingletonBase<SceneManager>	// 싱글톤 베이스를 상속받아서 신매니저를 넘겨준다
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;
	//static쓸때 : 메모리가 시작할 때부터 끝날때까지 해제되지 않는다. 
				// 전역변수와 다른점은 scenemanager멤버변수로 들어있기때문에 접근할때 방법이 다르다.
	
public:
	static GameNode* currentScene;
	static GameNode* loadingScene;
	static GameNode* readyScene;

	HRESULT Init();			//virtual을 안쓴이유 GameNode를 상속받지 않아서.
	void Release();	
	void Update();	
	void Render(HDC hdc);	
	
	//씬 추가
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadScene(string key, GameNode* scene);

	//씬 체인지
	HRESULT ChangeScene(string sceneName);	// 씬만 바꾸는거
	HRESULT ChangeScene(string sceneName, bool goToCons);	// 씬만 바꾸는거
	
	HRESULT LoadingChangeScene(string sceneName, string loadingSceneName);	//씬이랑 로딩씬이랑 같이 출력하는것
	HRESULT LoadingChangeScene(string sceneName, string loadingSceneName, bool goToCons);

	SceneManager();
	virtual ~SceneManager();
};

