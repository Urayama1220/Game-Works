#include "Imput.h"

Imput::Imput()
{
}

Imput::~Imput()
{
}

const ImputData& Imput::GetData(ImputType type)
{
	if (type == ImputType::NOW)
	{
		return data_;
	}
	else
	{
		return dataOld_;
	}
	return data_;
}
