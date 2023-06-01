#include "imageMng.h"
#include <DxLib.h>
#include "../../_debug/_DebugConOut.h"

const VecInt& imageMng::GetID(std::string key)
{
	if (imageMap_.find(key) == imageMap_.end())//imageMap_.count(key) ==0@‚±‚ê‚Å‚à‚¢‚¢
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(key.c_str());
		
	}
	return imageMap_[key];
}

const VecInt& imageMng::GetID(std::string f_name, std::string key)
{
	if (imageMap_.find(key) == imageMap_.end())
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());

	}
	return imageMap_[key];
}

const VecInt& imageMng::GetID(std::string f_name, std::string key, Vector2 divsize, Vector2 divCnt)
{
	if (imageMap_.find(key) == imageMap_.end())
	{
		imageMap_[key].resize(static_cast<UINT64>(divCnt.x) * static_cast<UINT64>(divCnt.y));
		if (LoadDivGraph(f_name.c_str(),
			divCnt.x * divCnt.y,
			divCnt.x, divCnt.y,
			divsize.x, divsize.y,
			&imageMap_[key][0], true) == -1)
		{
			TRACE("‰æ‘œ‚Ì“Ç‚İ‚İ¸”s:%s\n", f_name.c_str());
		}
	}
	return imageMap_[key];
	
}

imageMng::imageMng()
{
}
imageMng::~imageMng()
{
}
