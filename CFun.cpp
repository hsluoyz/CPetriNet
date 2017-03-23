#include "CFun.h"
#include <stdarg.h>

CValue CFun::PFromUO(vector<CValue> argValues)
{
	if (argValues.size() != 2)
	{
		cout << "PFromUO Error." << endl;
		return CValue();
	}
	CValue u = argValues[0];
	CValue t = argValues[1];
	
	int flag = 1;
	if (u.colorset != "USER" || u.type != "var")
		flag = 0;
	if (t.colorset != "OPT" || t.type != "var")
		flag = 0;
	
	vector<CValue> results;
	results.push_back(u);
	results.push_back(t);
	results.push_back(CValue("ACT", 1, "int", 1));
	return CValue("PERMISSION", 1, "item", results);
}

CValue CFun::DFromUO(vector<CValue> argValues)
{
	if (argValues.size() != 2)
	{
		cout << "DFromUO Error." << endl;
		return CValue();
	}
	CValue u = argValues[0];
	CValue t = argValues[1];
	
	int flag = 1;
	if (u.colorset != "USER" || u.type != "var")
		flag = 0;
	if (t.colorset != "OPT" || t.type != "var")
		flag = 0;
	
	vector<CValue> results;
	results.push_back(u);
	results.push_back(t);
	results.push_back(CValue("ACT", 1, "int", 0));
	return CValue("PERMISSION", 1, "item", results);
}

CValue CFun::DFromP(vector<CValue> argValues)
{
	if (argValues.size() != 1)
	{
		cout << "DFromP Error." << endl;
		return CValue();
	}
	CValue args = argValues[0];
	
	int flag = 1;
	if (args.colorset != "PERMISSION" || args.type != "item")
		flag = 0;
	if (args.values.size() != 3)
		flag = 0;
	if (args.values[0].colorset != "USER" || args.values[0].type != "var")
		flag = 0;
	if (args.values[1].colorset != "OPT" || args.values[0].type != "var")
		flag = 0;
	if (args.values[2].colorset != "ACT" || args.values[0].type != "int" || args.values[0].i != 1)
		flag = 0;
	if (flag == 0)
		return CValue();
	
	vector<CValue> results;
	results.push_back(args.values[0]);
	results.push_back(args.values[1]);
	results.push_back(CValue("ACT", 1, "int", 1));
	return CValue("PERMISSION", 1, "item", results);
}

CValue CFun::CFromP(vector<CValue> argValues)
{
	if (argValues.size() != 1)
	{
		cout << "CFromP Error." << endl;
		return CValue();
	}
	CValue args = argValues[0];
	
	int flag = 1;
	if (args.colorset != "PERMISSION" || args.type != "item")
		flag = 0;
	if (args.values.size() != 3)
		flag = 0;
	if (args.values[0].colorset != "USER" || args.values[0].type != "var")
		flag = 0;
	if (args.values[1].colorset != "OPT" || args.values[0].type != "var")
		flag = 0;
	if (args.values[2].colorset != "ACT" || args.values[0].type != "int" || args.values[0].i != 1)
		flag = 0;
	if (flag == 0)
		return CValue();
	
	vector<CValue> results;
	results.push_back(args.values[0]);
	results.push_back(args.values[1]);
	return CValue("CONFLICT", 1, "item", results);
}

CValue CFun::CFromU(vector<CValue> argValues)
{
	if (argValues.size() != 1)
	{
		cout << "CFromP Error." << endl;
		return CValue();
	}
	CValue ui = argValues[0];

	int flag = 1;
	if (ui.colorset != "USER" || ui.type != "index" || ui.nickname != "user")
		flag = 0;
	if (flag == 0)
		return CValue();

	CValue result = CValue("CONFLICT", 1, "index", "conflict", ui.i);
	return result;
}

CValue CFun::calculateValue(vector<CValue> args)
{
	if (args.size() != count)
	{
		cout << "calculateValue Error." << endl;
		return CValue();
	}
	else
	{	
		if (name == "PFromUO")
			return PFromUO(args);
		else if (name == "DFromUO")
			return DFromUO(args);
		else if (name == "DFromP")
			return DFromP(args);
		else if (name == "CFromP")
			return CFromP(args);
		else if (name == "CFromU")
			return CFromU(args);
		else
		{
			cout << "calculateValue Error." << endl;
			return CValue();
		}
	}
}

string CFun::toString()
{
	return name;
}