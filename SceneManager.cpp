#include "SceneManager.h"
#include "GameNode.h"

//���ӳ���� ������Ÿ���� ���Ŵ����� Ŀ��ƮŸ���� �ʱ�ȭ�Ѵ�(�ʱ�ȭ �����Ȼ���)(�����ָ� ������ ����)
GameNode* SceneManager::currentScene = nullptr;	
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	//������ ���� ����(���)
	/*
		1. ȣ��� �Լ��� ��ȯ�� �� (�츮�� ����� ���)
		2. ȣ��� �Լ� ���ο��� ExitThread()�� ȣ������ ��
		3. ������ ���μ����� �ٸ� ���μ��� TerminateThread()�� ȣ������ ��
		4. ���� �����尡 ���Ե� ���μ����� ����� ��
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
	//������ ���� ����(���)
	/*
		1. ȣ��� �Լ��� ��ȯ�� �� (�츮�� ����� ���)
		2. ȣ��� �Լ� ���ο��� ExitThread()�� ȣ������ ��
		3. ������ ���μ����� �ٸ� ���μ��� TerminateThread()�� ȣ������ ��
		4. ���� �����尡 ���Ե� ���μ����� ����� ��
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
											// TitleScene�� BattleScene�� ���´�
GameNode * SceneManager::AddScene(string key, GameNode * scene)
{	
	if (scene == nullptr)
		return nullptr;
					//pair:map�ȿ� ���� ����� Ÿ��(map�̶� ���°� ���ƾ���) (Key��Scene�� �־� �ʱ�ȭ�Ѵ�)
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

	if (it == mapSceneDatas.end())	return E_FAIL;	//������ Sceneü������ ����

	if (it->second == currentScene) return S_OK;

		//iterator�� Second���� Init���ְ� (�ٲٷ��� Scene)
	if (SUCCEEDED(it->second->Init()))	//����������
	{
		if (currentScene) // ����Scene�� ������
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

	if (it == mapSceneDatas.end())	return E_FAIL;	//������ Sceneü������ ����

	if (it->second == currentScene) return S_OK;

	//iterator�� Second���� Init���ְ� (�ٲٷ��� Scene)
	if (SUCCEEDED(it->second->Init(goToCons)))	//����������
	{
		if (currentScene) // ����Scene�� ������
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

	// change �߰��� �� LoadingScene
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())	// LoadingScene�� ������~
	{
		return ChangeScene(sceneName);	// return�� ����� �ؿ� �ִ� ����� ����ȵǰ� ������.
	}

	if (SUCCEEDED(itLoading->second->Init()))				// LoadingScene�� ������~
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		readyScene = it->second;	// stand by���ѵ�
		loadingScene = itLoading->second;

		currentScene = loadingScene;	//itLoading->second�� �־ �������

		// ��Ƽ������� change�� mainScene�� �ʱ�ȭ�Ѵ�.
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

	// change �߰��� �� LoadingScene
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())	// LoadingScene�� ������~
	{
		return ChangeScene(sceneName, goToCons);	// return�� ����� �ؿ� �ִ� ����� ����ȵǰ� ������.
	}

	if (SUCCEEDED(itLoading->second->Init()))	// LoadingScene�� ������~
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		readyScene = it->second;	// stand by���ѵ�
		loadingScene = itLoading->second;

		currentScene = loadingScene;	//itLoading->second�� �־ �������

		// ��Ƽ������� change�� mainScene�� �ʱ�ȭ�Ѵ�.
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
