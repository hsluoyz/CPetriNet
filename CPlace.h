#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>
using namespace std;

class CTransition;
#include "CValue.h"

class CPlace
{
public:
	string name;
	string colorset;
	vector<CValue> values;
	
	vector<CTransition*> froms;
	vector<CTransition*> tos;
	
public:
	CPlace(string a_name, string a_colorset);
	CPlace(string a_name, string a_colorset, CValue a_value);
	void addValue(CValue a_value);

	void addFromTransition(CTransition *transition);
	void addToTransition(CTransition *transition);
	int putToken(CValue a_value);
	int okTakeToken(CValue a_value);
	int takeToken(CValue a_value);

	static string itos(int i);
	string toString();
};