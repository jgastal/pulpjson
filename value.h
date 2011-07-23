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

#ifndef VALUE_H
#define VALUE_H

#include <map>
#include <string>
#include "object.h"

using namespace std;

namespace pulpjson {

/**
 * @brief Class that encapsulates a JSON value.
 *
 * @warning There is no public constructor, the only way to get an instance of Value is through @ref Parser.
 *
 * The use of this class is fairly straight forward process, this shows a function that prints a value(recursively):
 * @code
 * //v must be a *Value instance gotten from Parser
 * void print_value(Value v)
 * {
 * 	switch(v.getType())
 * 	{
 * 		case Value::INT:
 * 			std::cout << "v is of type int and has value " << v.asInt() << "!\n";
 * 			break;
 * 		case Value::DOUBLE:
 * 			std::cout << "v is of type double and has value " << v.asDouble() << "!\n";
 * 			break;
 * 		case Value::STRING:
 * 			std::cout << "v is of type string and has value " << v.asString() << "!\n";
 * 			break;
 * 		case Value::BOOL:
 * 			std::cout << "v is of type bool and has value " << v.asBool() << "!\n";
 * 			break;
 * 		case Value::VECTOR:
 * 			std::cout << "v is of type vector and has value: \n";
 * 			for(int i = 0; i < v.asVector().size(); i++)
 * 				print_value(v.asVector()[i]);
 * 			break;
 * 		case Value::OBJECT:
 * 			std::cout << "v is of type object and has value: \n";
 * 			for(Object::iterator it = v.asObject().begin(); it != v.asObject().end(); it++)
 * 				print_value((*it).second);
 * 	}
 * }
 * @endcode
 */
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
		Value(int i);
		Value(double d);
		Value(string str);
		Value(Object obj);
		Value(Vector v);
		Value(bool b);
		Type getType();
		string asString();
		int asInt();
		double asDouble();
		Object asObject();
		bool asBool();
		Vector asVector();
		string asJSON();

	private:
		Value() { };
		friend class Parser;
		friend class map<string, Value>;

		Type t;
		Object obj;
		Vector v;
		string str;
		double d;
		int i;
		bool b;
};

}

#endif // VALUE_H
