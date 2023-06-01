#include "TmxObj.h"
#include <string>
#include <sstream>
#include <fstream>
//#include "../_debug/_DebugConOut.h"
#include "../class/common/imageMng.h"
#include <iostream>

TmxObj::TmxObj()
{
	//�o�[�W�������Ή����o�^
	virsion_["1.5.0"] = 0;	
	virsion_["1.6.0"] = 1;
	virsion_["1.7.2"] = 1;
	firstgID_ = 0;
	layerSize_ = 0;
	//virsion_.emplace();//�L�[�ƃf�[�^������̂œ�ǉ�����K�v������
	//virsion_.try_emplace();//���̃��[�g�����ȏ�ʂ�ꍇ�������ŏ���
}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTSX(std::string fileName)
{
	//auto Name = fileName.substr(fileName.find_first_of ("map.tmx") - 1);
	rapidxml::file<> xmlFileName = fileName.c_str();
	tsxDoc_.parse<0>(xmlFileName.data());
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");
	//auto tileset = tsxDoc_.first_node("tileset")		��Ɠ���

	auto tiledversion = tileset->first_attribute("tiledversion");
	if (!CheckTildeVersion(tileset))
	{
		return false;
	}
	/*auto node = tsxDoc_.first_node();
	while (node)
	{
		if (node->name_size())
		{
			TRACE("%s�[��", node->name());
		}
		auto atr = node->first_attribute();
		while (atr)
		{
			if (atr->name_size())
			{
				TRACE("%s:", atr->name());
			}
			TRACE("%s", atr->value());
			atr = atr->next_attribute();
		}
		TRACE("\n");
		node = node->next_sibling();
	}*/
	auto node		= tsxDoc_.first_node();						//�ŏ��̃m�[�h���擾
	while (node)											//null�m�F�@�m�[�h���Ȃ��Ȃ�܂Ń��[�v
	{
		if (node->name_size())								//�T�C�X�m�F�@���O�����邩�m�F
		{
			//TRACE("%s->", node->name());					//�m�[�h�o��
		}
		auto atr = node->first_attribute();				//�ŏ��̃A�g���r���[�g�擾
		while (atr)										//null�m�F�@�m�[�h���Ȃ��Ȃ�܂Ń��[�v
		{
			if (atr->name_size())							//�T�C�X�m�F�@���O�����邩�m�F
			{
				//TRACE("%s:", atr->name());					//�A�g���r���[�g�o��
			}
			//TRACE("%s", atr->value());						//�o�����[�̏o��
			atr = atr->next_attribute();					//���̃A�g���r���[�g
			//TRACE("\n");
		}
		node = node->next_sibling();						//���̃m�[�h
	}
	//tileset����f�[�^�̎��o��
	auto imageNode	= tileset->first_node("image");
	std::string source = imageNode->first_attribute("source")->value();//�t�@�C�����擾
	auto keyName	= source.substr(source.find_last_of("/")+ 1);		//��납�猟�����ăX���b�V���������邻���{�ɂ����/����낪����
		//������̕������o�Ȃǂ�string���Ƃ��₷���@//�p�X���𔲂���key�𐶐�
	auto divsizex	= atoi(tileset->first_attribute("tilewidth")->value());
	auto divsizey	= atoi(tileset->first_attribute("tileheight")->value());
	auto divCntx	= atoi(tileset->first_attribute("columns")->value());
	auto divCnty	= atoi(tileset->first_attribute("tilecount")->value()) / divCntx;
	//--

	

	//GetID�̓ǂݍ���
	lpImageMng.GetID(source, keyName, Vector2{ divsizex,divsizey }, Vector2{ divCntx ,divCnty });
	//TRACE("\n");
	return true;
}

bool TmxObj::LoadTMX(std::string fileName)
{
	rapidxml::file<> tmxFileName = fileName.c_str();
	tmxDoc_.parse<0>(tmxFileName.data());
	rapidxml::xml_node<>* MapNode = tmxDoc_.first_node("map");
	 
	if(!CheckTildeVersion(MapNode))
	{
		return false;
	}

	auto node = tmxDoc_.first_node();
	while (node)
	{
		if (node->name_size())
		{
			//TRACE("%s->", node->name());
		}
		
		auto attribute = node->first_attribute();
		while (attribute)
		{
			if (attribute->name_size())
			{
				//TRACE("%s:", attribute->name());
				
			}
			//TRACE("%s", attribute->value());
			attribute = attribute->next_attribute();
			//TRACE("\n");
		}
		node = node->next_sibling();
	}

	//LoadTSX�̈����̍쐬
	auto tileset	= MapNode->first_node("tileset");
	auto pass		= fileName.substr(0,fileName.find_last_of("/")+1);		//./tmx/������Ă���
	std::string source = pass + tileset->first_attribute("source")->value();	//source���Ƃ��Ă���pass�ƍ���
	//--

	if (!LoadTSX(source))
	{
		//TRACE("TSX�̓ǂݍ��ݎ��s\n");
		return false;
	}
	//MapNode����f�[�^�̎��o��
	firstgID_		= atoi(tileset->first_attribute("firstgid")->value());
	layerSize_		= atoi(MapNode->first_attribute("nextlayerid")->value()) - 1;
	worldArea_.x	= atoi(MapNode->first_attribute("width")->value());
	worldArea_.y	= atoi(MapNode->first_attribute("height")->value());
	tileSize_.x		= atoi(MapNode->first_attribute("tilewidth")->value());
	tileSize_.y		= atoi(MapNode->first_attribute("tileheight")->value());
	
	
	//--
	return SetMap();
}

bool TmxObj::SetMap(void)
{
	rapidxml::xml_node<>* MapNode = tmxDoc_.first_node("map");
	
	if (MapNode == nullptr)
	{
		return false;
	}

	auto layerNode = MapNode->first_node("layer");
	//do 
	for(auto layerNode = MapNode->first_node("layer");	layerNode !=nullptr;	layerNode = layerNode->next_sibling())
	{
		auto layerName = layerNode->first_attribute("name")->value();

		//�I�u�W�F�N�g�O���[�v���}�b�v����O��
		if (layerName == MapNode->first_node("objectgroup")->first_attribute("name")->value())
		{
			continue;
		}
		//--

		auto layer = mapData_.try_emplace(layerName);
		if (layer.second == true)
		{
			layer.first->second.resize(worldArea_.x * worldArea_.y);
		}
		auto layerData = layerNode->first_node("data")->first_node();
		//TRACE("%s\n", layerData->value());

		std::stringstream dataStream;
		dataStream << layerData->value();

		//�͈�for����,�ŋ�؂�Ȃ�����
		for (auto& data : layer.first->second)
		{
			std::string strbuf;
			std::getline(dataStream, strbuf, ',');
			data = atoi(strbuf.c_str());
		}
		//--
		//���̃m�[�h����
		//layerNode = layerNode->next_sibling("layer");

	} //while (layerNode);
	SetCol();
	return true;
}

bool TmxObj::SetCol(void)
{
	int offset = 48;
	rapidxml::xml_node<>* MapNode = tmxDoc_.first_node("map");

	if (MapNode == nullptr)
	{
		return false;
	}
	auto ColNode = MapNode->first_node("objectgroup");
		auto ColName = ColNode->first_attribute("name")->value();
		auto objNode = ColNode->first_node("object");
		for(objNode; objNode != nullptr; objNode = objNode->next_sibling())
	{
		auto objID = objNode->first_attribute("id")->value();	//�g���ĂȂ�
		double objX = atoi(objNode->first_attribute("x")->value());
		double objY = atoi(objNode->first_attribute("y")->value());
		double objW = atoi(objNode->first_attribute("width")->value());
		double objH = atoi(objNode->first_attribute("height")->value());
		Collist_.push_back({ Vector2Dbl{ objX ,objY+(offset) }, Vector2Dbl{ objW ,objH } });
		
	}
	return true;
}

bool TmxObj::LoadAnimCnt(std::string fileName)
{
	/*rapidxml::file<>tmxFileName = fileName.c_str();
	amDoc_.parse<0>(tmxFileName.data());
	rapidxml::xml_node<>* amNode = amDoc_.first_node("actionList");
	if (amNode == nullptr)
	{
		return false;
	}
	auto node = amDoc_.first_node();

	std::string amversion = amNode->first_attribute("version")->value();
	if (amversion != "1.0")
	{
		return false;
	}
	auto animtillnode = amNode->first_node("animtill");
	auto source = animtillnode->first_attribute("source")->value();
	auto keyname = animtillnode->first_attribute("name")->value();
	auto divsizeX = atoi(animtillnode->first_attribute("divsizeX")->value());
	auto divsizeY = atoi(animtillnode->first_attribute("divsizeY")->value());
	auto divCntX = atoi(animtillnode->first_attribute("divCntX")->value());
	auto divCntY = atoi(animtillnode->first_attribute("divCntY")->value());
	lpImageMng.GetID(source, keyname, Vector2{ divsizeX,divsizeY }, Vector2{ divCntX ,divCntY });
	auto action = amDoc_.first_node("action");
	auto name = action->first_attribute("name")->value();
	auto cmX = action->first_attribute("cmX")->value();
	auto cmY = action->first_attribute("cmY")->value();
	auto loop = action->first_attribute("loop")->value();*/
	return true;
}

const Vector2& TmxObj::GetWorldArea(void)
{
	return worldArea_;
}
const Vector2& TmxObj::GetTileSize(void)
{
	return tileSize_;
}
const unsigned int TmxObj::GetLayerSize(void)
{
	return layerSize_;
}
const unsigned int TmxObj::GetFirstgID(void)
{
	return firstgID_;
}

ColList& TmxObj::GetColList(void)
{
	return Collist_;
}

const MapData& TmxObj::GetMapData(void)
{
	return mapData_;
}

const int TmxObj::GetMapData(std::string layer, Vector2 pos)
{
	if (mapData_.count(layer) == 0)
	{
		return 0;
	}
	pos /= tileSize_;
	return GetMapData(layer, pos.x, pos.y);		//�}�X�ڂ̕ω����ԈႦ�ĂȂ���Α��̏����͐��������ɂȂ�
	/*int po = pos.x + (pos.y * worldArea_.x);	//�֐��Ăяo���̃I�[�o�[�w�b�h�������A�f�o�b�N�H���͔{������
	if (po >= 0 && mapData_[layer].size())
	{
		return mapData_[layer][po];
	}*/
}

const int TmxObj::GetMapData(std::string layer, int x, int y)
{
	if (mapData_.count(layer) == 0)
	{
		return 0;
	}
	int point = x + (y * worldArea_.x);
	if (point < 0 && point >= mapData_[layer].size())
	{
		return 0;
	}
	return  mapData_[layer][point];
}

bool TmxObj::CheckTildeVersion(rapidxml::xml_node<>* node)
{
	if (!node)
	{
		return false;
	}
	auto tiledversion = node->first_attribute("tiledversion");
	if (!virsion_.count(tiledversion->value()))//���g�̒l������
	{
		//TRACE("TMX�̔�Ή��o�[�W����\n");
		return false;
	}
	if (!virsion_[tiledversion->value()])//�󋵂ɂ���ẮA
	{
		//TRACE("TMX��Ή��o�[�W����\n");
		return false;
	}
	//TRACE("TMX�̑Ή��o�[�W����\n");
	return true;
}
