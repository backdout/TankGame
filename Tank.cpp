#include "Tank.h"
#include "macroFunction.h"
#include "Missile.h"

HRESULT Tank::Init()
{
	// TODO : 초기화 설명

	// 몸통
	center.x = WINSIZE_X / 2;
	center.y = WINSIZE_Y;
	bodySize = 150;

	// 포신
	barrelEnd.x = WINSIZE_X / 2;
	barrelEnd.y = center.y - 150;

	barrelAngle = PI / 4.0f;

	return S_OK;
}

void Tank::Release()
{
}

void Tank::Update()
{
	// 탱크의 키입력을 처리한다.
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		barrelAngle += (PI / 180 * 5);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		barrelAngle -= (PI / 180 * 5);
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{
		Fire();
	}

	// 포신 끝 좌표를 프레임마다 계산한다
	//cosf(barrelAngle) = barrelEnd.x / 150;
	barrelEnd.x = center.x + cosf(barrelAngle) * 150;

	//sinf(barrelAngle) = barrelEnd.y / 150;
	barrelEnd.y = center.y - sinf(barrelAngle) * 150;

	// 미사일
	for (int i = 0; i < missileMaxCount; i++)
	{
		missile[i].Update();
	}

}

void Tank::Render(HDC hdc)
{
	// 몸통
	RenderEllipseToCenter(hdc, center.x, center.y, bodySize, bodySize);

	// 포신
	RenderLine(hdc, center.x, center.y, barrelEnd.x, barrelEnd.y);

	// 미사일
	for (int i = 0; i < missileMaxCount; i++)
	{
		missile[i].Render(hdc);
	}
}

void Tank::Fire()
{
	// 먼저 확인해야 하는 내용?
	for (int i = 0; i < missileMaxCount; i++)
	{
		if (missile[i].GetIsFire() == false)
		{
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFire(true);
			missile[i].SetAngle(barrelAngle);

			if (i % 3 == 2)
			{
				missile[i].SetTarget(target);
			}

			break;
		}
	}
	//if (missile)
	//{
	//	missile->SetPos(barrelEnd);
	//	missile->SetIsFire(true);
	//	missile->SetAngle(barrelAngle);
	//}
}

Tank::Tank()
	: missileMaxCount(50)
{
	missile = new Missile[missileMaxCount];
	for (int i = 0; i < missileMaxCount; i++)
	{
		missile[i].Init();
	}

	//missile = new Missile();
	//missile->Init();
}


Tank::~Tank()
{
	delete[] missile;
	//delete missile;
}
