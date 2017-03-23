#include "CTransition.h"
#include "CCPNet.h"
#include "CArc.h"
#include "CVar.h"
#include "CPlace.h"

CTransition::CTransition(string a_name, CCPNet *a_cpnet)
{
	name = a_name;
	cpnet = a_cpnet;
}

void CTransition::addFromPlaceAndValue(string strPlace, CValue value)
{
	CPlace *place = cpnet->getPlace(strPlace);
	fromPlaces.push_back(place);
	CArc *arc = new CArc(value, place);
	fromArcs.push_back(arc);
	fromArcsInit.push_back(0);
}

void CTransition::addToPlaceAndValue(string strPlace, CValue value)
{
	CPlace *place = cpnet->getPlace(strPlace);
	toPlaces.push_back(place);
	CArc *arc = new CArc(value, place);
	toArcs.push_back(arc);
}

int CTransition::findVar(CVar *var)
{
	for (int i = 0; i < vars.size(); i ++)
	{
		if (vars[i]->colorset == var->colorset && vars[i]->name == var->name)
		{
			return 1;
		}
	}
	return 0;
}

CVar* CTransition::addVar(string a_name)
{
	CVar *var = cpnet->getVar(a_name);
	if (var == NULL)
	{
		cout << "addVar Error." << endl;
		return NULL;
	}
	else
	{
		if (findVar(var) == 0)
		{
			CVar *copyVar = var->copy();
			vars.push_back(copyVar);
			return copyVar;
		}
		else
		{
			return NULL;
		}
	}
}

void CTransition::addVarFromValue(CArc *arc, CValue &value)
{
	if (value.type == "var")
	{
		CVar *var = addVar(value.varname);
		if (var != NULL)
		{
			var->setInitArc(arc);
		}
	}
	else if (value.type == "item")
	{
		for (int i = 0; i < value.values.size(); i ++)
		{
			addVarFromValue(arc, value.values[i]);
		}
	}
}

void CTransition::addAllVars()
{
	for (int i = 0; i < fromArcs.size(); i ++)
	{
		addVarFromValue(fromArcs[i], fromArcs[i]->value);
	}
}

void CTransition::initAlterValues()
{
	for (int i = 0; i < vars.size(); i ++)
	{
		vars[i]->clearAlterValues();

		CArc *arc = vars[i]->arc;
		CPlace *place = arc->place;
		CValue value = arc->value;

		for (int j = 0; j < place->values.size(); j ++)
		{
			if (value.colorset != place->values[j].colorset)
			{
				cout << "initAlterValues Error." << endl;
				return;
			}
			if (value.number <= place->values[j].number)
			{
				vars[i]->addAlterValue(place->values[j]);
			}
		}
	}
}

CVar* CTransition::varname2Var(string strVarname)
{
	for (int i = 0; i < vars.size(); i ++)
	{
		if (vars[i]->name == strVarname)
		{
			return vars[i];
		}
	}
	cout << "varname2Var Error." << endl;
	return NULL;
}

CValue CTransition::varname2Value(string strVarname)
{
	CVar *var = varname2Var(strVarname);
	if (var == NULL)
	{
		cout << "varname2Value Error." << endl;
		return CValue();
	}
	if (var->alter_index >= var->alter_values.size())
	{
		cout << "varname2Value Error." << endl;
		return CValue();
	}
	return var->alter_values[var->alter_index];
}

int CTransition::okSubArc(CArc *arc)
{
	CValue value = arc->value.removeFunAndVar(this);
	return arc->place->okTakeToken(value);
}

int CTransition::subArc(CArc *arc)
{
	CValue value = arc->value.removeFunAndVar(this);
	return arc->place->takeToken(value);
}

int CTransition::addArc(CArc *arc)
{
	CValue value = arc->value.removeFunAndVar(this);
	return arc->place->putToken(value);
}

void CTransition::init()
{
	addAllVars();
}

int CTransition::fire()
{
	if (name == "T:R1_USER|R2_USER-Conflict")
	{
		int a = 1;
	}
	initAlterValues();

	vector<int> avlSizes;
	vector<CVar*> avlVars;
	for (int i = 0; i < vars.size(); i ++)
	{
		if (vars[i]->alter_values.size() == 0)
		{
			return 0;
		}
		avlSizes.push_back(vars[i]->alter_values.size());
		avlVars.push_back(vars[i]);
	}
	int currentAVLIndex = 0;

	int fireFlag = 0;
	while (1)
	{
		int flag = 1;
		for (int i = 0; i < fromArcs.size(); i ++)
		{
			if (okSubArc(fromArcs[i]) != 1)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			for (i = 0; i < fromArcs.size(); i ++)
			{
				subArc(fromArcs[i]);
			}
			for (i = 0; i < toArcs.size(); i ++)
			{
				addArc(toArcs[i]);
			}
			fireFlag = 1;
			break;
		}
		else
		{
			currentAVLIndex ++;
			if (avlSizes.size() == 0)
			{
				fireFlag = 0;
				break;
			}
			else if (currentAVLIndex == avlSizes[avlSizes.size() - 1])
			{
				currentAVLIndex = 0;
				avlSizes.pop_back();
				avlVars.pop_back();
				if (avlSizes.size() == 0)
				{
					fireFlag = 0;
					break;
				}
			}
			avlVars[avlVars.size() - 1]->alter_index = currentAVLIndex;
		}
	}

	return fireFlag;
}