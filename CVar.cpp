#include "CVar.h"

CVar::CVar(string a_name, CColorset *a_colorset)
{
	name = a_name;
	colorset = a_colorset;
	alter_index = 0;
	arc = NULL;
}

void CVar::setValue(CValue a_value)
{
	value = a_value;
}

CValue CVar::getValue()
{
	return value;
}

CVar* CVar::copy()
{
	CVar *var = new CVar(name, colorset);
	return var;
}

void CVar::setInitArc(CArc *a_arc)
{
	arc = a_arc;
}

void CVar::clearAlterValues()
{
	alter_index = 0;
	alter_values.clear();
}

void CVar::addAlterValue(CValue a_value)
{
	a_value.number = 1;
	alter_values.push_back(a_value);
}