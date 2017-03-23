#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
using namespace std;

class CVal
{
public:
	string name;
	int value;

public:
	CVal(string a_name, int a_value);
};