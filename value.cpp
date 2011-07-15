#include "value.h"

namespace libjson {

Value::Type Value::getType()
{
	return t;
}

bool Value::asBool()
{
	return b;
}

double Value::asDouble()
{
	return d;
}

int Value::asInt()
{
	return i;
}

Object* Value::asObject()
{
	return obj;
}

string Value::asString()
{
	return str;
}

Vector* Value::asVector()
{
	return v;
}

}
