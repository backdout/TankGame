#pragma once
#include "pch.h"

class GameNode
{
protected:
	FPOINT pos;

public:
	virtual HRESULT Init();		
	virtual HRESULT Init(bool goToCons);	// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		   // �޸� ����
	virtual void Update();		   // ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT _pos) {  pos= _pos; }

	GameNode();
	~GameNode();
};

