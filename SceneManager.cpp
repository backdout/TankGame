#include "SceneManager.h"
#include "GameNode.h"

//게임노드의 포인터타입이 씬매니저의 커런트타입을 초기화한다(초기화 오류안생김)(안해주면 문법상 오류)
GameNode* SceneManager::currentScene = nullptr;	
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	//쓰레드 종료 시점(방법)
	/*
		1. 호출된 함수가 반환될 때 (우리가 사용할 방법)
		2. 호출된 함수 내부에서 ExitThread()를 호출했을 때
		3. 동일한 프로세스나 다른 프로세스 TerminateThread()를 호출했을 때
		4. 현재 쓰레드가 포함된 프로세스가 종료될 때
	*/

	SceneManager::readyScene->Init();
	SceneManager::currentScene = SceneManager::readyScene;
	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}
DWORD CALLBACK LoadingThread2(LPVOID pvParam,bool isgoto)
{
	//쓰레드 종료 시점(방법)
	/*
		1. 호출된 함수가 반환될 때 (우리가 사용할 방법)
		2. 호출된 함수 내부에서 ExitThread()를 호출했을 때
		3. 동일한 프로세스나 다른 프로세스 TerminateThread()를 호출했을 때
		4. 현재 쓰레드가 포함된 프로세스가 종료될 때
	*/

	SceneManager::readyScene->Init(isgoto);
	SceneManager::currentScene = SceneManager::readyScene;
	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}
											// TitleScene과 BattleScene이 들어온다
GameNode * SceneManager::AddScene(string key, GameNode * scene)
{	
	if (scene == nullptr)
		return nullptr;
					//pair:map안에 들어가는 요소의 타입(map이랑 형태가 같아야함) (Key랑Scene을 넣어 초기화한다)
	mapSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

GameNode * SceneManager::AddLoadScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*>::iterator it;
	it = mapSceneDatas.find(sceneName);
	//find return type : iterator
	mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())	return E_FAIL;	//없으면 Scene체인지에 실패

	if (it->second == currentScene) return S_OK;

		//iterator에 Second에서 Init해주고 (바꾸려는 Scene)
	if (SUCCEEDED(it->second->Init()))	//성공했을때
	{
		if (currentScene) // 현재Scene이 있을때
		{
			currentScene->Release();
		}

		currentScene = it->second;
		return S_OK;
	}
	

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, bool goToCons)
{
	map<string, GameNode*>::iterator it;
	it = mapSceneDatas.find(sceneName);
	//find return type : iterator
	mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())	return E_FAIL;	//없으면 Scene체인지에 실패

	if (it->second == currentScene) return S_OK;

	//iterator에 Second에서 Init해주고 (바꾸려는 Scene)
	if (SUCCEEDED(it->second->Init(goToCons)))	//성공했을때
	{
		if (currentScene) // 현재Scene이 있을때
		{
			currentScene->Release();
		}

		currentScene = it->second;
		return S_OK;
	}


	return E_FAIL;
}

HRESULT SceneManager::LoadingChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameNode*>::iterator it;
	it = mapSceneDatas.find(sceneName);

	mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())	return E_FAIL;

	if (it->second == currentScene) return S_OK;

	// change 중간에 들어갈 LoadingScene
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())	// LoadingScene이 없으면~
	{
		return ChangeScene(sceneName);	// return을 해줘야 밑에 있는 내용들 진행안되고 끝난다.
	}

	if (SUCCEEDED(itLoading->second->Init()))				// LoadingScene이 있으면~
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		readyScene = it->second;	// stand by시켜둠
		loadingScene = itLoading->second;

		currentScene = loadingScene;	//itLoading->second를 넣어도 상관없다

		// 멀티쓰레드로 change할 mainScene을 초기화한다.
		HANDLE hThread;
		DWORD loadThreadID;
		//hThread = CloseHandle(CreateThread(NULL, 0, func, NULL, 0, &loadThreadID));
		//CloseHandle(hThread);


		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThreadID));
		return S_OK;
	}
	return S_OK;
}

HRESULT SceneManager::LoadingChangeScene(string sceneName, string loadingSceneName, bool goToCons)
{
	map<string, GameNode*>::iterator it;
	it = mapSceneDatas.find(sceneName);

	mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())	return E_FAIL;

	if (it->second == currentScene) return S_OK;

	// change 중간에 들어갈 LoadingScene
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())	// LoadingScene이 없으면~
	{
		return ChangeScene(sceneName, goToCons);	// return을 해줘야 밑에 있는 내용들 진행안되고 끝난다.
	}

	if (SUCCEEDED(itLoading->second->Init()))	// LoadingScene이 있으면~
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		readyScene = it->second;	// stand by시켜둠
		loadingScene = itLoading->second;

		currentScene = loadingScene;	//itLoading->second를 넣어도 상관없다

		// 멀티쓰레드로 change할 mainScene을 초기화한다.
		HANDLE hThread;
		DWORD loadThreadID;
		//hThread = CloseHandle(CreateThread(NULL, 0, func, NULL, 0, &loadThreadID));
		//CloseHandle(hThread);


		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThreadID));
		return S_OK;
	}
	return S_OK;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
