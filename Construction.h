#pragma once
#include "GameNode.h"
#include "pch.h"

//640*288  20*9(32*32)

enum TANKTERRAIN
{
	//TTR_GRASS,
	TTR_OBJ = -1,
	TTR_NONE = 0,
	TTR_R_REDBLOCK,//1
	TTR_L_REDBLOCK,//2
	TTR_U_REDBLOCK,//3
	TTR_D_REDBLOCK,//4
	TTR_REDBLOCK,//5 //1
	TTR_R_IRON,//6
	TTR_L_IRON,//7
	TTR_U_IRON,//8
	TTR_D_IRON,//9
	TTR_IRON,//10//2
	TTR_WEED,//11//3
	TTR_WATER,//12//4
	TTR_ENEMY,//13//5
	TTR_KING,//14//6
	TTR_S_L_REDBLOCK,//15//7
	TTR_S_R_REDBLOCK,//16//8
	TTR_END // �̳��� ������ �˱����� ����
};


typedef struct tagSelectTile
{

	//RECT rcTile;
	int frameX;
	int frameY;
	TERRAIN  terrain;

}SELECT_TILE_INFO;

typedef struct tagTank
{

	RECT rcTile;
	int frameX;
	int frameY;
	int posX;
	int posY;
	bool isSelect;
	TERRAIN  terrain;
	TANKTERRAIN  tankTerrain;
}Tank_INFO;


class Button;
class Image;
class Construction :public GameNode
{
private:
	Image* sampleTileImage;
	Image* objTileImage;
	Image* tankImg;
	Image* bgImg;

	Button*		saveButton;
	Button*		loadButton;
	Button*		mapOrObjButton;
	// ���� Ÿ���� ����-> ���������� ����Ʈ��  �����ϱ� ���� ��Ʈ ����  ( ����ü �迭�� ����)
	SMAPLE_TILE_INFO sampleTileInfo[SAMPLETILE_X* SAMPLETILE_Y];

	//objectTile
	SMAPLE_TILE_INFO objTileInfo[OBJTILE_X* OBJTILE_Y];

	//���� Ÿ���� ���� -> ��Ʈ ���� / ���� Ÿ���� ���� ������ ����Ʈ /Ÿ���� �Ӽ�
	TILE_INFO tileInfo[TILE_X* TILE_Y];
	
	//TILE_INFO tempInfo''
	// ���õ� Ÿ���� ���� (���� Ÿ�Ͽ��� ) -> ���� ������ ���� 
	Tank_INFO tank;
	SELECT_TILE_INFO selectTileInfo;
	SELECT_TILE_INFO selectTileInfos[2];
	RECT totalTileSize;
	//���̺� �ε� 


	float scale;

	bool isDownSample;
	int minX, minY, maxX, maxY;
	int dragSizeX ;
	int dragSizeY ;


public:
	virtual HRESULT Init() override;
	virtual void Release()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();
	void Reset();
	void ChangeTerrain(TANKTERRAIN  tankTerrain);

	Construction();
	~Construction();
};


