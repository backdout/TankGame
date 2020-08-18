#include "Missile.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"
#include "Player_1p.h"
#include "MissileManager.h"

HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	size = 21;
	angle = 90;
	speed = 300.0f;
	isFire = false;
	adjustAngle = 0.0f;
	tileInfo= new TILE_INFO[TILE_X* TILE_Y];
	target = nullptr;

	currFrameX = currFrameY = 0;

	img = ImageManager::GetSingleton()->AddImage("bullet", "Image/bullet.bmp", pos.x, pos.y, 20, 5, 4, 1, true, RGB(0, 0, 1));
	/*test = new Player_1p;
	test->Init();*/
	isEnemy = false;
	return S_OK;
}

void Missile::Release()
{
	/*test->Release();
	SAFE_DELETE(test);

	img->Release();
	SAFE_DELETE(img);*/
}

void Missile::Update()
{
	if (isFire)
	{
		if (target)
		{
			float x = target->GetPos().x - pos.x;
			float y = target->GetPos().y - pos.y;

			float targetAngle = atan2(-y, x);

			adjustAngle += 2.0f;
			if (adjustAngle >= 100.0f)
			{
				adjustAngle = 98.0f;
			}
			angle += (targetAngle - angle) / (100.0f - adjustAngle);
		}

		pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();

		if (pos.x <= 58 || pos.x >= 880 || pos.y <= 44 || pos.y >= 840)
		{
			isFire = false;
		}


		rcMi = GetRect(pos.x, pos.y,  5 * 5);
		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (tileInfo[i].terrain == 1|| tileInfo[i].terrain == TR_KING|| tileInfo[i].terrain == TR_IRON)
			{
				if (CheckRectCollision(tileInfo[i].rcTile, rcMi))
				{
					//this->pos = { 0,0 };
					isFire = false;
					if (!(tileInfo[i].terrain == TR_IRON))
					{
						tileInfo[i].frameX = 0;
						tileInfo[i].frameY = 0;
						tileInfo[i].terrain = TR_NONE;
					}
					break;
				}

			}

		}


		if (isEnemy)
		{
		
			if (CheckRectCollision(tank->GetTankRect(), rcMi))
			{
				isFire = false;
				//this->pos = { 0,0 };
				tank->SetIshit(true);
			}

		
	
		}

	}

}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		if (img)
		{
			img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 5.0f);
		}
		//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}