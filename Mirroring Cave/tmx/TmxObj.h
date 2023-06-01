#pragma once

#include <string>
#include <map>
#include <vector>
#include "../class/common/Vector2.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <list>
#include "../class/common/Collision.h"
using MapData = std::map<std::string, std::vector<int>>;
//using ColList = std::list<std::pair<Vector2, Vector2>>;
class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	bool LoadTSX(std::string fileName);
	bool LoadTMX(std::string fileName);
	bool SetMap(void);
	bool SetCol(void);
	bool LoadAnimCnt(std::string fileName);
	const Vector2& GetWorldArea(void);
	const Vector2& GetTileSize(void);
	const unsigned int GetLayerSize(void);
	const unsigned int GetFirstgID(void);

	ColList& GetColList(void);

	const MapData& GetMapData(void);
	const int GetMapData(std::string layer,Vector2 pos);//posは座標変換が必要
	const int GetMapData(std::string layer, int x,int y);//xyはマス目数
private:
	bool CheckTildeVersion(rapidxml::xml_node<>* node);//バージョンチェック関数
	std::map<std::string, int>virsion_;

	//TMX
	rapidxml::xml_document<> tmxDoc_;
	unsigned int firstgID_;		//layerのID
	unsigned int layerSize_;
	Vector2 worldArea_;	//世界のサイズ
	Vector2 tileSize_;	//一チップ当たりのサイズ
	MapData mapData_;

	//TSX
	rapidxml::xml_document<> tsxDoc_;
	//
	ColList Collist_;
protected:
};

