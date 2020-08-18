#include "Path.h"

//zzzzzzzzzzzzA_Node_INFO Path::CopyTileinfo(int index)
//{
//	A_Node_INFO copy;
//	copy.tileIndex= index;
//	copy.tilePosX = index % TILE_X;
//	copy.tilePosY = index / TILE_X;
//	copy.x = tileInfo[index].rcTile.right;
//	copy.y = tileInfo[index].rcTile.bottom;
//	dist;
//	copy.terrain = tileInfo[index].terrain;
//	copy. pParent;
//	return copy
//}
//
//void Path::FindPath(int  _startTileIndex, int  _endtileIndex)
//{
//	startPos = {_startTileIndex%TILE_X ,_startTileIndex / TILE_X };
//
//	endPos = { _endtileIndex %TILE_X, _endtileIndex / TILE_X };
//
//		if (startPos.x == endPos.x && startPos.y == endPos.y)
//		{
//			return;
//		}
//		
//		openList.push_back(startPos.x)
//
//
//}z

//void Path::Copy(A_Node_INFO pNode)
//{
//	x = pNode.x;
//	y = pNode.y;
//	dist = pNode.dist;
//	depth = pNode.depth;
//	pParent = pNode.pParent;
//}
//
//bool Path::IsSamePos(A_Node_INFO pNode)
//{
//	if (x != pNode.x || y != pNode.y) return false;
//
//	return true;
//}
//
//A_Node_INFO Path::Clone()
//{
//	A_Node_INFO pNode;
//	pNode.x = x;
//	pNode.y = y;
//	pNode.dist = dist;
//	pNode.depth = depth;
//	pNode.pParent = NULL;
//	return pNode;
//}
//
//A_Node_INFO Path::Create(int sx, int sy, int dx, int dy, int dep)
//{
//	A_Node_INFO pNode;
//	pNode.x = sx;
//	pNode.y = sy;
//
//	int deltx = dx - sx;
//	int delty = dy - sy;
//	pNode.dist = (deltx * deltx) + (delty * delty);
//	pNode.depth = dep;
//
//	return pNode;
//}
//
//A_Node_INFO Path::Create(int sx, int sy)
//{
//	A_Node_INFO pNode;
//	pNode.x = sx;
//	pNode.y = sy;
//	return pNode;
//}
//
//void Path::CalcDist(A_Node_INFO pDest, int cdepth)
//{
//	int deltx = pDest.x - x;
//	int delty = pDest.y - y;
//	dist = (deltx * deltx) + (delty * delty);
//	depth = cdepth;
//}
