#include "Astar.h"

// Astar 내부의 클래스

Astar::Node::Node()
{

}

Astar::Node::Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint)
{
	point.x = _x;
	point.y = _y;
	pParent = _pParent;
	end = _EndPoint;

	if (pParent == NULL) // 부모가 없는 경우
	{
		G = 0;
	}
	else if ( // 십자 방향인 경우
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y) || // 부모가 '상'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y) || // 부모가 '하'방향에 있거나
		(pParent->point.x == point.x && pParent->point.y == point.y - 1) || // 부모가 '좌'방향에 있거나
		(pParent->point.x == point.x && pParent->point.y == point.y + 1)) // 부모가 '우'방향에 있으면		
	{
		G = pParent->G + 10;
	}
	else if ( // 대각선 방향인 경우
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y - 1) || // 부모가 '좌상'방향에 있거나
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y + 1) || // 부모가 '우상'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y - 1) || // 부모가 '좌하'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y + 1)) // 부모가 '우하'방향에 있으면
	{
		G = pParent->G + 14;
	}
	else {
		//cout << " 부모 설정 오류 " << endl;
		F = -100000;  H = -100000; G = -100000;
	}

	H = (abs(end.x - point.x) + abs(end.y - point.y)) * 10;

	F = G + H;
}

Astar::Node::~Node()
{

}

Astar::Map::Map()
{// 맵의 크기를 불러옴
	char csizeX[4], csizeY[4];
	sizeX = 14; sizeY = 14;

	DWORD readByte;
	HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
	CloseHandle(hFile);

	map = new int*[sizeX]; // 행 할당
	for (int i = 0; i < sizeX; i++) // 열 할당
	{
		map[i] = new int[sizeY];
	}
	for (int i = 0; i < sizeY ; i++)
	{
		for (int j = 0; j < sizeX ; j++)
		{
			//map[j][i] = tileInfo[i + (j* TILE_X)].terrain;
			if (!(tileInfo[(i*2) + ((j*2)*TILE_X)].terrain == 0 ||
				tileInfo[(i * 2) + ((j * 2)*TILE_X)].terrain == 3 ||
				tileInfo[(i * 2) + ((j * 2)*TILE_X)].terrain == 5)||
				!(tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 0 ||
				tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 3 || 
				tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 5)||
				!(tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 0 
				|| tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 3
				|| tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 5)||
				!(tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 0 
					|| tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 3 
					|| tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 5))
			{	
				map[i][j] = 1; 
			}
			else
			{
				map[i][j] = 0;// continue;
			}
		}
	}

}

//Astar::Map::Map(const char * fileName)
//{
//
//	char csizeX[4], csizeY[4];
//	//GetPrivateProfileStringA("MAP", "sizeX", "", csizeX, sizeof(csizeX) - 1, "../Data/Map.txt");
//	//GetPrivateProfileStringA("MAP", "sizeY", "", csizeY, sizeof(csizeY) - 1, "../Data/Map.txt");
//	sizeX = 14; sizeY = 14;
//
//	DWORD readByte;
//	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
//	CloseHandle(hFile);
//	
//
//	map = new int*[sizeX]; // 행 할당
//	for (int i = 0; i < sizeX; i++) // 열 할당
//	{
//		map[i] = new int[sizeY];
//	}
//
//	for (int i = 0; i < sizeY; i++)
//	{
//		for (int j = 0; j < sizeX; j++)
//		{
//			//map[j][i] = tileInfo[i + (j* TILE_X)].terrain;
//			//0,0
//			if (!(tileInfo[(i * 2) + ((j * 2)*TILE_X)].terrain == 0 || tileInfo[(i * 2) + ((j * 2)*TILE_X)].terrain == 3 || tileInfo[(i * 2) + ((j * 2)*TILE_X)].terrain == 5) ||
//				!(tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 0 || tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 3 || tileInfo[i * 2 + (((j * 2) + 1)*TILE_X)].terrain == 5) ||
//				!(tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 0 || tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 3 || tileInfo[((i * 2) + 1) + ((j * 2) *TILE_X)].terrain == 5) ||
//				!(tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 0 || tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 3 || tileInfo[((i * 2) + 1) + (((j * 2) + 1)*TILE_X)].terrain == 5))
//			{
//
//				map[i][j] = 1;
//			}
//			else
//			{
//				map[i][j] = 0;// continue;
//			}
//
//
//		}
//	}
//
//
//}

void Astar::Map::Copy(Map* _map)
{
	// 맵 크기 복사
	sizeX = _map->sizeX;
	sizeY = _map->sizeY;

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			map[i][j] = _map->map[i][j];
		}
	}
}

void Astar::Map::Copy(TILE_INFO* _tileInfo)
{
	sizeX = TILE_X;
	sizeY = TILE_Y;

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			map[j][i] = _tileInfo[i+(j* TILE_X)].terrain;
		}
	}


}

Astar::Map::~Map()
{
	for (int i = 0; i < sizeX; i++)
	{
		delete[] map[i]; // 맵의 열 동적할당 해제, 열은 행의 갯수만큼 동적할당 되었으므로 sizeX만큼 반복
	}
	delete[] map; // 맵의 행 동적할당 해제
}

void Astar::Map::PrintMap()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			//printf("%d ", map[i][j]);
		}
		//printf("\n");
	}
}




// Astar 내부의 함수
list<Astar::Coordinate*> Astar::FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint) // Map 은 동적할당했기 때문에 얕은 복사 시 에러
{
	// (상,우,하,좌) 4방향 시계방향 탐색 후 결과에 따라 (우상,우하,좌하,좌상) 탐색.	
	list<Node*> OpenNode; // 열린노드
	list<Node*> CloseNode; // 닫힌노드
	Node* SNode; // 선택된 노드
	list<Coordinate*> path;

	OpenNode.push_back(new Node(StartPoint.x, StartPoint.y, NULL, EndPoint)); // 시작지점을 열린노드에 추가

	list<Node*>::iterator iter;

	// 열린 노드가 비거나(열린노드의 시작==끝) 목적지에 도착(열린노드에서 값이 발견)한 경우 끝내야함
	// 즉 조건은 반대로 '열린 노드에 내용이 있거나 목적지를 못 찾은 경우' 반복
	while ((OpenNode.end() != OpenNode.begin()) && (OpenNode.end() == FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode)))
	{
		iter = FindNextNode(&OpenNode); // 열린노드 중 F값이 제일 작은 노드의 주소를 찾아서 iter 에 저장
		SNode = *iter; // 열린노드 중 F값이 제일 작은 노드를 SNode에 저장   // 선택된 SNode 주변의 8방향 노드 탐색, 값이 수정될 수 있는 것은 열린 노드 뿐이므로 열린 노드는 주소를 전달.
		ExploreNode(Navi, SNode, &OpenNode, &CloseNode, EndPoint);
		CloseNode.push_back(SNode); // 현재 탐색한 노드를 닫힌 노드에 추가
		OpenNode.erase(iter); // 닫힌 노드에 추가한 노드를 열린 노드에서 제거
	}
	if ((OpenNode.end() != OpenNode.begin())) // 길을 찾은 경우
	{
		iter = FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode); // 목적지의 노드를 찾아서 iter에 저장
		for (SNode = *iter; SNode->pParent != NULL; SNode = SNode->pParent)  // 부모가 NULL일 때까지 path에 경로 저장
		{
			path.push_back(new Coordinate(SNode->point.x, SNode->point.y));
		}	path.push_back(new Coordinate(SNode->point.x, SNode->point.y)); // 부모가 NULL인 경우의 path까지 저장(출발 지점)

		path.reverse(); // 목적지점으부터 역순으로 입력했으므로 다시 역순으로 뒤집어 출발지점이 첫 번째가 되도록 함.

		// 길을 찾은 경우 동적할당 해제
		iter = OpenNode.begin();
		for (; iter != OpenNode.end(); iter++)
		{
			delete *iter; // 열린 노드 동적할당 해제
		}
		iter = CloseNode.begin();
		for (; iter != CloseNode.end(); iter++)
		{
			delete *iter; // 닫힌 노드 동적할당 해제
		}

		return path; // 길을 찾은 경우 리턴
	}
	// 길을 찾지 못한 경우 동적할당 해제
	iter = CloseNode.begin();
	for (; iter != CloseNode.end(); iter++)
	{
		delete *iter; // 닫힌 노드 동적할당 해제
	}
	return path; // 길을 찾지 못한 경우 리턴
}

void Astar::ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint)
{
	bool up = true, right = true, down = true, left = true; // 이 결과에 따라 대각선 방향 탐색 여부를 결정. true == 장애물 있음, false == 없음
	bool isNoneTerrain = true;
	list<Node*>::iterator iter;
	POINT point;

	// '상' 방향 탐색
	point.x = SNode->point.x - 1;	point.y = SNode->point.y;

	
	if (SNode->point.x > 0 && Navi->map[point.x][point.y] == 0) // '상' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		up = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '우' 방향 탐색
	point.x = SNode->point.x;	point.y = SNode->point.y + 1;
	if (SNode->point.y < (Navi->sizeY - 1) && Navi->map[point.x][point.y] == 0) // '우' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		right = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '하' 방향 탐색
	point.x = SNode->point.x + 1;	point.y = SNode->point.y;//(Navi->map[point.x][point.y] == 0 || Navi->map[point.x][point.y] == 3))
	if (SNode->point.x < (Navi->sizeX - 1) && Navi->map[point.x][point.y] == 0) // '하' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		down = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '좌' 방향 탐색
	point.x = SNode->point.x;	point.y = SNode->point.y - 1;
	if (SNode->point.y > 0 && Navi->map[point.x][point.y] == 0) // '좌' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		left = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}

	// '우상' 방향 탐색
	//point.x = SNode->point.x - 1;	point.y = SNode->point.y + 1;
	//if (SNode->point.x > 0 && SNode->point.y < (Navi->sizeY - 1) && (Navi->map[point.x][point.y] == 0 || Navi->map[point.x][point.y] == 3) &&
	//	up == false && right == false) // '우상' 방향에 맵이 존재하고 장애물이 없으며, 우방향과 상방향에도 장애물이 없을 경우
	//{
	//	// 이미 열린 노드에 있는 경우
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
	//		{
	//			(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
	//		}
	//	}

	//	// 닫힌 노드에 있는 경우
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
	//	// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
	//	else
	//	{
	//		OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '우하' 방향 탐색
	//point.x = SNode->point.x + 1;	point.y = SNode->point.y + 1;
	//if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y < (Navi->sizeY - 1) &&
	//	(Navi->map[point.x][point.y] == 0 || Navi->map[point.x][point.y] == 3) && right == false && down == false)
	//	// '우하' 방향에 맵이 존재하고 장애물이 없으며, 우방향과 하방향에도 장애물이 없을 경우
	//{
	//	// 이미 열린 노드에 있는 경우
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
	//		{
	//			(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
	//		}
	//	}

	//	// 닫힌 노드에 있는 경우
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
	//	// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
	//	else
	//	{
	//		OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '좌하' 방향 탐색
	//point.x = SNode->point.x + 1;	point.y = SNode->point.y - 1;
	//if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y > 0 && (Navi->map[point.x][point.y] == 0 || Navi->map[point.x][point.y] == 3) &&
	//	left == false && down == false) // '좌하' 방향에 맵이 존재하고 장애물이 없으며, 좌방향과 하방향에도 장애물이 없을 경우
	//{
	//	// 이미 열린 노드에 있는 경우
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
	//		{
	//			(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
	//		}
	//	}

	//	// 닫힌 노드에 있는 경우
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
	//	// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
	//	else
	//	{
	//		OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '좌상' 방향 탐색
	//point.x = SNode->point.x - 1;	point.y = SNode->point.y - 1;
	//if (SNode->point.x > 0 && SNode->point.y > 0 && (Navi->map[point.x][point.y] == 0 || Navi->map[point.x][point.y] == 3) &&
	//	left == false && up == false) // '좌상' 방향에 맵이 존재하고 장애물이 없으며, 좌방향과 상방향에도 장애물이 없을 경우
	//{
	//	// 이미 열린 노드에 있는 경우
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
	//		{
	//			(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
	//		}
	//	}

	//	// 닫힌 노드에 있는 경우
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
	//	// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
	//	else
	//	{
	//		OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
	//	}
	//}
}

list<Astar::Node*>::iterator Astar::FindNextNode(list<Astar::Node*>* pOpenNode) // 오픈노드 중 F값이 제일 작은 노드 찾아서 반환
{
	list<Node*>::iterator iter = (*pOpenNode).begin();

	int minValue = 2000000000; // 현재 제일 작은 값을 저장
	int order = 0; // 제일 작은 값이 몇 번째인지

	for (int i = 1; iter != (*pOpenNode).end(); i++, iter++)
	{
		if ((*iter)->F <= minValue) // F값이 작거나 같은 경우를 발견하면(이렇게 구현 시 F값이 같은 경우 최근에 추가된 것이 우선)
		{
			minValue = (*iter)->F;
			order = i;
		}
	}

	iter = (*pOpenNode).begin();
	for (int i = 1; i < order; i++)
	{
		iter++;
	}

	return iter;
}

list<Astar::Node*>::iterator Astar::FindCoordNode(int _x, int _y, list<Astar::Node*>* NodeList) // 노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환. 없으면 end()반환.
{
	list<Astar::Node*>::iterator iter = NodeList->begin();

	for (int i = 1; iter != NodeList->end(); i++, iter++)
	{
		if ((*iter)->point.x == _x && (*iter)->point.y == _y)
		{
			return iter;
		}
	}

	return NodeList->end();
}

void Astar::FindPath()
{
	path = FindPath(&Navi, StartPoint, EndPoint);
	iter = path.begin(); // iter 값 원래대로 돌려주기
}

Astar::Coordinate Astar::GetPos(int order)
{
	Coordinate pos;
	for (int i = 1; i < order; i++)
	{
		iter++;
	}
	pos.x = (*iter)->x;
	pos.y = (*iter)->y;
	iter = path.begin();
	return pos;
}

void Astar::SetFree(int _x, int _y)
{
	Navi.map[_x][_y] = 0;
}

void Astar::SetObstacle(int _x, int _y)
{
	Navi.map[_x][_y] = 1;
}

void Astar::PrintPath()
{
	for (int i = 0; iter != path.end(); iter++)
	{
		/*cout << (*iter)->x << (*iter)->y << endl;*/
	}
	iter = path.begin(); // iter 값 원래대로 돌려주기
}

void Astar::PrintMap()
{
	Navi.PrintMap();
}

void Astar::PrintNavi()
{
	printNavi.Copy(&Navi);

	for (int i = 0; iter != path.end(); iter++) // 맵에서 경로에 해당하는 곳은 7로 표시
	{
		printNavi.map[(*iter)->x][(*iter)->y] = 7;
	}
	iter = path.begin(); // iter 값 원래대로 돌려주기

	printNavi.PrintMap();
}