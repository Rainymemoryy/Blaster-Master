#include <fstream>
#include <iostream>
#include "Map.h"
#include"Utils.h"
#include "Game.h"

Map::Map(int idMap, int nTitleCols, int nTitleRows, int nMapCols, int nMapRows, int nTotalTiles)
{
	this->TileSet = CTextures::GetInstance()->Get(idMap);
	this->TotalColsOfMap = nMapCols;
	this->TotalRowsOfMap = nMapRows;
	this->TotalRowsOfTileSet = nTitleRows;
	this->TotalColsOfTitleSet = nTitleCols;
	this->TotalTiles = nTotalTiles;
}
Map::~Map()
{
}
void Map::CreateTilesFromTileSet()
{
	int left, bottom, right, top;
	for (int tileNum = 0; tileNum < TotalTiles; tileNum++) {
		left = tileNum % TotalColsOfTitleSet * TILE_WIDTH;
		top = tileNum / TotalColsOfTitleSet * TILE_HEIGHT;
		bottom = top + TILE_HEIGHT;
		right = left + TILE_WIDTH;
		LPSPRITE Tile = new CSprite(tileNum, left, top, right, bottom, TileSet);
		this->Tiles.push_back(Tile);
	}
}
void Map::LoadMatrix(LPCWSTR path)
{
	ifstream file;

	file.open(path);
	this->Matrix = new int* [TotalRowsOfMap];
	for (int iRow = 0; iRow < TotalRowsOfMap; iRow++)
	{
		this->Matrix[iRow] = new int[TotalColsOfMap];
		for (int iColumn = 0; iColumn < TotalColsOfMap; iColumn++)
		{
			file >> this->Matrix[iRow][iColumn];
		}
	}
	file.close();
}
void Map::Render(int cx, int cy,int al)
{

	int col = (cx + CGame::GetInstance()->GetScreenWidth()) / 16 + 1;
	col = col >= TotalColsOfMap ? TotalColsOfMap : col;

	int row = (cy + CGame::GetInstance()->GetScreenHeight()) / 16 + 1;
	row = row >= TotalRowsOfMap ? TotalRowsOfMap : row;
	if (cy < 0) cy = 0;
	for (int iRow = cy / 16; iRow < row; iRow++)
	{
		if (cx < 0) cx = 0;

		for (int iColumn = cx / 16; iColumn < col; iColumn++)
		{
			this->Tiles[this->Matrix[iRow][iColumn] - 1]->Draw(iColumn * TILE_WIDTH, iRow * TILE_HEIGHT, al);
		}
	}
}
void Map::Render2(int cx, int cy)
{

	int col = (cx + CGame::GetInstance()->GetScreenWidth()) / 16 + 1;
	col = col >= TotalColsOfMap ? TotalColsOfMap : col;

	int row = (cy + CGame::GetInstance()->GetScreenHeight()) / 16 + 1;
	row = row >= TotalRowsOfMap ? TotalRowsOfMap : row;
	if (cy < 0) cy = 0;
	int i = cy / 16;
	while (i % 16 != 12)
		i++;
	for (int iRow = i; iRow <= i; iRow += 16)
	{
		if (cx < 0) cx = 0;

		if (iRow % 16 == 12)
			for (int iColumn = cx / 16; iColumn < col; iColumn++)
			{
				this->Tiles[this->Matrix[iRow][iColumn] - 1]->Draw(iColumn * TILE_WIDTH, iRow * TILE_HEIGHT, 255);
				this->Tiles[this->Matrix[iRow + 1][iColumn] - 1]->Draw(iColumn * TILE_WIDTH, (iRow + 1) * TILE_HEIGHT, 255);

			}
	}
}
int Map::GetMapHeight()
{
	if (Height == 0)
		Height = TotalRowsOfMap * TILE_HEIGHT;
	return Height;
}
int Map::GetMapWidth()
{
	if (Width == 0)
	{
		Width = TotalColsOfMap * TILE_WIDTH;
	}
	return Width;
}