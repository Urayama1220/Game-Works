#pragma once
#include <array>
#include <map>
#include "InputID.h"
#include "../../tmx/TmxObj.h"
#include <chrono>
//#include "../../tmx/rapidxml.hpp"
//#include "../../tmx/rapidxml_utils.hpp"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include <vector>
//“ü—Í‘•’u‚Ìí—Ş
enum class CntTupe
{
	Key,
	Pad,
	Max
};
enum class Trg
{
	Now,
	Old,
	Max
};

using ChronoSysClock = std::chrono::system_clock::time_point;
using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;
class Controller
{
public:
	
	Controller() ;	//‰½‚à‚µ‚È‚¯‚ê‚Î‘‚©‚È‚­‚Ä‚¢‚¢
	virtual ~Controller() {};
	virtual void  Updata() = 0;
	virtual CntTupe GetCntType(void) = 0;

	const CntData& GetCntData(void)
	{
		return cntData_;
	};
	/*rapidxml::xml_node<>* Getnode();*/
private:
	ChronoSysClock startTime;
protected:
	CntData cntData_;
};
