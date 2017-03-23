#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <iostream>
using namespace std;

#include "CValue.h"

class CFun
{
public:
	string name;
	int count;
	
public:
	static CValue PFromUO(vector<CValue> argValues);
	static CValue DFromUO(vector<CValue> argValues);
	static CValue DFromP(vector<CValue> argValues);
	static CValue CFromP(vector<CValue> argValues);
	static CValue CFromU(vector<CValue> argValues);
	CValue calculateValue(vector<CValue> argValues);

	string toString();
};