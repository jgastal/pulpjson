#include "parser.h"
#include "value.h"

#define BOOST_TEST_MODULE Parser
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>




// #include <iostream>
// 	for(Object::iterator it = obj->begin(); it != obj->end(); it++)
// 		std::cout << "key: \"" <<  (*it).first << "\"" << std::endl;





using namespace libjson;

BOOST_AUTO_TEST_CASE( empty )
{
	Parser p("{}", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 0);
}

BOOST_AUTO_TEST_CASE( int_prop )
{
	Parser p("{ a: 0, b: 1, c:10, d: 10000, e: -40}", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 5);
	BOOST_REQUIRE_EQUAL((*obj)["a"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*obj)["b"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*obj)["c"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*obj)["d"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*obj)["e"]->getType(), Value::INT);

	BOOST_CHECK_EQUAL((*obj)["a"]->asInt(), 0);
	BOOST_CHECK_EQUAL((*obj)["b"]->asInt(), 1);
	BOOST_CHECK_EQUAL((*obj)["c"]->asInt(), 10);
	BOOST_CHECK_EQUAL((*obj)["d"]->asInt(), 10000);
	BOOST_CHECK_EQUAL((*obj)["e"]->asInt(), -40);
}

BOOST_AUTO_TEST_CASE( bool_prop )
{
	Parser p("{ a: true, b:true, c: false, d:false}", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 4);
	BOOST_REQUIRE_EQUAL((*obj)["a"]->getType(), Value::BOOL);
	BOOST_REQUIRE_EQUAL((*obj)["b"]->getType(), Value::BOOL);
	BOOST_REQUIRE_EQUAL((*obj)["c"]->getType(), Value::BOOL);
	BOOST_REQUIRE_EQUAL((*obj)["d"]->getType(), Value::BOOL);

	BOOST_CHECK_EQUAL((*obj)["a"]->asBool(), true);
	BOOST_CHECK_EQUAL((*obj)["b"]->asBool(), true);
	BOOST_CHECK_EQUAL((*obj)["c"]->asBool(), false);
	BOOST_CHECK_EQUAL((*obj)["d"]->asBool(), false);
}

BOOST_AUTO_TEST_CASE( string_prop )
{
	Parser p("{ a: \"\", b: \"asdf\", c:\"123\", d: \"'!@#jlk5%*&(&*\", e:\"ççáé\" }", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 5);
	BOOST_REQUIRE_EQUAL((*obj)["a"]->getType(), Value::STRING);
	BOOST_REQUIRE_EQUAL((*obj)["b"]->getType(), Value::STRING);
	BOOST_REQUIRE_EQUAL((*obj)["c"]->getType(), Value::STRING);
	BOOST_REQUIRE_EQUAL((*obj)["d"]->getType(), Value::STRING);
	BOOST_REQUIRE_EQUAL((*obj)["e"]->getType(), Value::STRING);

	BOOST_CHECK_EQUAL((*obj)["a"]->asString().compare(""), 0);
	BOOST_CHECK_EQUAL((*obj)["b"]->asString().compare("asdf"), 0);
	BOOST_CHECK_EQUAL((*obj)["c"]->asString().compare("123"), 0);
	BOOST_CHECK_EQUAL((*obj)["d"]->asString().compare("'!@#jlk5%*&(&*"), 0);
	BOOST_CHECK_EQUAL((*obj)["e"]->asString().compare("ççáé"), 0);
}

BOOST_AUTO_TEST_CASE( double_prop )
{
	Parser p("{ a: 0.8, b: -1.0, c:0.7644, d: 10000.90, e: -40.123, f: 1.23456789}", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 6);
	BOOST_REQUIRE_EQUAL((*obj)["a"]->getType(), Value::DOUBLE);
	BOOST_REQUIRE_EQUAL((*obj)["b"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*obj)["c"]->getType(), Value::DOUBLE);
	BOOST_REQUIRE_EQUAL((*obj)["d"]->getType(), Value::DOUBLE);
	BOOST_REQUIRE_EQUAL((*obj)["e"]->getType(), Value::DOUBLE);
	BOOST_REQUIRE_EQUAL((*obj)["f"]->getType(), Value::DOUBLE);

	BOOST_CHECK_EQUAL((*obj)["a"]->asDouble(), 0.8);
	BOOST_CHECK_EQUAL((*obj)["b"]->asInt(), -1);
	BOOST_CHECK_EQUAL((*obj)["c"]->asDouble(), 0.7644);
	BOOST_CHECK_EQUAL((*obj)["d"]->asDouble(), 10000.90);
	BOOST_CHECK_EQUAL((*obj)["e"]->asDouble(), -40.123);
	BOOST_CHECK_EQUAL((*obj)["f"]->asDouble(), 1.23456789);
}

BOOST_AUTO_TEST_CASE( object_prop )
{
	Parser p("{ a: {}, b: {a: {a: { a: {a: 1234, b: \"asdf\", c: true, d:false, e: 0.7}}}}, c: {a: 1234, b: \"asdf\", c: true, d:false, e: 0.654} }", false);
	Object *obj = p.getRootObject();

	BOOST_REQUIRE_EQUAL(obj->size(), 3);
	BOOST_REQUIRE_EQUAL((*obj)["a"]->getType(), Value::OBJECT);
	BOOST_REQUIRE_EQUAL((*obj)["b"]->getType(), Value::OBJECT);
	BOOST_REQUIRE_EQUAL((*obj)["c"]->getType(), Value::OBJECT);

	BOOST_CHECK_EQUAL((*obj)["a"]->asObject()->size(), 0);

	Object *b = (*obj)["b"]->asObject();
	BOOST_REQUIRE_EQUAL(b->size(), 1);
	BOOST_REQUIRE_EQUAL((*b)["a"]->getType(), Value::OBJECT);

	Object *ba = (*b)["a"]->asObject();
	BOOST_REQUIRE_EQUAL(ba->size(), 1);
	BOOST_REQUIRE_EQUAL((*ba)["a"]->getType(), Value::OBJECT);

	Object *baa = (*ba)["a"]->asObject();
	BOOST_REQUIRE_EQUAL(baa->size(), 1);
	BOOST_REQUIRE_EQUAL((*baa)["a"]->getType(), Value::OBJECT);

	Object *baaa = (*baa)["a"]->asObject();
	BOOST_REQUIRE_EQUAL(baaa->size(), 5);
	BOOST_REQUIRE_EQUAL((*baaa)["a"]->getType(), Value::INT);
	BOOST_REQUIRE_EQUAL((*baaa)["b"]->getType(), Value::STRING);
	BOOST_REQUIRE_EQUAL((*baaa)["c"]->getType(), Value::BOOL);
	BOOST_REQUIRE_EQUAL((*baaa)["d"]->getType(), Value::BOOL);
	BOOST_REQUIRE_EQUAL((*baaa)["e"]->getType(), Value::DOUBLE);

	BOOST_REQUIRE_EQUAL((*baaa)["a"]->asInt(), 1234);
	BOOST_REQUIRE_EQUAL((*baaa)["b"]->asString().compare("asdf"), 0);
	BOOST_REQUIRE_EQUAL((*baaa)["c"]->asBool(), true);
	BOOST_REQUIRE_EQUAL((*baaa)["d"]->asBool(), false);
	BOOST_REQUIRE_EQUAL((*baaa)["e"]->asDouble(), 0.7);

	Object *c = (*obj)["c"]->asObject();
	BOOST_REQUIRE_EQUAL(c->size(), 5);
	BOOST_REQUIRE_EQUAL((*c)["a"]->asInt(), 1234);
	BOOST_REQUIRE_EQUAL((*c)["b"]->asString().compare("asdf"), 0);
	BOOST_REQUIRE_EQUAL((*c)["c"]->asBool(), true);
	BOOST_REQUIRE_EQUAL((*c)["d"]->asBool(), false);
	BOOST_REQUIRE_EQUAL((*c)["e"]->asDouble(), 0.654);
}
