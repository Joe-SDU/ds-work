#pragma once

// “Ï≥£¿‡

#include <string>

class illegalParameterValue
{
public:
	illegalParameterValue(const std::string& msg = "illegal value")
		: errorMsg(msg) {}
private:
	std::string errorMsg;
};
