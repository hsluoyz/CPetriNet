#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class CFun;
class CPlace;
#include "CValue.h"

class CArc
{
public:
	CValue value;
	int init;
	CPlace *place;
	
public:
	CArc(CValue a_value, CPlace *a_place);
};