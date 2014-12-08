#include <boost/test/unit_test.hpp>

#include "sketch_string.h"
#include <string>

void CompareStr(const std::string& stdString, const SketchStl::string& string, const char* c_string) {
    size_t size = 0;
    const char* begin = c_string;
    while (*begin++) {
        size += 1;
    }

    const char* stdStr = stdString.c_str();
    const char* str = string.c_str();

    BOOST_REQUIRE(stdStr != nullptr);
    BOOST_REQUIRE(str != nullptr);
    BOOST_REQUIRE(stdString.size() == size && string.size() == size);
    BOOST_REQUIRE(strcmp(stdStr, str) == 0);
}

BOOST_AUTO_TEST_CASE(string_default_constructor)
{
    std::string stdString;
    SketchStl::string string;

    CompareStr(stdString, string, "");
}

BOOST_AUTO_TEST_CASE(string_c_string_constructor)
{
    std::string stdStringEmpty("");
    SketchStl::string stringEmpty("");

    CompareStr(stdStringEmpty, stringEmpty, "");

    std::string stdString("Hello World");
    SketchStl::string string("Hello World");

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_copy_constructor)
{
    std::string stdString("Hello World");
    SketchStl::string string("Hello World");

    std::string copyStdString(stdString);
    SketchStl::string copyString(string);

    CompareStr(copyStdString, copyString, "Hello World");

    std::string stdStringEmpty;
    SketchStl::string stringEmpty;

    std::string copyStdStringEmpty(stdStringEmpty);
    SketchStl::string copyStringEmpty(stringEmpty);

    CompareStr(copyStdStringEmpty, copyStringEmpty, "");
}

BOOST_AUTO_TEST_CASE(string_substring_constructor)
{
    std::string stdString("Hello World");
    SketchStl::string string("Hello World");

    std::string subStdStringFull(stdString, 0);
    SketchStl::string subStringFull(string, 0);

    CompareStr(subStdStringFull, subStringFull, "Hello World");

    std::string subStdStringWorld(stdString, 6);
    SketchStl::string subStringWorld(string, 6);

    CompareStr(subStdStringWorld, subStringWorld, "World");

    std::string subStdStringHello(stdString, 0, 5);
    SketchStl::string subStringHello(string, 0, 5);

    CompareStr(subStdStringHello, subStringHello, "Hello");

    std::string subStdString(stdString, 3, 6);
    SketchStl::string subString(string, 3, 6);

    CompareStr(subStdString, subString, "lo Wor");
}

BOOST_AUTO_TEST_CASE(string_buffer_constructor)
{
    std::string stdStringEmpty("Hello World", std::string::size_type(0));
    SketchStl::string stringEmpty("Hello World", 0);

    CompareStr(stdStringEmpty, stringEmpty, "");

    std::string stdStringFull("Hello World", 11);
    SketchStl::string stringFull("Hello World", 11);

    CompareStr(stdStringFull, stringFull, "Hello World");

    std::string stdStringHello("Hello World", 5);
    SketchStl::string stringHello("Hello World", 5);

    CompareStr(stdStringHello, stringHello, "Hello");
}

BOOST_AUTO_TEST_CASE(string_fill_constructor)
{
    std::string stdStringEmpty(0, 'a');
    SketchStl::string stringEmpty(0, 'a');

    CompareStr(stdStringEmpty, stringEmpty, "");

    std::string stdString(5, 'a');
    SketchStl::string string(5, 'a');

    CompareStr(stdString, string, "aaaaa");
}

BOOST_AUTO_TEST_CASE(string_assignment_string)
{
    std::string stdString("Hello World");
    SketchStl::string string("Hello World");

    std::string stdStringAssign;
    SketchStl::string stringAssign;

    stdStringAssign = stdString;
    stringAssign = string;

    CompareStr(stdStringAssign, stringAssign, "Hello World");

    std::string stdStringEmpty;
    SketchStl::string stringEmpty;

    stdStringAssign = stdStringEmpty;
    stringAssign = stringEmpty;

    CompareStr(stdStringAssign, stringAssign, "");
}

BOOST_AUTO_TEST_CASE(string_assignment_c_string)
{
    std::string stdString;
    SketchStl::string string;

    stdString = "Hello World";
    string = "Hello World";

    CompareStr(stdString, string, "Hello World");

    stdString = "";
    string = "";

    CompareStr(stdString, string, "");
}

BOOST_AUTO_TEST_CASE(string_assignement_char)
{
    std::string stdString;
    SketchStl::string string;

    stdString = 'a';
    string = 'a';

    CompareStr(stdString, string, "a");
}

BOOST_AUTO_TEST_CASE(string_size_and_length)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    BOOST_REQUIRE(stdString.size() == stdString.length());
    BOOST_REQUIRE(string.size() == string.length());

    BOOST_REQUIRE(stdString.size() == string.size());
}

BOOST_AUTO_TEST_CASE(string_resize)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.resize(stdString.size());
    string.resize(string.size());

    CompareStr(stdString, string, "Hello World");

    stdString.resize(15);
    string.resize(15);

    BOOST_REQUIRE(stdString.size() == 15 && string.size() == 15);
    BOOST_REQUIRE(strcmp(stdString.c_str(), string.c_str()) == 0);

    stdString.resize(5);
    string.resize(5);

    CompareStr(stdString, string, "Hello");
}

BOOST_AUTO_TEST_CASE(string_resize_fill)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.resize(stdString.size(), 'a');
    string.resize(string.size(), 'a');

    CompareStr(stdString, string, "Hello World");

    stdString.resize(15, 'a');
    string.resize(15, 'a');

    CompareStr(stdString, string, "Hello Worldaaaa");

    stdString.resize(5, 'a');
    string.resize(5, 'a');

    CompareStr(stdString, string, "Hello");
}

BOOST_AUTO_TEST_CASE(string_clear)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.clear();
    string.clear();

    CompareStr(stdString, string, "");
}

BOOST_AUTO_TEST_CASE(string_empty)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    BOOST_REQUIRE(!stdString.empty());
    BOOST_REQUIRE(!string.empty());

    stdString = "";
    string = "";

    BOOST_REQUIRE(stdString.empty());
    BOOST_REQUIRE(string.empty());
}

BOOST_AUTO_TEST_CASE(string_bracket_operators)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    BOOST_REQUIRE(stdString[4] == 'o');
    BOOST_REQUIRE(string[4] == 'o');

    stdString[4] = 'a';
    string[4] = 'a';

    CompareStr(stdString, string, "Hella World");
}

BOOST_AUTO_TEST_CASE(string_at)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    BOOST_REQUIRE(stdString.at(4) == 'o');
    BOOST_REQUIRE(string.at(4) == 'o');

    stdString.at(4) = 'a';
    string.at(4) = 'a';

    CompareStr(stdString, string, "Hella World");
}

BOOST_AUTO_TEST_CASE(string_operator_append_string)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString += stdStringEmpty;
    string += stringEmpty;

    CompareStr(stdString, string, "Hello ");

    std::string stdStringWorld = "World";
    SketchStl::string stringWorld = "World";

    stdString += stdStringWorld;
    string += stringWorld;

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_operator_append_c_string)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    stdString += "";
    string += "";

    CompareStr(stdString, string, "Hello ");

    stdString += "World";
    string += "World";

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_operator_append_char)
{
    std::string stdString = "Hello Worl";
    SketchStl::string string = "Hello Worl";

    stdString += 'd';
    string += 'd';

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_append_string)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString.append(stdStringEmpty);
    string.append(stringEmpty);

    CompareStr(stdString, string, "Hello ");

    std::string stdStringWorld = "World";
    SketchStl::string stringWorld = "World";

    stdString.append(stdStringWorld);
    string.append(stringWorld);

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_append_substring)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    std::string stdStringWorldToAll = "World to all";
    SketchStl::string stringWorldToAll = "World to all";

    stdString.append(stdStringWorldToAll, 0, 0);
    string.append(stringWorldToAll, 0, 0);

    CompareStr(stdString, string, "Hello ");

    stdString.append(stdStringWorldToAll, 0, 5);
    string.append(stringWorldToAll, 0, 5);

    CompareStr(stdString, string, "Hello World");

    stdString.append(stdStringWorldToAll, 5, 3);
    string.append(stringWorldToAll, 5, 3);

    CompareStr(stdString, string, "Hello World to");

    stdString.append(stdStringWorldToAll, 8, 10);
    string.append(stringWorldToAll, 8, 10);

    CompareStr(stdString, string, "Hello World to all");
}

BOOST_AUTO_TEST_CASE(string_append_c_string)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    stdString.append("");
    string.append("");

    CompareStr(stdString, string, "Hello ");

    stdString.append("World");
    string.append("World");

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_append_buffer)
{
    std::string stdString = "Hello ";
    SketchStl::string string = "Hello ";

    stdString.append("World to all", 5);
    string.append("World to all", 5);

    CompareStr(stdString, string, "Hello World");

    stdString.append(" to all", 7);
    string.append(" to all", 7);

    CompareStr(stdString, string, "Hello World to all");
}

BOOST_AUTO_TEST_CASE(string_append_fill)
{
    std::string stdString = "Hello";
    SketchStl::string string = "Hello";

    stdString.append(4, 'o');
    string.append(4, 'o');

    CompareStr(stdString, string, "Hellooooo");
}

BOOST_AUTO_TEST_CASE(string_push_back)
{
    std::string stdString = "Hello Worl";
    SketchStl::string string = "Hello Worl";

    stdString.push_back('d');
    string.push_back('d');

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_assign_string)
{
    std::string stdString = "Hi";
    SketchStl::string string = "Hi";

    std::string stdStringEmpty;
    SketchStl::string stringEmpty;

    stdString.assign(stdStringEmpty);
    string.assign(stringEmpty);

    CompareStr(stdString, string, "");

    std::string stdStringHelloWorld = "Hello World";
    SketchStl::string stringHelloWorld = "Hello World";

    stdString.assign(stdStringHelloWorld);
    string.assign(stringHelloWorld);

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_assign_substring)
{
    std::string stdString = "Hello";
    SketchStl::string string = "Hello";

    std::string stdStringHelloWorld = "Hello World";
    SketchStl::string stringHelloWorld = "Hello World";

    stdString.assign(stdStringHelloWorld, 0, 0);
    string.assign(stringHelloWorld, 0, 0);

    CompareStr(stdString, string, "");

    stdString.assign(stdStringHelloWorld, 3, 6);
    string.assign(stringHelloWorld, 3, 6);

    CompareStr(stdString, string, "lo Wor");

    stdString.assign(stdStringHelloWorld, 0, 11);
    string.assign(stringHelloWorld, 0, 11);

    CompareStr(stdString, string, "Hello World");

    stdString.assign(stdStringHelloWorld, 0, 20);
    string.assign(stringHelloWorld, 0, 20);

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_assign_c_string)
{
    std::string stdString("Hello");
    SketchStl::string string("Hello");

    stdString.assign("");
    string.assign("");

    CompareStr(stdString, string, "");

    stdString.assign("Hello World");
    string.assign("Hello World");

    CompareStr(stdString, string, "Hello World");
}

BOOST_AUTO_TEST_CASE(string_assign_buffer)
{
    std::string stdString("Hello");
    SketchStl::string string("Hello");

    stdString.assign("Hello World", 5);
    string.assign("Hello World", 5);

    CompareStr(stdString, string, "Hello");
}

BOOST_AUTO_TEST_CASE(string_assign_fill)
{
    std::string stdString("Hi");
    SketchStl::string string("Hi");

    stdString.assign(0, 'a');
    string.assign(0, 'a');

    CompareStr(stdString, string, "");

    stdString.assign(5, 'a');
    string.assign(5, 'a');

    CompareStr(stdString, string, "aaaaa");
}

BOOST_AUTO_TEST_CASE(string_insert_string)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString.insert(5, stdStringEmpty);
    string.insert(5, stringEmpty);

    CompareStr(stdString, string, "Hello World");

    std::string stdStringToYou = " to you";
    SketchStl::string stringToYou = " to you";

    stdString.insert(5, stdStringToYou);
    string.insert(5, stringToYou);

    CompareStr(stdString, string, "Hello to you World");
}

BOOST_AUTO_TEST_CASE(string_insert_substring)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString.insert(5, stdStringEmpty, 0, 0);
    string.insert(5, stringEmpty, 0, 0);

    CompareStr(stdString, string, "Hello World");

    std::string stdStringToYou = "Hello to you World";
    SketchStl::string stringToYou = "Hello to you World";

    stdString.insert(5, stdStringToYou, 5, 7);
    string.insert(5, stringToYou, 5, 7);

    CompareStr(stdString, string, "Hello to you World");
}

BOOST_AUTO_TEST_CASE(string_insert_c_string)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.insert(5, "");
    string.insert(5, "");

    CompareStr(stdString, string, "Hello World");

    stdString.insert(5, " to you");
    string.insert(5, " to you");

    CompareStr(stdString, string, "Hello to you World");
}

BOOST_AUTO_TEST_CASE(string_insert_c_buffer)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.insert(5, " to you World", 7);
    string.insert(5, " to you World", 7);

    CompareStr(stdString, string, "Hello to you World");
}

BOOST_AUTO_TEST_CASE(string_insert_fill)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    stdString.insert(5, 4, 'o');
    string.insert(5, 4, 'o');

    CompareStr(stdString, string, "Hellooooo World");
}

BOOST_AUTO_TEST_CASE(string_erase)
{
    std::string stdString = "Helloo to you World";
    SketchStl::string string = "Helloo to you World";

    stdString.erase(5, 1);
    string.erase(5, 1);

    CompareStr(stdString, string, "Hello to you World");

    stdString.erase(5, 7);
    string.erase(5, 7);

    CompareStr(stdString, string, "Hello World");

    stdString.erase();
    string.erase();

    CompareStr(stdString, string, "");
}

BOOST_AUTO_TEST_CASE(string_replace_string)
{
    std::string stdString = "Helloo to you World";
    SketchStl::string string = "Helloo to you World";

    std::string stdStringA = "a";
    SketchStl::string stringA = "a";

    stdString.replace(5, 1, stdStringA);
    string.replace(5, 1, stringA);

    CompareStr(stdString, string, "Helloa to you World");

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString.replace(5, 1, stdStringEmpty);
    string.replace(5, 1, stringEmpty);

    CompareStr(stdString, string, "Hello to you World");

    std::string stdStringLong = "everyone, have a nice day";
    SketchStl::string stringLong = "everyone, have a nice day";

    stdString.replace(6, 15, stdStringLong);
    string.replace(6, 15, stringLong);

    CompareStr(stdString, string, "Hello everyone, have a nice day");
}