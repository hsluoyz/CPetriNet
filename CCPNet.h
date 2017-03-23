#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif


#include <string>
#include <map>
#include <iostream>
using namespace std;

class CPlace;
class CTransition;
class CVal;
class CColorset;
class CVar;
#include "CValue.h"

class CCPNet
{
public:
	string name;

	map<string, CPlace*> places;
	map<string, CTransition*> transitions;
	map<string, CVal*> vals;
	map<string, CColorset*> colorsets;
	map<string, CVar*> vars;
	map<string, FUN_POINTER> funs;

public:
	CPlace* checkPlace(string strName);
	CPlace* getPlace(string strName);
	void addPlace(CPlace *place);
	void addPlace(string strPlaceName, string strColorset);
	void addPlace(string strPlaceName, string strColorset, CValue value);
	void addPlaceValue(string strPlaceName, CValue value);

	CTransition* checkTransition(string strName);
	CTransition* getTransition(string strName);
	void addTransition(CTransition *transition);
	void addTransition(string strTransitionName);

	void transitionAddFromPlaceAndValue(string strTransition, string strPlace, CValue value);
	void transitionAddToPlaceAndValue(string strTransition, string strPlace, CValue value);
	void transitionAddFromToPlaceAndValue(string strTransition, string strPlace, CValue value);
	void initAllTransitions();

	CVal* getVal(string strName);
	void addVal(CVal *val);

	CColorset* checkColorset(string strName);
	CColorset* getColorset(string strName);
	void addColorset(CColorset *colorset);

	CVar* checkVar(string strName);
	CVar* getVar(string strName);
	void addVar(CVar *var);
	void addVar(string strVarName, string strColorset);
	CValue varname2Value(int iVar, string strVarName);
	CValue VAR(int iVar, string strVarName);
	
	FUN_POINTER checkFun(string strName);
	FUN_POINTER getFun(string strName);
	void addFun(string strName, FUN_POINTER fun);
	CValue FUN(string strFunName, string strArgVarName1);
	CValue FUN(string strFunName, string strArgVarName1, string strArgVarName2);
	CValue FUN(string strFunName, string strArgVarName1, string strArgVarName2, string strArgVarName3);
	
	int fire();
	void fireToEnd();

	string places2String();
};