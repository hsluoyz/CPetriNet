#include "CCPNet.h"
#include "CPlace.h"
#include "CTransition.h"
#include "CValue.h"
#include "CColorset.h"

void example1()
{
	CCPNet *cpnet = new CCPNet();
	cpnet->addPlace("P1", "int", CValue("int", 1, "int", 10));
	cpnet->addPlace("P2", "int");
	cpnet->addPlace("P3", "int");
	
	cpnet->addTransition("T1_2");
	cpnet->transitionAddFromPlaceAndValue("T1_2", "P1", CValue("int", 1, "int", 10));
	cpnet->transitionAddToPlaceAndValue("T1_2", "P2", CValue("int", 1, "int", 10));
	
	cpnet->addTransition("T2_3");
	cpnet->transitionAddFromPlaceAndValue("T2_3", "P2", CValue("int", 1, "int", 10));
	cpnet->transitionAddToPlaceAndValue("T2_3", "P3", CValue("int", 1, "int", 10));
	cpnet->initAllTransitions();
	
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

CValue doubleInt(vector<CValue> argValues)
{
	if (argValues.size() != 1)
	{
		cout << "doubleInt Error." << endl;
		return CValue();
	}
	CValue result = argValues[0];
	result.number *= 2;
	return result;
}

void example2()
{
	CCPNet *cpnet = new CCPNet();
	
	cpnet->addColorset(CColorset::int_colorset());
	cpnet->addColorset(CColorset::string_colorset());
	cpnet->addVar("i", "INT");
	cpnet->addVar("j", "INT");
	cpnet->addFun("doubleInt", doubleInt);

	cpnet->addPlace("P1", "INT", CValue("INT", 3, "int", 1));
	cpnet->addPlaceValue("P1", CValue("INT", 3, "int", 3));
	cpnet->addPlace("P2", "INT", CValue("INT", 2, "int", 2));
	cpnet->addPlace("P3", "INT", CValue("INT", 2, "int", 3));
	cpnet->addPlace("P4", "INT");
	cpnet->addPlace("P5", "INT");
	
	cpnet->addTransition("T1_4");
	cpnet->transitionAddFromPlaceAndValue("T1_4", "P1", cpnet->VAR(1, "i"));
	cpnet->transitionAddToPlaceAndValue("T1_4", "P4", cpnet->VAR(1, "i"));
	
	cpnet->addTransition("T2_4");
	cpnet->transitionAddFromPlaceAndValue("T2_4", "P2", cpnet->VAR(1, "i"));
	cpnet->transitionAddToPlaceAndValue("T2_4", "P4", cpnet->VAR(2, "i"));

	cpnet->addTransition("T3|4_5");
	cpnet->transitionAddFromPlaceAndValue("T3|4_5", "P3", cpnet->VAR(1, "i"));
	cpnet->transitionAddFromPlaceAndValue("T3|4_5", "P4", cpnet->VAR(2, "i"));
	cpnet->transitionAddToPlaceAndValue("T3|4_5", "P5", CValue("", 1, "fun", "doubleInt", cpnet->VAR(1, "i")));

	cpnet->initAllTransitions();
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

CValue PFromUO(vector<CValue> argValues)
{
	if (argValues.size() != 2)
	{
		cout << "PFromUO Error." << endl;
		return CValue();
	}
	CValue u = argValues[0];
	CValue t = argValues[1];

	int flag = 1;
	if (u.colorset != "USER" || u.type != "index" || u.nickname != "user")
		flag = 0;
	if (t.colorset != "OPT" || t.type != "enum")
		flag = 0;
	if (flag == 0)
	{
		cout << "PFromUO Error." << endl;
		return CValue();
	}

	vector<CValue> results;
	results.push_back(u);
	results.push_back(t);
	results.push_back(CValue("ACT", 1, "int", 1));
	return CValue("PERMISSION", 1, "item", results);
}

CValue DFromUO(vector<CValue> argValues)
{
	if (argValues.size() != 2)
	{
		cout << "DFromUO Error." << endl;
		return CValue();
	}
	CValue u = argValues[0];
	CValue t = argValues[1];

	int flag = 1;
	if (u.colorset != "USER" || u.type != "index" || u.nickname != "user")
		flag = 0;
	if (t.colorset != "OPT" || t.type != "enum")
		flag = 0;
	if (flag == 0)
	{
		cout << "DFromUO Error." << endl;
		return CValue();
	}
	
	vector<CValue> results;
	results.push_back(u);
	results.push_back(t);
	results.push_back(CValue("ACT", 1, "int", 0));
	return CValue("PERMISSION", 1, "item", results);
}

CValue DFromP(vector<CValue> argValues)
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
	if (args.values[0].colorset != "USER" || args.values[0].type != "index" || args.values[0].nickname != "user")
		flag = 0;
	if (args.values[1].colorset != "OPT" || args.values[1].type != "enum")
		flag = 0;
	if (args.values[2].colorset != "ACT" || args.values[2].type != "int" || args.values[2].i != 1)
		flag = 0;
	if (flag == 0)
	{
		cout << "DFromP Error." << endl;
		return CValue();
	}

	vector<CValue> results;
	results.push_back(args.values[0]);
	results.push_back(args.values[1]);
	results.push_back(CValue("ACT", 1, "int", 0));
	return CValue("PERMISSION", 1, "item", results);
}

CValue CFromP(vector<CValue> argValues)
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
	if (args.values[0].colorset != "USER" || args.values[0].type != "index" || args.values[0].nickname != "user")
		flag = 0;
	if (args.values[1].colorset != "OPT" || args.values[1].type != "enum")
		flag = 0;
	if (args.values[2].colorset != "ACT" || args.values[2].type != "int" || args.values[2].i != 1)
		flag = 0;
	if (flag == 0)
	{
		cout << "CFromP Error." << endl;
		return CValue();
	}
	
	vector<CValue> results;
	results.push_back(args.values[0]);
	results.push_back(args.values[1]);
	return CValue("CONFLICT", 1, "item", results);
}

CValue CFromU(vector<CValue> argValues)
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
	{
		cout << "CFromU Error." << endl;
		return CValue();
	}
	
	CValue result = CValue("CONFLICT", 1, "index", "conflict", ui.i);
	return result;
}

void RBAC_AC_example()
{
	CCPNet *cpnet = new CCPNet();
	
	cpnet->addColorset(new CColorset("USER", "index", "user", 0, 65535));
	cpnet->addColorset(new CColorset("OPT", "enum", "r", "w", "x"));
	cpnet->addColorset(new CColorset("ACT", "int", 0, 1));
	cpnet->addColorset(new CColorset("PERMISSION", "item", cpnet->getColorset("USER"), cpnet->getColorset("OPT"), cpnet->getColorset("ACT")));
	cpnet->addColorset(new CColorset("CONFLICT", "item", cpnet->getColorset("USER"), cpnet->getColorset("OPT")));

	CColorset *colorset = cpnet->getColorset("USER");

	cpnet->addVar("u", "USER");
	cpnet->addVar("t", "OPT");
	cpnet->addVar("p", "PERMISSION");
	cpnet->addFun("PFromUO", PFromUO);
	cpnet->addFun("DFromUO", DFromUO);
	cpnet->addFun("DFromP", DFromP);
	cpnet->addFun("CFromP", CFromP);
	
	cpnet->addPlace("U1", "USER", CValue("USER", 1, "index", "user", 1));
	cpnet->addPlace("U2", "USER", CValue("USER", 1, "index", "user", 2));
	cpnet->addPlace("R1", "USER");
	cpnet->addPlace("R2", "USER");
	cpnet->addPlace("R3", "USER");
	cpnet->addPlace("R4", "USER");
	cpnet->addPlace("Write", "OPT", CValue("OPT", 1, "enum", "w"));
	cpnet->addPlace("Res1_Permit", "PERMISSION");
	cpnet->addPlace("Res1_Deny", "PERMISSION");
	cpnet->addPlace("Res1", "CONFLICT");
	
	cpnet->addTransition("T:U1-R1");
	cpnet->transitionAddFromPlaceAndValue("T:U1-R1", "U1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U1-R1", "R1", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:U2-R2");
	cpnet->transitionAddFromPlaceAndValue("T:U2-R2", "U2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U2-R2", "R2", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:R1|Res1_Permit");
	cpnet->transitionAddFromPlaceAndValue("T:R1|Res1_Permit", "R1", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R1|Res1_Permit", "Write", cpnet->VAR(1, "t"));
	cpnet->transitionAddToPlaceAndValue("T:R1|Res1_Permit", "Res1_Permit", cpnet->FUN("PFromUO", "u", "t"));
	cpnet->transitionAddToPlaceAndValue("T:R1|Res1_Permit", "R3", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1|Res1_Permit", "Write", cpnet->VAR(1, "t"));

	cpnet->addTransition("T:R2|Res1_PermitDeny");
	cpnet->transitionAddFromPlaceAndValue("T:R2|Res1_PermitDeny", "R2", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R2|Res1_PermitDeny", "Write", cpnet->VAR(1, "t"));
	cpnet->transitionAddToPlaceAndValue("T:R2|Res1_PermitDeny", "Res1_Permit", cpnet->FUN("PFromUO", "u", "t"));
	cpnet->transitionAddToPlaceAndValue("T:R2|Res1_PermitDeny", "Res1_Deny", cpnet->FUN("DFromUO", "u", "t"));
	cpnet->transitionAddToPlaceAndValue("T:R2|Res1_PermitDeny", "R4", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R2|Res1_PermitDeny", "Write", cpnet->VAR(1, "t"));

	cpnet->addTransition("T:R3|Res1_Permit");
	cpnet->transitionAddFromPlaceAndValue("T:R3|Res1_Permit", "R3", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R3|Res1_Permit", "Write", cpnet->VAR(1, "t"));
	cpnet->transitionAddToPlaceAndValue("T:R3|Res1_Permit", "Res1_Permit", cpnet->FUN("PFromUO", "u", "t"));
	cpnet->transitionAddToPlaceAndValue("T:R3|Res1_Permit", "Write", cpnet->VAR(1, "t"));

	cpnet->addTransition("T:R4|Res1_Deny");
	cpnet->transitionAddFromPlaceAndValue("T:R4|Res1_Deny", "R4", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R4|Res1_Deny", "Write", cpnet->VAR(1, "t"));
	cpnet->transitionAddToPlaceAndValue("T:R4|Res1_Deny", "Res1_Deny", cpnet->FUN("DFromUO", "u", "t"));
	cpnet->transitionAddToPlaceAndValue("T:R4|Res1_Deny", "Write", cpnet->VAR(1, "t"));

	cpnet->addTransition("T:Res1_PermitDeny|Res1");
	cpnet->transitionAddFromPlaceAndValue("T:Res1_PermitDeny|Res1", "Res1_Permit", cpnet->VAR(1, "p"));
	cpnet->transitionAddFromPlaceAndValue("T:Res1_PermitDeny|Res1", "Res1_Deny", cpnet->FUN("DFromP", "p"));
	cpnet->transitionAddToPlaceAndValue("T:Res1_PermitDeny|Res1", "Res1", cpnet->FUN("CFromP", "p"));
	
	cpnet->initAllTransitions();
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

void RBAC_SODC_example()
{
	CCPNet *cpnet = new CCPNet();
	
	cpnet->addColorset(new CColorset("USER", "index", "user", 0, 65535));
	cpnet->addColorset(new CColorset("CONFLICT", "index", "conflict", 0, 65535));
	cpnet->addVar("u", "USER");
	cpnet->addFun("CFromU", CFromU);
	
	cpnet->addPlace("U1", "USER", CValue("USER", 1, "index", "user", 1));
	cpnet->addPlace("U2", "USER", CValue("USER", 1, "index", "user", 2));
	cpnet->addPlace("R1", "USER");
	cpnet->addPlace("R2", "USER");
	cpnet->addPlace("R3", "USER");
	cpnet->addPlace("R4", "USER");
	cpnet->addPlace("R1_USER", "USER");
	cpnet->addPlace("R2_USER", "USER");
	cpnet->addPlace("Conflict", "CONFLICT");
	
	cpnet->addTransition("T:U1-R1");
	cpnet->transitionAddFromPlaceAndValue("T:U1-R1", "U1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U1-R1", "R1", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:U2-R1|R2");
	cpnet->transitionAddFromPlaceAndValue("T:U2-R1|R2", "U2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U2-R1|R2", "R1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U2-R1|R2", "R2", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:R1-R1_USER");
	cpnet->transitionAddFromPlaceAndValue("T:R1-R1_USER", "R1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1-R1_USER", "R3", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1-R1_USER", "R1_USER", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:R2-R2_USER");
	cpnet->transitionAddFromPlaceAndValue("T:R2-R2_USER", "R2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R2-R2_USER", "R4", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R2-R2_USER", "R2_USER", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:R1_USER|R2_USER-Conflict");
	cpnet->transitionAddFromPlaceAndValue("T:R1_USER|R2_USER-Conflict", "R1_USER", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R1_USER|R2_USER-Conflict", "R2_USER", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1_USER|R2_USER-Conflict", "Conflict", CValue("", 1, "fun", "CFromU", cpnet->VAR(1, "u")));
	
	cpnet->initAllTransitions();
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

void RBAC_IRC_example()
{
	CCPNet *cpnet = new CCPNet();
	
	cpnet->addColorset(new CColorset("USER", "index", "user", 0, 65535));
	cpnet->addColorset(new CColorset("COUNT", "enum", "count"));
	cpnet->addColorset(new CColorset("CONFLICT", "index", "conflict", 0, 65535));
	cpnet->addVar("u", "USER");
	cpnet->addFun("CFromU", CFromU);
	
	cpnet->addPlace("R1", "USER", CValue("USER", 1, "index", "user", 1));
	cpnet->addPlace("R2", "USER");
	cpnet->addPlace("R3", "USER");
	cpnet->addPlace("R4", "USER");
	cpnet->addPlace("CountMax", "COUNT", CValue("COUNT", 2, "enum", "count"));
	cpnet->addPlace("Count", "USER");
	cpnet->addPlace("Conflict", "CONFLICT");
	
	cpnet->addTransition("T:R1-R2");
	cpnet->transitionAddFromPlaceAndValue("T:R1-R2", "R1", cpnet->VAR(1, "u"));
	cpnet->transitionAddFromPlaceAndValue("T:R1-R2", "CountMax", CValue("COUNT", 1, "enum", "count"));
	cpnet->transitionAddToPlaceAndValue("T:R1-R2", "R2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1-R2", "Count", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:R2-R3");
	cpnet->transitionAddFromPlaceAndValue("T:R2-R3", "R2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R2-R3", "R3", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:R3-R4");
	cpnet->transitionAddFromPlaceAndValue("T:R3-R4", "R3", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R3-R4", "R4", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:R4-R1");
	cpnet->transitionAddFromPlaceAndValue("T:R4-R1", "R4", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R4-R1", "R1", cpnet->VAR(1, "u"));

	cpnet->addTransition("T:Count-Conflict");
	cpnet->transitionAddFromPlaceAndValue("T:Count-Conflict", "Count", cpnet->VAR(2, "u"));
	cpnet->transitionAddToPlaceAndValue("T:Count-Conflict", "Conflict", CValue("", 1, "fun", "CFromU", cpnet->VAR(1, "u")));
	
	cpnet->initAllTransitions();
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

void RBAC_UCC_example()
{
	CCPNet *cpnet = new CCPNet();
	int max = 2;
	
	cpnet->addColorset(new CColorset("USER", "index", "user", 0, 65535));
	cpnet->addColorset(new CColorset("COUNT", "enum", "count"));
	cpnet->addColorset(new CColorset("CONFLICT", "enum", "conflict"));
	cpnet->addVar("u", "USER");
	
	cpnet->addPlace("U1", "USER", CValue("USER", 1, "index", "user", 1));
	cpnet->addPlace("U2", "USER", CValue("USER", 1, "index", "user", 2));
	cpnet->addPlace("U3", "USER", CValue("USER", 1, "index", "user", 3));
	cpnet->addPlace("R1", "USER");
	cpnet->addPlace("R2", "USER");
	cpnet->addPlace("Count", "COUNT");
	cpnet->addPlace("Conflict", "CONFLICT");
	
	cpnet->addTransition("T:U1-R1");
	cpnet->transitionAddFromPlaceAndValue("T:U1-R1", "U1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U1-R1", "R1", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:R1-R2");
	cpnet->transitionAddFromPlaceAndValue("T:R1-R2", "R1", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R1-R2", "R2", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:U2-R2");
	cpnet->transitionAddFromPlaceAndValue("T:U2-R2", "U2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U2-R2", "R2", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:U3-R2");
	cpnet->transitionAddFromPlaceAndValue("T:U3-R2", "U3", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:U3-R2", "R2", cpnet->VAR(1, "u"));
	
	cpnet->addTransition("T:R2-Count");
	cpnet->transitionAddFromPlaceAndValue("T:R2-Count", "R2", cpnet->VAR(1, "u"));
	cpnet->transitionAddToPlaceAndValue("T:R2-Count", "Count", CValue("COUNT", 1, "enum", "count"));

	cpnet->addTransition("T:Count-Conflict");
	cpnet->transitionAddFromPlaceAndValue("T:Count-Conflict", "Count", CValue("COUNT", max + 1, "enum", "count"));
	cpnet->transitionAddToPlaceAndValue("T:Count-Conflict", "Conflict", CValue("CONFLICT", 1, "enum", "conflict"));
	
	cpnet->initAllTransitions();
	cpnet->fireToEnd();
	
	cout << cpnet->places2String();
}

int main()
{
	RBAC_AC_example();

	return 0;
}