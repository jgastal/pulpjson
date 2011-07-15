#ifndef VALUE_H
#define VALUE_H

#include <map>
#include <string>
#include "parser.h"

using namespace std;

namespace libjson {

class Value
{
	public:
		enum Type {
			OBJECT,
			INT,
			DOUBLE,
			STRING,
			BOOL,
			VECTOR
		};
		Type getType();
		string asString();
		int asInt();
		double asDouble();
		Object *asObject();
		bool asBool();
		Vector *asVector();

	private:
		Value() { };
		friend class Parser;

		Type t;
		Object *obj;
		Vector *v;
		string str;
		double d;
		int i;
		bool b;
};

}

#endif // VALUE_H
