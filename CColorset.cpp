#include "CColorset.h"
#include <stdarg.h>

CColorset::CColorset(string a_name, string a_type, int a_int_min, int a_int_max)
{
	name = a_name;
	type = a_type; //"int"
	int_min = a_int_min;
	int_max = a_int_max;
}

CColorset::CColorset(string a_name, string a_type)
{
	name = a_name;
	type = a_type; //"string"
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, string a_nickname, int a_int_min, int a_int_max)
{
	name = a_name;
	type = a_type; //"index"
	nickname = a_nickname;
	int_min = a_int_min;
	int_max = a_int_max;
}

CColorset::CColorset(string a_name, string a_type, vector<CColorset*> a_itemColorsets)
{
	name = a_name;
	type = a_type; //"item"
	itemColorsets = a_itemColorsets;
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, CColorset *itemColorset1)
{
	name = a_name;
	type = a_type; //"item"
	itemColorsets.push_back(itemColorset1);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, CColorset *itemColorset1, CColorset *itemColorset2)
{
	name = a_name;
	type = a_type; //"item"
	itemColorsets.push_back(itemColorset1);
	itemColorsets.push_back(itemColorset2);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, CColorset *itemColorset1, CColorset *itemColorset2, CColorset *itemColorset3)
{
	name = a_name;
	type = a_type; //"item"
	itemColorsets.push_back(itemColorset1);
	itemColorsets.push_back(itemColorset2);
	itemColorsets.push_back(itemColorset3);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, vector<string> a_enumValues)
{
	name = a_name;
	type = a_type; //"enum"
	enumValues = a_enumValues;
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, string enumValue1)
{
	name = a_name;
	type = a_type; //"enum"
	enumValues.push_back(enumValue1);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, string enumValue1, string enumValue2)
{
	name = a_name;
	type = a_type; //"enum"
	enumValues.push_back(enumValue1);
	enumValues.push_back(enumValue2);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, string enumValue1, string enumValue2, string enumValue3)
{
	name = a_name;
	type = a_type; //"enum"
	enumValues.push_back(enumValue1);
	enumValues.push_back(enumValue2);
	enumValues.push_back(enumValue3);
	int_min = -1;
	int_max = -1;
}

CColorset::CColorset(string a_name, string a_type, int argCount, ...)
{
	name = a_name;
	type = a_type; //"item" | "enum"
	int_min = -1;
	int_max = -1;
	
	if (a_type == "item")
	{
		va_list arg_ptr; 
		va_start(arg_ptr, argCount); 
		for (int i = 0; i < argCount; i ++)
		{
			CColorset *itemColorset = (CColorset *) va_arg(arg_ptr, int);
			itemColorsets.push_back(itemColorset);
		}
		va_end(arg_ptr);
	}
	else if (a_type == "enum")
	{
		va_list arg_ptr; 
		va_start(arg_ptr, argCount); 
		for (int i = 0; i < argCount; i ++)
		{
			string_wrapper *enumValue = (string_wrapper *) va_arg(arg_ptr, int);
			enumValues.push_back(enumValue->str);
			delete enumValue;
		}
		va_end(arg_ptr);
	}
	else
	{
		cout << "CColorset Error." << endl;
	}
}

CColorset* CColorset::int_colorset()
{
	CColorset *colorset = new CColorset("INT", "int", 0, 65535);
	return colorset;
}

CColorset* CColorset::uint_colorset()
{
	CColorset *colorset = new CColorset("INT", "int", -32768, 32767);
	return colorset;
}

CColorset* CColorset::bool_colorset()
{
	CColorset *colorset = new CColorset("INT", "int", 0, 1);
	return colorset;
}

CColorset* CColorset::string_colorset()
{
	CColorset *colorset = new CColorset("STRING", "string");
	return colorset;
}