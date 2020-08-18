#include "Animation.h"

Animation::Animation()
	:frameCount(0)
	, frameWidth(0)
	, frameHeight(0)
	, isLoop(false)
	, nowPlayIdx(0)
	, isPlaying(false)	// {}안에 해주나 밖에 해주나 사실상 차이 거의 없음
	, keyFrameUpdateTime(0)
	, accumulateTime(0.0f)
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalwidth, int totalHeight, int frameWidth, int frameHeight)
{
	// 가로 프레임 수
	int frameWidthCount = totalwidth / frameWidth;
	// 세로 프레임 수
	int frameHeightCount = totalHeight / frameHeight;
	// 전체 프레임 수
	frameCount = frameWidthCount * frameHeightCount;

	// 프레임 위치 리스트 셋팅
	vecFrameList.clear();
	vecFrameList.resize(frameCount);

	for (int i = 0; i < frameHeightCount; i++)
	{
		for (int j = 0; j < frameWidthCount; j++)
		{

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			/*
			POINT framePos;

			framePos.x = j * frameWidth;
			framePos.y = i * frameHeight;

			vecFrameList[i * frameWidthCount + j] = framePos;

			위아래 둘다 같음

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			vecFrameList[i * frameWidthCount + j] = framePos;
			*/
		}
	}
	// 기본 플레이 리스트 셋팅

	return E_NOTIMPL;
}

void Animation::SetPlayFrame(bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		// 정방향
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);	// pushback으로 인덱스 번호를 집어 넣자. 플레이리스트 0번부터 11번까지 진행되는거
		}
		// 역방향
		for (int i = frameCount - 1; i > 0; i--)
		{
			vecPlayList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}
	}
}

void Animation::SetPlayFrame(int startFrame, int endFrame, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	// startFrame 이 0보다 크거나 같고 endFrame이 마지막 Frame보다 작거나 같을 때
	// startFrame = 8 endFrame = 3 인 경우
	if (startFrame == endFrame)	// 정지되어있는 애니메이션
	{
		Stop();					// 스탑함수 호출한뒤에
		return;					// 리턴 시킨다.
	}

	if (startFrame > endFrame)	// 첫시작이 마지막보다 클때
	{
		if (isReverse)
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}
			for (int i = 0; i <= endFrame; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = endFrame; i >= 0; i--)
			{
				vecPlayList.push_back(i);
			}
			for (int i = frameCount - 1; i >= startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}
			for (int i = 0; i <= endFrame; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
	else
	{
		if (isReverse)
		{
			// 정방향
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);	// pushback으로 인덱스 번호를 집어 넣자. 플레이리스트 0번부터 11번까지 진행되는거
			}
			// 역방향
			for (int i = endFrame - 1; i > startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{									// + 1을 해줘야 endFrame까지 들어가진다.
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
}

void Animation::SetPlayFrame(int * arr, int arrLength, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
		for (int i = arrLength - 1; i >= 0; i--)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
}

void Animation::UpdateKeyFrame(float dt)
{
	if (isPlaying)
	{
		accumulateTime += dt;

		if (accumulateTime >= keyFrameUpdateTime)
		{
			nowPlayIdx++;

			if (nowPlayIdx >= vecPlayList.size())	// 셋팅해놓은 애니메이션이 다 끝았을때
			{
				//루프일 때
				if (isLoop)
				{
					nowPlayIdx = 0;
				}
				else
				{
					nowPlayIdx--;
					isPlaying = false;
				}
			}
			accumulateTime -= keyFrameUpdateTime;
			//accumulateTime -= 0.0f;	자세한 처리가 가능해짐
		}
	}

}

void Animation::Start()
{
	nowPlayIdx = 0;
	isPlaying = true;
}

void Animation::Stop()
{
	nowPlayIdx = 0;
	isPlaying = false;
}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Resume()
{
	isPlaying = true;
}