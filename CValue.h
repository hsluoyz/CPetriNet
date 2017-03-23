#ifndef CVALUE
#define CVALUE

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class CTransition;

class CValue
{
public:
	string colorset;
	int number;
	string type;
	string nickname;
	int i;
	string enumname;
	vector<CValue> values;
	string varname;
	string funname;

	CTransition *transition;
	
public:
	CValue();
	CValue(string a_colorset, int a_number, string a_type, int a_i);
	CValue(string a_colorset, int a_number, string a_type, string a_nickname, int a_i);
	CValue(string a_colorset, int a_number, string a_type, string a_funname, vector<CValue> a_values);
	CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1);
	CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1, CValue argValue2);
	CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1, CValue argValue2, CValue argValue3);
	CValue(string a_colorset, int a_number, string a_type, vector<CValue> a_values);
	CValue(string a_colorset, int a_number, string a_type, string a_name);

	CValue removeFunAndVar(CTransition *a_transition);

	static int isIdentical(CValue &value1, CValue &value2);
	static string itos(int i);
	string toString();
};

typedef CValue (*FUN_POINTER) (vector<CValue> argValues);

#endif