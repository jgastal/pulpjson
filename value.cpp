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

#include "value.h"

namespace libjson {

/**
 * @brief Gets the type this @ref Value represents.
 * @returns The type of this @ref Value.
 */
Value::Type Value::getType()
{
	return t;
}

/**
 * @brief Gets this value as a boolean.
 * @returns This @ref Value as a bool
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref BOOL
 */
bool Value::asBool()
{
	return b;
}

/**
 * @brief Gets this value as a double.
 * @returns This @ref Value as a double
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref DOUBLE
 */
double Value::asDouble()
{
	return d;
}

/**
 * @brief Gets this value as an integer.
 * @returns This @ref Value as a int
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref INT
 */
int Value::asInt()
{
	return i;
}

/**
 * @brief Gets this value as an @ref Object.
 * @returns This @ref Value as an @ref Object
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref OBJECT
 */
Object Value::asObject()
{
	return obj;
}

/**
 * @brief Gets this value as a string.
 * @returns This @ref Value as a string
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref STRING
 */
string Value::asString()
{
	return str;
}

/**
 * @brief Gets this value as a @ref Vector.
 * @returns This @ref Value as a @ref Vector
 *
 * @warning Undefined behavior if this @ref Value is not of type @ref VECTOR
 */
Vector Value::asVector()
{
	return v;
}

}
