#pragma once
#include "pch.h"
#include <list>


typedef struct tagANode
{
	int tileIndex;
	int tilePosX;
	int tilePosY;
	int x;
	int y;
	int dist;
	TERRAIN terrain;
	//A_Node_INFO pParent;

}A_Node_INFO;



class Path
{
//private:
//
//	int x;
//	int y;
//	int dist;
//	int depth;
//
//	POINT  startPos;
//	POINT  endPos;
//	A_Node_INFO pParent;
//	A_Node_INFO copyNode;
//	list<A_Node_INFO> openList;
//	list<A_Node_INFO> closeList;
//	list<A_Node_INFO> pathList;
//	list<int> pathIndexList;
//	TILE_INFO tileInfo[TILE_X* TILE_Y];
//public:
//	A_Node_INFO CopyTileinfo(int index);
//	void FindPath(int  _startTileIndex, int  _endtileIndex);
//	void SetTileInfo(TILE_INFO tileInfo)
//	{
//		for (int i = 0; i < TILE_X*TILE_Y, i++)
//		{
//			this->tileInfo[i] = tileInfo[i];
//		}
//	}
//
//	void Copy(A_Node_INFO pNode);
//	bool IsSamePos(A_Node_INFO pNode);
//	A_Node_INFO Clone();
//	static A_Node_INFO Create(int sx, int sy, int dx, int dy, int dep);
//	static A_Node_INFO Create(int sx, int sy);
//	void CalcDist(A_Node_INFO pDest, int cdepth);
//
//
//	 void SetParent(A_Node_INFO p) { pParent = p; }
//
//	 A_Node_INFO GetParent() { return pParent; }
//
//	 void Delete();
//	 bool FindPath(A_Node_INFO pStart, A_Node_INFO pEnd, ref List<A_Node_INFO> vecPath, CNavigationData pNavi);

};

