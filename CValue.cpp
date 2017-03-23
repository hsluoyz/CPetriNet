#include "CValue.h"
#include "CFun.h"
#include "CTransition.h"
#include "CCPNet.h"

CValue::CValue()
{
	type = ""; //""
	number = 0;
	i = -1;
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, int a_i)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"int"
	i = a_i;
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_nickname, int a_i)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"index"
	nickname = a_nickname;
	i = a_i;
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, vector<CValue> a_values)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"item"
	i = -1;
	values = a_values;
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_funname, vector<CValue> a_values)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"fun"
	i = -1;
	funname = a_funname;
	values = a_values;
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"fun"
	i = -1;
	funname = a_funname;
	values.push_back(argValue1);
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1, CValue argValue2)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"fun"
	i = -1;
	funname = a_funname;
	values.push_back(argValue1);
	values.push_back(argValue2);
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_funname, CValue argValue1, CValue argValue2, CValue argValue3)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"fun"
	i = -1;
	funname = a_funname;
	values.push_back(argValue1);
	values.push_back(argValue2);
	values.push_back(argValue3);
	transition = NULL;
}

CValue::CValue(string a_colorset, int a_number, string a_type, string a_name)
{
	colorset = a_colorset;
	number = a_number;
	type = a_type; //"string" | "enum" | "var"
	if (a_type == "string")
		nickname = a_name;
	else if (a_type == "enum")
		enumname = a_name;
	else if (a_type == "var")
		varname = a_name;
	else
	{
		cout << "CValue Error." << endl;
	}
	i = -1;
	transition = NULL;
}

CValue CValue::removeFunAndVar(CTransition *a_transition)
{
	transition = a_transition;

	if (type == "fun")
	{
		FUN_POINTER fun_pointer = transition->cpnet->getFun(funname);
		vector<CValue> valuesRemoved;
		for (int i = 0; i < values.size(); i ++)
			valuesRemoved.push_back(values[i].removeFunAndVar(transition));
		return fun_pointer(valuesRemoved);
	}
	else if (type == "var")
	{
		CValue value = transition->varname2Value(varname);
		value.number = number;
		return value;
	}
	else
	{
		return *this;
	}
}

int CValue::isIdentical(CValue &value1, CValue &value2)
{
	if (value1.colorset != value2.colorset)
		return 0;
	if (value1.type != value2.type)
		return 0;
	if (value1.nickname != value2.nickname)
		return 0;
	if (value1.i != value2.i)
		return 0;
	if (value1.enumname != value2.enumname)
		return 0;
	if (value1.values.size() != value2.values.size())
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < value1.values.size(); i ++)
			if (CValue::isIdentical(value1.values[i], value2.values[i]) == 0)
				return 0;
	}
	if (value1.varname != value2.varname)
		return 0;
	if (value1.funname != value2.funname)
		return 0;
	return 1;
}

string CValue::itos(int i)
{
	char cBuffer[10];
	itoa(i, cBuffer, 10);
	string s(cBuffer);
	return s;
}

/*
string CValue::toString()
{
	string strResult;
	strResult += ("colorset:" + colorset);
	strResult += (" number:" + itos(number));
	strResult += (" type:" + type);
	if (type == "int")
	{
		strResult += (" i:" + itos(i));
	}
	else if (type == "index")
	{
		strResult += (" nickname:" + nickname);
		strResult += (" index:" + itos(i));
	}
	else if (type == "item")
	{
		for (int i = 0; i < values.size(); i ++)
		{
			strResult += ("\nitem-" + itos(i) + ":");
			strResult += values[i].toString();
		}
	}
	else if (type == "fun")
	{
		strResult += (" fun:" + funname);
		for (int i = 0; i < values.size(); i ++)
		{
			strResult += ("\narg-" + itos(i) + ":");
			strResult += values[i].toString();
		}
	}
	else if (type == "enum")
	{
		strResult += (" enumname:" + enumname);
	}
	else if (type == "var")
	{
		strResult += (" varname:" + varname);
	}
	else
	{
		cout << "toString Error." << endl;
		return "";
	}

	return strResult;
}
*/

string CValue::toString()
{
	string strResult;
	strResult += (colorset + "::" + itos(number) + "`");
	if (type == "int")
	{
		strResult += itos(i);
	}
	else if (type == "index")
	{
		strResult += (nickname + "(" + itos(i) + ")");
	}
	else if (type == "item")
	{
		strResult += "(";
		for (int i = 0; i < values.size(); i ++)
		{
			strResult += (values[i].toString() + " ,");
		}
		strResult.erase(strResult.size() - 2, 2);
		strResult += ")";
	}
	else if (type == "fun")
	{
		strResult += (funname + "(");
		for (int i = 0; i < values.size(); i ++)
		{
			strResult += (values[i].toString() + " ,");
		}
		strResult.erase(strResult.size() - 2, 2);
		strResult += ")";
	}
	else if (type == "enum")
	{
		strResult += enumname;
	}
	else if (type == "var")
	{
		strResult += varname;
	}
	else
	{
		cout << "toString Error." << endl;
		return "";
	}
	
	return strResult;
}