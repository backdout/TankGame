#pragma once
#include "GameNode.h"

class Enemy;
class Missile;
class Tank
{
private:
	POINT center;
	//int x, y;		// ��ġ ��ǥ
	// ����
	int bodySize;

	// ����
	FPOINT barrelEnd;
	float barrelAngle;			// ����	: degree(��)	0 ~ 360
								//      : radian    0.0 ~ PI * 2 (3.141592...) 

	// �̻���
	Missile* missile;
	int missileMaxCount;

	// Ÿ��
	Enemy* target;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();	
	virtual void Render(HDC hdc);

	void Fire();

	void SetTarget(Enemy* enemy) { target = enemy; }

	POINT GetCenter() { return center; }

	void SetBarrelAngle(float angle) { barrelAngle = angle; }
	float GetBarrelAngle() { return barrelAngle; }

	int GetMissileMaxCount() { return missileMaxCount; }
	Missile* GetMissileDatas() { return missile; }

	Tank();
	~Tank();
};

