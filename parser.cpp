#include "parser.h"

#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

#include <iostream>

#include "value.h"

namespace libjson {

Parser::Parser(const char* str, bool file) : root(NULL)
{
	string json;
	if(file)
	{
		ifstream file(str, ifstream::in);
		string str;
		if(!file.is_open())
			return;

		while(!file.eof())
		{
			string line;
			file >> line;
			str.append(line);
		}
	}
	else
		json = str;

	root = createObject(json);
}

Object *Parser::getRootObject()
{
	return root;
}

Object *Parser::createObject(string &str)
{
	if(str[0] != '{')
		return NULL;

	str = str.substr(str.find_first_not_of("{"));
	Object *obj = new Object();

	while(str[0] != '}')
	{
		str = str.substr(str.find_first_not_of(" \t\n\r"));
		size_t idxStart = str.find(':');
		size_t idxEnd = findValueEnd(str.substr(idxStart + 1));
		(*obj)[str.substr(0, idxStart)] = createValue(str.substr(idxStart + 1, idxEnd));
		idxEnd = str.find(',', idxStart + 1 + idxEnd);
		if(idxEnd == string::npos)
			break;
		else
			str = str.substr(idxEnd + 1);
	}
	return obj;
}

Value *Parser::createValue(string str)
{
	Value *v = new Value();

	str = str.substr(str.find_first_not_of(" \t\n\r"));
	if(str[0] == '{')
	{
		v->t = Value::OBJECT;
		v->obj = createObject(str);
	}
	else if(str[0] == '"')
	{
		v->t = Value::STRING;
		v->str = str.substr(1, str.find('"', 1) - 1);
	}
	else if(str.find("true") == 0)
	{
		v->t = Value::BOOL;
		v->b = true;
	}
	else if(str.find("false") == 0)
	{
		v->t = Value::BOOL;
		v->b = false;
	}
	else if(str.find_first_of("0123456789-") == 0)
	{
		double d = atof(str.c_str());
		if(d == ceil(d))
		{
			v->t = Value::INT;
			v->i = ceil(d);
		}
		else
		{
			v->t = Value::DOUBLE;
			v->d = d;
		}
	}
	else if(str[0] == '[')
	{
		v->t = Value::VECTOR;
		v->v = new vector<Value*>();
		while(true)
		{
			int idx = str.find(',');
			if(idx == string::npos)
				break;
			v->v->push_back(createValue(str.substr(1, idx)));
			str = str.substr(idx + 1);
		}
	}
	else
		return NULL;

	return v;
}

size_t Parser::findValueEnd(string str)
{
	size_t idx = str.find_first_not_of(" \t\r\n");
	short int nesting = 1;
	if(str[idx] == '{')
	{
		while(nesting)
		{
			idx = str.find_first_of("{}", idx + 1);
			if(str[idx] == '{')
				nesting++;
			else 
				nesting--;
		}
		
	}
	else if(str[idx] == '[')
	{
		while(nesting)
		{
			idx = str.find_first_of("[]", idx + 1);
			if(str[idx] == '[')
				nesting++;
			else
				nesting--;
		}
	}
	else if(str[idx] == '"')
	{
		while(1)
		{
			idx = str.find('"', idx + 1);
			if(str[idx - 1] != '\\')
				break;
		}
	}
	else
		idx = str.find(',') - 1;

	return ++idx;
}

}