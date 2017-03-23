#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>
using namespace std;

class CCPNet;
class CPlace;
class CArc;
class CVar;
#include "CValue.h"

class CTransition
{
public:
	string name;

	vector<CPlace*> fromPlaces;
	vector<CPlace*> toPlaces;
	vector<CArc*> fromArcs;
	vector<CArc*> toArcs;
	vector<int> fromArcsInit;
	vector<CVar*> vars;
	CCPNet *cpnet;
	
public:
	CTransition(string a_name, CCPNet *a_cpnet);
	void addFromPlaceAndValue(string strPlace, CValue value);
	void addToPlaceAndValue(string strPlace, CValue value);
	
	int findVar(CVar *var);
	CVar* addVar(string a_name);
	void addVarFromValue(CArc *arc, CValue &value);
	void addAllVars();
	void initAlterValues();

	CVar* varname2Var(string strVarname);
	CValue varname2Value(string strVarname);
	int okSubArc(CArc *arc);
	int subArc(CArc *arc);
	int addArc(CArc *arc);

	void init();
	int fire();
};