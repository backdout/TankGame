#include "Tank.h"
#include "macroFunction.h"
#include "Missile.h"

HRESULT Tank::Init()
{
	// TODO : �ʱ�ȭ ����

	// ����
	center.x = WINSIZE_X / 2;
	center.y = WINSIZE_Y;
	bodySize = 150;

	// ����
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
	// ��ũ�� Ű�Է��� ó���Ѵ�.
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

	// ���� �� ��ǥ�� �����Ӹ��� ����Ѵ�
	//cosf(barrelAngle) = barrelEnd.x / 150;
	barrelEnd.x = center.x + cosf(barrelAngle) * 150;

	//sinf(barrelAngle) = barrelEnd.y / 150;
	barrelEnd.y = center.y - sinf(barrelAngle) * 150;

	// �̻���
	for (int i = 0; i < missileMaxCount; i++)
	{
		missile[i].Update();
	}

}

void Tank::Render(HDC hdc)
{
	// ����
	RenderEllipseToCenter(hdc, center.x, center.y, bodySize, bodySize);

	// ����
	RenderLine(hdc, center.x, center.y, barrelEnd.x, barrelEnd.y);

	// �̻���
	for (int i = 0; i < missileMaxCount; i++)
	{
		missile[i].Render(hdc);
	}
}

void Tank::Fire()
{
	// ���� Ȯ���ؾ� �ϴ� ����?
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
