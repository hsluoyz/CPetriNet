#include "CCPNet.h"
#include "CPlace.h"
#include "CTransition.h"
#include "CVal.h"
#include "CColorset.h"
#include "CVar.h"

CPlace* CCPNet::checkPlace(string strName)
{
	map<string, CPlace*>::iterator iter= places.find(strName);
	if(iter == places.end())
	{
		return NULL;
	}
	else
	{
		cout << "checkPlace Error." << endl;
		return iter->second;
	}
}

CPlace* CCPNet::getPlace(string strName)
{
	map<string, CPlace*>::iterator iter= places.find(strName);
	if(iter == places.end())
	{
		cout << "getPlace Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addPlace(CPlace *place)
{
	if (checkPlace(place->name) != NULL)
	{
		cout << "addPlace Error." << endl;
		return;
	}
	places.insert(map<string, CPlace*>::value_type(place->name, place));
}

void CCPNet::addPlace(string strPlaceName, string strColorset)
{
	CPlace *place = new CPlace(strPlaceName, strColorset);
	places.insert(map<string, CPlace*>::value_type(place->name, place));
}

void CCPNet::addPlace(string strPlaceName, string strColorset, CValue value)
{
	CPlace *place = new CPlace(strPlaceName, strColorset, value);
	places.insert(map<string, CPlace*>::value_type(place->name, place));
}

void CCPNet::addPlaceValue(string strPlaceName, CValue value)
{
	CPlace *place = getPlace(strPlaceName);
	if (place != NULL)
	{
		place->addValue(value);
	}
}

CTransition* CCPNet::checkTransition(string strName)
{
	map<string, CTransition*>::iterator iter= transitions.find(strName);
	if(iter == transitions.end())
	{
		return NULL;
	}
	else
	{
		cout << "checkTransition Error." << endl;
		return iter->second;
	}
}

CTransition* CCPNet::getTransition(string strName)
{
	map<string, CTransition*>::iterator iter= transitions.find(strName);
	if(iter == transitions.end())
	{
		cout << "getTransition Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addTransition(CTransition *transition)
{
	if (checkTransition(transition->name) != NULL)
	{
		cout << "addTransition Error." << endl;
		return;
	}
	transitions.insert(map<string, CTransition*>::value_type(transition->name, transition));
}

void CCPNet::addTransition(string strTransitionName)
{
	CTransition *transition = new CTransition(strTransitionName, this);
	addTransition(transition);
}

void CCPNet::transitionAddFromPlaceAndValue(string strTransition, string strPlace, CValue value)
{
	CTransition *transition = getTransition(strTransition);
	if (transition != NULL)
	{
		transition->addFromPlaceAndValue(strPlace, value);
	}
}

void CCPNet::transitionAddToPlaceAndValue(string strTransition, string strPlace, CValue value)
{
	CTransition *transition = getTransition(strTransition);
	if (transition != NULL)
	{
		transition->addToPlaceAndValue(strPlace, value);
	}
}

void CCPNet::transitionAddFromToPlaceAndValue(string strTransition, string strPlace, CValue value)
{
	CTransition *transition = getTransition(strTransition);
	if (transition != NULL)
	{
		transition->addFromPlaceAndValue(strPlace, value);
		transition->addToPlaceAndValue(strPlace, value);
	}
}

void CCPNet::initAllTransitions()
{
	map<string, CTransition*>::iterator iter;
	for (iter = transitions.begin(); iter != transitions.end(); iter ++)
	{
		iter->second->init();
	}
}

CVal* CCPNet::getVal(string strName)
{
	map<string, CVal*>::iterator iter= vals.find(strName);
	if(iter == vals.end())
	{
		cout << "getVal Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addVal(CVal *val)
{
	if (getVal(val->name) != NULL)
		cout << "addVal Error." << endl;
	vals.insert(map<string, CVal*>::value_type(val->name, val));
}

CColorset* CCPNet::checkColorset(string strName)
{
	map<string, CColorset*>::iterator iter= colorsets.find(strName);
	if(iter == colorsets.end())
	{
		return NULL;
	}
	else
	{
		cout << "checkColorset Error." << endl;
		return iter->second;
	}
}

CColorset* CCPNet::getColorset(string strName)
{
	map<string, CColorset*>::iterator iter= colorsets.find(strName);
	if(iter == colorsets.end())
	{
		cout << "getColorset Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addColorset(CColorset *colorset)
{
	if (checkColorset(colorset->name) != NULL)
	{
		cout << "addColorset Error." << endl;
		return;
	}
	colorsets.insert(map<string, CColorset*>::value_type(colorset->name, colorset));
}

CVar* CCPNet::checkVar(string strName)
{
	map<string, CVar*>::iterator iter= vars.find(strName);
	if(iter == vars.end())
	{
		return NULL;
	}
	else
	{
		cout << "checkVar Error." << endl;
		return iter->second;
	}
}

CVar* CCPNet::getVar(string strName)
{
	map<string, CVar*>::iterator iter= vars.find(strName);
	if(iter == vars.end())
	{
		cout << "getVar Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addVar(CVar *var)
{
	if (checkVar(var->name) != NULL)
	{
		cout << "addVar Error." << endl;
		return;
	}
	vars.insert(map<string, CVar*>::value_type(var->name, var));
}

void CCPNet::addVar(string strVarName, string strColorset)
{
	if (checkVar(strVarName) != NULL)
	{
		cout << "addVar Error." << endl;
		return;
	}
	CColorset *colorset = getColorset(strColorset);
	if (colorset == NULL)
	{
		cout << "addVar Error." << endl;
		return;
	}
	CVar *var = new CVar(strVarName, colorset);
	vars.insert(map<string, CVar*>::value_type(var->name, var));
}

CValue CCPNet::varname2Value(int iVar, string strVarName)
{
	CVar *var = getVar(strVarName);
	if (var == NULL)
	{
		cout << "varname2Value Error." << endl;
		return CValue();
	}

	CValue value = CValue(var->colorset->name, iVar, "var", strVarName);
	return value;
}

CValue CCPNet::VAR(int iVar, string strVarName)
{
	return varname2Value(iVar, strVarName);
}

CValue CCPNet::FUN(string strFunName, string strArgVarName1)
{
	CVar *var1 = getVar(strArgVarName1);
	if (var1 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}

	CValue value = CValue("", 1, "fun", strFunName, VAR(1, strArgVarName1));
	return value;
}

CValue CCPNet::FUN(string strFunName, string strArgVarName1, string strArgVarName2)
{
	CVar *var1 = getVar(strArgVarName1);
	if (var1 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}
	CVar *var2 = getVar(strArgVarName2);
	if (var2 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}
	
	CValue value = CValue("", 1, "fun", strFunName, VAR(1, strArgVarName1), VAR(1, strArgVarName2));
	return value;
}

CValue CCPNet::FUN(string strFunName, string strArgVarName1, string strArgVarName2, string strArgVarName3)
{
	CVar *var1 = getVar(strArgVarName1);
	if (var1 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}
	CVar *var2 = getVar(strArgVarName2);
	if (var2 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}
	CVar *var3 = getVar(strArgVarName3);
	if (var3 == NULL)
	{
		cout << "FUN Error." << endl;
		return CValue();
	}
	
	CValue value = CValue("", 1, "fun", strFunName, VAR(1, strArgVarName1), VAR(1, strArgVarName2), VAR(1, strArgVarName3));
	return value;
}

FUN_POINTER CCPNet::checkFun(string strName)
{
	map<string, FUN_POINTER>::iterator iter= funs.find(strName);
	if(iter == funs.end())
	{
		return NULL;
	}
	else
	{
		cout << "checkFun Error." << endl;
		return iter->second;
	}
}

FUN_POINTER CCPNet::getFun(string strName)
{
	map<string, FUN_POINTER>::iterator iter= funs.find(strName);
	if(iter == funs.end())
	{
		cout << "getFun Error." << endl;
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void CCPNet::addFun(string strName, FUN_POINTER fun)
{
	if (checkFun(strName) != NULL)
	{
		cout << "addFun Error." << endl;
		return;
	}
	funs.insert(map<string, FUN_POINTER>::value_type(strName, fun));
}

int CCPNet::fire()
{
	map<string, CTransition*>::iterator iter;
	for (iter = transitions.begin(); iter != transitions.end(); iter ++)
	{
		if (iter->second->fire() == 1)
		{
			cout << iter->second->name << " fired succeed." << endl;
			return 1;
		}
	}
	return 0;
}

void CCPNet::fireToEnd()
{
	while (fire() == 1);
}

string CCPNet::places2String()
{
	string strResult;
	map<string, CPlace*>::iterator iter;
	for (iter = places.begin(); iter != places.end(); iter ++)
	{
		strResult += (iter->second->toString() + "\n");
	}
	return strResult;
}