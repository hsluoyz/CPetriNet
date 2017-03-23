#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
using namespace std;

class CColorset;
class CArc;
#include "CValue.h"

class CVar
{
public:
	string name;
	CColorset *colorset;
	CValue value;
	vector<CValue> alter_values;
	int alter_index;
	CArc *arc;
	
public:
	CVar(string a_name, CColorset *a_colorset);
	void setValue(CValue a_value);
	CValue getValue();

	CVar* copy();
	void setInitArc(CArc *a_arc);
	void clearAlterValues();
	void addAlterValue(CValue a_value);
};