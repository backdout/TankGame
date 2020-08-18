#pragma once
#include "pch.h"

class Animation
{
private:
	vector<POINT> vecFrameList; // key frame 위치 리스트
	vector<int> vecPlayList;	// 플레이 리스트

	int frameCount;		// 전체 프레임 수
	int frameWidth;		// 프레임 가로크기
	int frameHeight;	// 프레임 세로크기

	bool isLoop;		// 반복 되는지 여부
	int nowPlayIdx;		// 현재 플레이 프레임 인덱스
	bool isPlaying;		// 현재 플레이 중인지 여부

	float keyFrameUpdateTime;	// 업데이트 기준 시간
	float accumulateTime;		// 누적 시작
public:
	Animation();
	~Animation();

	HRESULT Init(int totalwidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int* arr, int arrLength, bool isReverse = FALSE, bool isLoop = FALSE);
	// FALSE나 false나 의미상 같으니 쓰고 싶은데로 써라
	// BOOL 이나 bool도 의미상 같으니 ~
	void UpdateKeyFrame(float dt);

	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; }

	POINT GetFramePos() { return vecFrameList[vecPlayList[nowPlayIdx]]; }

	void Start();
	void Stop();
	void Pause();
	void Resume();
};

