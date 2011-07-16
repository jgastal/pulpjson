/*
 * Copyright (c) 2011, Jonas M. Gastal
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Jonas M. Gastal nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Jonas M. Gastal BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "parser.h"

#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "value.h"
#include "jsonexception.hpp"

namespace libjson {

Parser::Parser(const char* str, bool file)
{
	string json;
	if(file)
	{
		ifstream file(str, ifstream::in);
		string str;
		if(!file.is_open())
			throw ios_base::failure("File not found");

		while(!file.eof())
		{
			string line;
			file >> line;
			str.append(line);
		}
		file.close();
	}
	else
		json = str;

	root = createObject(json);
}

Object Parser::getRootObject()
{
	return root;
}

Object Parser::createObject(string &str)
{
	str = str.substr(str.find_first_not_of(" \t\n\r"));
	if(str[0] != '{')
		throw JSONException(string("Objects must start with '{' found '") + str[0] + "' instead.");

	str = str.substr(str.find_first_not_of("{"));
	Object obj;

	while(str[0] != '}')
	{
		str = str.substr(str.find_first_not_of(" \t\n\r"));
		size_t idxStart = str.find(':');
		size_t idxEnd = findValueEnd(str.substr(idxStart + 1));
		obj[str.substr(0, idxStart)] = createValue(str.substr(idxStart + 1, idxEnd));
		idxEnd = str.find(',', idxStart + 1 + idxEnd);
		if(idxEnd == string::npos)
			break;
		else
			str = str.substr(idxEnd + 1);
	}
	return obj;
}

Value Parser::createValue(string str)
{
	Value v;

	str = str.substr(str.find_first_not_of(" \t\n\r"));
	if(str[0] == '{')
	{
		v.t = Value::OBJECT;
		v.obj = createObject(str);
	}
	else if(str[0] == '"')
	{
		v.t = Value::STRING;
		v.str = str.substr(1, str.find('"', 1) - 1);
	}
	else if(str.find("true") == 0)
	{
		v.t = Value::BOOL;
		v.b = true;
	}
	else if(str.find("false") == 0)
	{
		v.t = Value::BOOL;
		v.b = false;
	}
	else if(str.find_first_of("0123456789-") == 0)
	{
		double d = atof(str.c_str());
		if(d == ceil(d))
		{
			v.t = Value::INT;
			v.i = ceil(d);
		}
		else
		{
			v.t = Value::DOUBLE;
			v.d = d;
		}
	}
	else if(str[0] == '[')
	{
		v.t = Value::VECTOR;
		v.v = Vector();

		str = str.substr(1);
		while(str[0] != ']')
		{
			size_t idx = findValueEnd(str);
			if(idx == string::npos)
				break;
			v.v.push_back(createValue(str.substr(0, idx)));
			str = str.substr(idx + 1);
		}
	}
	else
		throw JSONException("Can't parse \"" + str + "\" as a JSON value.");

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
		idx = str.find_first_of(",]}") - 1;

	return ++idx;
}

}