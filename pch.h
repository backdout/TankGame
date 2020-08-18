#pragma once

#include <Windows.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

#define TILESIZE		8 //타일 한개의 사이즈
#define SAMPLETILE_X	12 // 샘플 타일의 갯수 
#define SAMPLETILE_Y	6
#define OBJTILE_X	15 // 샘플 타일의 갯수 
#define OBJTILE_Y	11
#define TILE_X			26		// 메인 타일의 갯수
#define TILE_Y			26
//타일별 리소스 출력을 위한 구조체
typedef struct tagSampleTile
{
	RECT rcTile;
	int frameX;
	int frameY;
}SMAPLE_TILE_INFO;
//타일의 타입을 지정해주는 enum
enum TERRAIN
{
	TR_OBJ = -1,
	TR_NONE = 0,
	TR_REDBLOCK,//1
	TR_IRON,
	TR_WEED,
	TR_WATER,
	TR_ENEMY,
	TR_KING,
	TR_S_L_REDBLOCK,//7
	TR_S_R_REDBLOCK,//8
	TR_END // 이넘의 갯수을 알기위한 변수
};
typedef struct tagArg
{
	const char* sceneName;
	const char* loadingName;

}ARG_INFO;
enum BOX
{
	BOX_First,
	BOX_Second,
	BOX_End
};
enum MOVE
{
	TOP,
	LEFT,
	RIGHT,
	BOTTOM
};
typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	int objFrameX;
	int objFrameY;
	TERRAIN  terrain;
	//RECT rcCollision;

}TILE_INFO;




#define FPS			30.0f
#define WINSIZE_X	1100
#define WINSIZE_TILE_MAP_X	1100
#define WINSIZE_Y	900
#define WINSIZE_TILE_MAP_Y	900
#define WINSTART_X	50
#define WINSTART_Y	50

#define PI			3.141592

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
#include"macroFunction.h"