#include "Construction.h"
#include "Image.h"
#include "macroFunction.h"
#include "Button.h"

HRESULT Construction::Init()
{
	
	minX = 0;
	maxX = 0;
	minY = 0;
	maxY = 0;
	dragSizeX = 0;
	dragSizeY = 0;
	scale = 4.0f;
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/tileMap.bmp", 0, 0, 96, 48, SAMPLETILE_X, SAMPLETILE_Y);
	bgImg = ImageManager::GetSingleton()->AddImage("BattleBG", "Image/bg.bmp", 0, 0, 1100, 900, 1, 1);
	tankImg = ImageManager::GetSingleton()->AddImage("1PTank", "Image/userTank.bmp", 0, 0, 152, 152, 8, 8, true, RGB(0, 0, 1));
	
	for (int i = 0; i < SAMPLETILE_Y; i++)
	{
		for (int j = 0; j < SAMPLETILE_X; j++)
		{
			sampleTileInfo[i*SAMPLETILE_X + j].frameX = j;
			sampleTileInfo[i*SAMPLETILE_X + j].frameY = i;
			SetRect(&sampleTileInfo[i*SAMPLETILE_X + j].rcTile,
				WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth() + j * TILESIZE, i*TILESIZE, WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth() + j * TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}
	
	// 왼쪽 타일  렉트 설정
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{

			SetRect(&tileInfo[i*TILE_X + j].rcTile,
				 j * TILESIZE*scale + 68, i*TILESIZE*scale + 34,  j * TILESIZE*scale + 68+ TILESIZE* scale,
				i*TILESIZE*scale + 34 + TILESIZE* scale);
		}
	}


	// 왼쪽에 그려질 내용을 초기화 한다. ( 기본 설정)
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		tileInfo[i].frameX = 0;
		tileInfo[i].frameY = 0;
		tileInfo[i].terrain = TR_NONE;
	}

	tank.posX = 0;
	tank.posY = 0;
	tank.isSelect = true;

	POINT upFramePoint = { 0, 0 };
	POINT downFramePoint = { 0, 1 };
	Load();


	return S_OK;
}

void Construction::Release()
{

}

void Construction::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RETURN))
	{
		Save();
		SceneManager::GetSingleton()->ChangeScene("타이틀");
		return;	//체인지되며 밑에있는 애들 랜더 안시키기위해
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('R'))
	{
		Load();
	}



	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
	{
		if (tank.posX == 0) tank.posX = 0;
		else tank.posX-=2;
		tank.isSelect = false;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
	{
		if (tank.posX >= TILE_X-2) tank.posX = TILE_X-2;
		else tank.posX += 2;
		tank.isSelect = false;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
	{
		if (tank.posY == 0)tank.posY = 0;
		else tank.posY-=2;
		tank.isSelect = false;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
	{
		if (tank.posY >= TILE_Y-2)tank.posY = TILE_Y-2;
		else tank.posY+=2;
		tank.isSelect = false;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp('Z'))
	{
		if (tileInfo[tank.posX + (tank.posY * TILE_X)].terrain < 5)
		{
			if (tank.isSelect)
			{
			
				if (tank.frameX == 10 && !(tileInfo[tank.posX + (tank.posY * TILE_X)].frameY == 4))
				{
					tank.frameX = 0; tank.frameY += 2;
					tank.tankTerrain = static_cast<TANKTERRAIN>(tank.tankTerrain + 1);
				}
				else if (tileInfo[tank.posX + (tank.posY * TILE_X)].frameY == 4)
				{
					tank.frameY = 0; tank.frameX = 0;
					tank.tankTerrain = static_cast<TANKTERRAIN>(0);
				}
				else
				{
					tank.frameX += 2;
					tank.tankTerrain = static_cast<TANKTERRAIN>(tank.tankTerrain + 1);
				}
			}
			else
			{
				tank.isSelect = true;
			}
		
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{

					{
						tileInfo[tank.posX + (tank.posY * TILE_X) + (y* TILE_X) + x].frameX = tank.frameX + x;
						tileInfo[tank.posX + (tank.posY * TILE_X) + (y* TILE_X) + x].frameY = tank.frameY + y;
						ChangeTerrain(tank.tankTerrain);
					}

				}
			}
		}
	
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		if (tileInfo[tank.posX + (tank.posY * TILE_X)].terrain < 5)
		{
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{

					{
						tileInfo[tank.posX + (tank.posY * TILE_X) + (y* TILE_X) + x].frameX = tank.frameX + x;
						tileInfo[tank.posX + (tank.posY * TILE_X) + (y* TILE_X) + x].frameY = tank.frameY + y;
						ChangeTerrain(tank.tankTerrain);
					}

				}
			}
		}
	}



}

void Construction::Render(HDC hdc)
{

	PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_Y, BLACKNESS);
	bgImg->Render(hdc,0,0);
	// 샘플 렌더 
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{

			{
				sampleTileImage->FrameRender(hdc, 1000+(32*x), 200+ (y * 32), tank.frameX+x, tank.frameY+y, scale);

			}

		}
	}
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		 sampleTileImage->FrameRender(hdc, tileInfo[i].rcTile.left + (TILESIZE / 2), tileInfo[i].rcTile.top + (TILESIZE / 2), tileInfo[i].frameX, tileInfo[i].frameY, scale);
		 /*if (tileInfo[i].terrain == TR_OBJ)
			 objTileImage->FrameRender(hdc, tileInfo[i].rcTile.left + (TILESIZE / 2)+68, tileInfo[i].rcTile.top + (TILESIZE / 2)+34, tileInfo[i].objFrameX, tileInfo[i].objFrameY, scale);*/
	}

	if(tankImg) tankImg->FrameRender(hdc, tileInfo[tank.posX + (tank.posY*(TILE_X))].rcTile.left + (TILESIZE / 2)-2, tileInfo[tank.posX + (tank.posY*(TILE_X))].rcTile.top + (TILESIZE / 2)-6, 1, 1, 4.0f);

	
}

void Construction::Save()
{
		DWORD writtenByte;
		HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);

}

void Construction::Load()
{
	DWORD readByte;
	HANDLE hFile = CreateFile("Save/load.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
	CloseHandle(hFile);

}

void Construction::Reset()
{

}

void Construction::ChangeTerrain(TANKTERRAIN tankTerrain)
{
	switch (tankTerrain)
	{
	case TTR_OBJ:
		break;
	case TTR_NONE:
		break;
	case TTR_R_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0* TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0* TILE_X) + 1].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1* TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1* TILE_X) + 1].terrain = TR_REDBLOCK;
		break;
	case TTR_L_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
		break;
	case TTR_U_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
		break;
	case TTR_D_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
		break;
	case TTR_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
		break;
	case TTR_R_IRON:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
		break;
	case TTR_L_IRON:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
		break;
	case TTR_U_IRON:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
		break;
	case TTR_D_IRON:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
		break;
	case TTR_IRON:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
		break;
	case TTR_WEED:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_WEED;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_WEED;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_WEED;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_WEED;
		break;
	case TTR_WATER:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_WATER;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_WATER;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_WATER;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_WATER;
		break;
	case TTR_ENEMY:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_ENEMY;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_ENEMY;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_ENEMY;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_ENEMY;
		break;
	case TTR_KING:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_KING;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_KING;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_KING;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_KING;
		break;
	case TTR_S_L_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
		break;
	case TTR_S_R_REDBLOCK:
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
		tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
		break;
	case TTR_END:
		break;
	default:
		break;
	}
}

//void Construction::ChangeRect()

	//오른쪽
	//if (tank.terrain == 1 && tank.terrain == 6)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + ((TILESIZE/2) * scale), tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	////왼쪽
	//if (tank.terrain == 2 && tank.terrain == 7)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left, tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + ((TILESIZE / 2) * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	////위에가 빈
	//if (tank.terrain == 3 && tank.terrain == 8)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left , tileInfo[tank.posY * TILE_X + tank.posX].rcTile.top + ((TILESIZE / 2) * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + (TILESIZE  * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	//if (tank.terrain == 4 && tank.terrain == 9)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left , tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + ((TILESIZE / 2) * scale));
	//}
	//if (tank.terrain == 5 && tank.terrain == 10)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left, tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}



Construction::Construction()
{
}

Construction::~Construction()
{
}
