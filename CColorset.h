#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class string_wrapper
{
public:
	string str;
	string_wrapper(string a_str) {str = a_str;}
};
#define STR(str) new string_wrapper(str)

class CColorset
{
public:
	string name;
	string type;//"int" | "index" | "item" | "enum"

	int int_min;
	int int_max;
	string nickname;
	vector<CColorset*> itemColorsets;
	vector<string> enumValues;
	
public:
	CColorset(string a_name, string a_type, int a_int_min, int a_int_max);
	CColorset(string a_name, string a_type);
	CColorset(string a_name, string a_type, string a_nickname, int a_int_min, int a_int_max);
	CColorset(string a_name, string a_type, vector<CColorset*> a_itemColorsets);
	CColorset(string a_name, string a_type, CColorset *itemColorset1);
	CColorset(string a_name, string a_type, CColorset *itemColorset1, CColorset *itemColorset2);
	CColorset(string a_name, string a_type, CColorset *itemColorset1, CColorset *itemColorset2, CColorset *itemColorset3);
	CColorset(string a_name, string a_type, vector<string> a_enumValues);
	CColorset(string a_name, string a_type, string enumValue1);
	CColorset(string a_name, string a_type, string enumValue1, string enumValue2);
	CColorset(string a_name, string a_type, string enumValue1, string enumValue2, string enumValue3);
	CColorset(string a_name, string a_type, int argCount, ...);

	static CColorset* int_colorset();
	static CColorset* uint_colorset();
	static CColorset* bool_colorset();
	static CColorset* string_colorset();
};