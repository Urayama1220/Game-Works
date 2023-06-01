#include "AnimMng.h"
#include "../common/imageMng.h"
#include "../../tmx/TmxObj.h"
//#include "../../_debug/_DebugConOut.h"
#include<sstream>
AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{
}
bool AnimMng::LoadAnim(std::string filName)
{
	rapidxml::xml_document<> amDoc_;
	rapidxml::file<>tmxFileName = filName.c_str();
	amDoc_.parse<0>(tmxFileName.data());
	rapidxml::xml_node<>* amNode = amDoc_.first_node("actionList");
	if (amNode == nullptr)
	{
		return false;
	}
	auto node = amDoc_.first_node();
	std::string objID = amNode->first_attribute("name")->value();
	std::string amversion = amNode->first_attribute("version")->value();
	if (amversion != "1.0")
	{
		return false;
	}
	auto animtillnode = amNode->first_node("animtill");
	auto source = animtillnode->first_attribute("source")->value();
	auto keyname = animtillnode->first_attribute("keyname")->value();
	auto divsizeX = atoi(animtillnode->first_attribute("divsizeX")->value());
	auto divsizeY = atoi(animtillnode->first_attribute("divsizeY")->value());
	auto divx = atoi(animtillnode->first_attribute("divCntX")->value());
	auto divy = atoi(animtillnode->first_attribute("divCntY")->value());
	lpImageMng.GetID(source, keyname, Vector2{ divsizeX,divsizeY }, Vector2{ divx ,divy });

	divsize.x = divsizeX;
	divsize.y = divsizeY;
	for (auto action = animtillnode->first_node("action"); action != nullptr; action = action->next_sibling())
	{
		std::string actionName = action->first_attribute("name")->value();
		//auto cmX = atoi(action->first_attribute("cmX")->value());//使ってない
		//auto cmY = atoi(action->first_attribute("cmY")->value());//使ってない
		auto actionLoop = atoi(action->first_attribute("loop")->value());
		auto objname = objID + actionName;
		AnimTbl.try_emplace(objname);
		AnimTbl[objname].first.first = actionLoop;
		//AnimTbl[objname].first.second.first = cmX;	//つかってない
		//AnimTbl[objname].first.second.second = cmY;	//つかってない

		auto actiondata = action->first_node("data")->first_node();
		if (actiondata == nullptr)
		{
			return false;
		}
		//TRACE("%s\n", actiondata->value());
		std::stringstream dataStream;
		dataStream << actiondata->value();

		std::string strbuf;
		

		while (std::getline(dataStream, strbuf, ','))
		{
			auto id = atoi(strbuf.c_str());
			std::getline(dataStream, strbuf, ',');
			auto frame = atoi(strbuf.c_str());
			/*std::getline(dataStream, strbuf, ',');
			auto colsi = atoi(strbuf.c_str());*/
			AnimTbl[objname].second.emplace_back(AnimData{ id, frame /*,colsi */});
		}
	}
	return true;
}

animItrCnt AnimMng::SetAnimData(std::string ObjID, std::string state_)
{
	return animItrCnt {
		ObjID,
		state_,
		AnimTbl[ObjID + state_].second.begin(),
		0,
		0
	};
}

bool AnimMng::UpdataAnime(animItrCnt& animItr)
{
	if (animItr.stateCnt_++ >= (*animItr.animitr)[InvLimit])
	{

		++animItr.animitr;
		animItr.stateCnt_ = 0;
		if (animItr.animitr == AnimTbl[animItr.ObjID + animItr.state].second.end())
		{
			if (++animItr.animPlayCnt_ < AnimTbl[animItr.ObjID + animItr.state].first.first || AnimTbl[animItr.ObjID + animItr.state].first.first == -1)
			{
				//ループ
				animItr.animitr = AnimTbl[animItr.ObjID + animItr.state].second.begin();
			}
			else
			{
				//再生終了の場合最終コマをセット
				animItr.animitr = --AnimTbl[animItr.ObjID + animItr.state].second.end();
				return true;
			}
		}
	}
	return false;
}
