#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <vector>

using namespace std;

namespace libjson {

class Value;
typedef map<string, Value*> Object;
typedef vector<Value*> Vector;

class Parser
{
	public:
		Parser(const char *str, bool file = true);
		Object *getRootObject();

	private:
		Object *createObject(string &str);
		Value *createValue(string str);
		size_t findValueEnd(string str);
		Object *root;
};

}

#endif // PARSER_H
