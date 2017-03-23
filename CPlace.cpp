#include "CPlace.h"

CPlace::CPlace(string a_name, string a_colorset)
{
	name = a_name;
	colorset = a_colorset;
}

CPlace::CPlace(string a_name, string a_colorset, CValue a_value)
{
	name = a_name;
	colorset = a_colorset;
	values.push_back(a_value);
}

void CPlace::addValue(CValue a_value)
{
	values.push_back(a_value);
}

void CPlace::addFromTransition(CTransition *transition)
{
	froms.push_back(transition);
}

void CPlace::addToTransition(CTransition *transition)
{
	tos.push_back(transition);
}

int CPlace::putToken(CValue a_value)
{
	if (colorset != a_value.colorset)
	{
		cout << "putToken Error." << endl;
		return -1;
	}

	for (int i = 0; i < values.size(); i ++)
	{
		if (CValue::isIdentical(values[i], a_value) == 1)
		{
			values[i].number += a_value.number;
			return 1;
		}
	}
	values.push_back(a_value);
	return 1;
}

int CPlace::okTakeToken(CValue a_value)
{
	if (colorset != a_value.colorset)
	{
		cout << "okTakeToken Error." << endl;
		return -1;
	}
	
	for (int i = 0; i < values.size(); i ++)
	{
		if (CValue::isIdentical(values[i], a_value) == 1)
		{
			if (values[i].number < a_value.number)
				return 0;
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

int CPlace::takeToken(CValue a_value)
{
	if (colorset != a_value.colorset)
	{
		cout << "takeToken Error." << endl;
		return -1;
	}

	for (int i = 0; i < values.size(); i ++)
	{
		if (CValue::isIdentical(values[i], a_value) == 1)
		{
			if (values[i].number < a_value.number)
				return 0;
			else
			{
				values[i].number -= a_value.number;
				if (values[i].number == 0)
				{
					values.erase(&values[i]);
				}
				return 1;
			}
		}
	}
	return 0;
}

string CPlace::itos(int i)
{
	char cBuffer[10];
	itoa(i, cBuffer, 10);
	string s(cBuffer);
	return s;
}

string CPlace::toString()
{
	string strResult;
	strResult += ("name:" + name);
	strResult += (" colorset:" + colorset + "\n");
	for (int i = 0; i < values.size(); i ++)
	{
		strResult += ("value-" + itos(i) + ": ");
		strResult += values[i].toString();
		strResult += "\n";
	}
	return strResult;
}