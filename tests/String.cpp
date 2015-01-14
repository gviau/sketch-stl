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

BOOST_AUTO_TEST_CASE(string_replace_substring)
{
    std::string stdString = "Helloo to you World";
    SketchStl::string string = "Helloo to you World";

    std::string stdStringBac = "bac";
    SketchStl::string stringBac = "bac";

    stdString.replace(5, 1, stdStringBac, 1, 0);
    string.replace(5, 1, stringBac, 1, 0);

    CompareStr(stdString, string, "Hello to you World");

    stdString.replace(5, 0, stdStringBac, 1, 1);
    string.replace(5, 0, stringBac, 1, 1);

    CompareStr(stdString, string, "Helloa to you World");

    std::string stdStringEmpty = "";
    SketchStl::string stringEmpty = "";

    stdString.replace(5, 1, stdStringEmpty, 0, 1);
    string.replace(5, 1, stringEmpty, 0, 1);

    CompareStr(stdString, string, "Hello to you World");

    std::string stdStringLong = "everyone, have a nice day";
    SketchStl::string stringLong = "everyone, have a nice day";

    stdString.replace(6, 15, stdStringLong, 10, 15);
    string.replace(6, 15, stringLong, 10, 15);

    CompareStr(stdString, string, "Hello have a nice day");
}

BOOST_AUTO_TEST_CASE(string_replace_c_string)
{
    std::string stdString = "Helloo to you World";
    SketchStl::string string = "Helloo to you World";

    stdString.replace(5, 1, "a");
    string.replace(5, 1, "a");

    CompareStr(stdString, string, "Helloa to you World");

    stdString.replace(5, 1, "");
    string.replace(5, 1, "");

    CompareStr(stdString, string, "Hello to you World");

    stdString.replace(6, 15, "everyone, have a nice day");
    string.replace(6, 15, "everyone, have a nice day");

    CompareStr(stdString, string, "Hello everyone, have a nice day");
}

BOOST_AUTO_TEST_CASE(string_replace_buffer)
{
    std::string stdString = "Helloo to you World";
    SketchStl::string string = "Helloo to you World";

    stdString.replace(5, 1, "asdja", 1);
    string.replace(5, 1, "asdja", 1);

    CompareStr(stdString, string, "Helloa to you World");

    stdString.replace(5, 1, "", 0);
    string.replace(5, 1, "", 0);

    CompareStr(stdString, string, "Hello to you World");

    stdString.replace(6, 15, "everyone, have a nice day and good day to all", 25);
    string.replace(6, 15, "everyone, have a nice day and good day to all", 25);

    CompareStr(stdString, string, "Hello everyone, have a nice day");
}

BOOST_AUTO_TEST_CASE(string_replace_fill)
{
    std::string stdString = "Hello";
    SketchStl::string string = "Hello";

    stdString.replace(4, 1, 5, 'o');
    string.replace(4, 1, 5, 'o');

    CompareStr(stdString, string, "Hellooooo");
}

BOOST_AUTO_TEST_CASE(string_swap)
{
    std::string stdStringHello = "Hello";
    SketchStl::string stringHello = "Hello";
    std::string stdStringWorld = "World";
    SketchStl::string stringWorld = "World";

    stdStringHello.swap(stdStringWorld);
    stringHello.swap(stringWorld);

    CompareStr(stdStringHello, stringHello, "World");
    CompareStr(stdStringWorld, stringWorld, "Hello");
}

BOOST_AUTO_TEST_CASE(string_copy)
{
    std::string stdString = "Hello world to all";
    SketchStl::string string = "Hello world to all";

    char stdBuffer[11];
    char buffer[11];

    stdString.copy(stdBuffer, 11);
    string.copy(buffer, 11);

    for (size_t i = 0; i < 11; i++) {
        BOOST_REQUIRE(stdBuffer[i] == buffer[i]);
    }

    stdString.copy(stdBuffer, 11, 6);
    string.copy(buffer, 11, 6);

    for (size_t i = 0; i < 11; i++) {
        BOOST_REQUIRE(stdBuffer[i] == buffer[i]);
    }

    stdString.copy(stdBuffer, 25, 7);
    string.copy(buffer, 25, 7);

    for (size_t i = 0; i < 11; i++) {
        BOOST_REQUIRE(stdBuffer[i] == buffer[i]);
    }
}

BOOST_AUTO_TEST_CASE(string_substr)
{
    std::string stdString = "Hello World to everyone";
    SketchStl::string string = "Hello World to everyone";

    CompareStr(stdString.substr(), string.substr(), "Hello World to everyone");
    CompareStr(stdString.substr(6), string.substr(6), "World to everyone");
    CompareStr(stdString.substr(0, 11), string.substr(0, 11), "Hello World");
    CompareStr(stdString.substr(6, 5), string.substr(6, 5), "World");
}

BOOST_AUTO_TEST_CASE(string_find_string)
{
    std::string stdString = "Hello World to everyone and all";
    SketchStl::string string = "Hello World to everyone and all";

    std::string stdSearchString = "Hello World";
    SketchStl::string searchString = "Hello World";

    size_t stdIdx = stdString.find(stdSearchString);
    size_t idx = string.find(searchString);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find(stdSearchString, 1);
    idx = string.find(searchString, 1);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find(stdSearchString, 25);
    idx = string.find(searchString, 25);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdSearchString = "to everyone an";
    searchString = "to everyone an";

    stdIdx = stdString.find(stdSearchString);
    idx = string.find(searchString);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find(stdSearchString, 12);
    idx = string.find(searchString, 12);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdSearchString = "";
    searchString = "";

    stdIdx = stdString.find(stdSearchString);
    idx = string.find(searchString);

    BOOST_REQUIRE(stdIdx == 0 && idx == 0);

    stdIdx = stdString.find(stdSearchString, 5);
    idx = string.find(searchString, 5);

    BOOST_REQUIRE(stdIdx == 5 && idx == 5);
}

BOOST_AUTO_TEST_CASE(string_find_cstring)
{
    std::string stdString = "Hello World to everyone and all";
    SketchStl::string string = "Hello World to everyone and all";

    size_t stdIdx = stdString.find("Hello World");
    size_t idx = string.find("Hello World");

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("Hello World", 1);
    idx = string.find("Hello World", 1);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find("Hello World", 25);
    idx = string.find("Hello World", 25);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find("to everyone an");
    idx = string.find("to everyone an");

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("to everyone an", 12);
    idx = string.find("to everyone an", 12);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("");
    idx = string.find("");

    BOOST_REQUIRE(stdIdx == 0 && idx == 0);

    stdIdx = stdString.find("", 5);
    idx = string.find("", 5);

    BOOST_REQUIRE(stdIdx == 5 && idx == 5);
}

BOOST_AUTO_TEST_CASE(string_find_buffer)
{
    std::string stdString = "Hello World to everyone and all";
    SketchStl::string string = "Hello World to everyone and all";

    size_t stdIdx = stdString.find("Hello World to everyone", 0, 11);
    size_t idx = string.find("Hello World to everyone", 0, 11);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("Hello World to everyone", 1, 11);
    idx = string.find("Hello World to everyone", 1, 11);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find("Hello World to everyone", 25, 11);
    idx = string.find("Hello World to everyone", 25, 11);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find("to everyone and all", 0, 14);
    idx = string.find("to everyone and all", 0, 14);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("to everyone and all", 12, 14);
    idx = string.find("to everyone and all", 12, 14);

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find("", 0, 0);
    idx = string.find("", 0, 0);

    BOOST_REQUIRE(stdIdx == 0 && idx == 0);

    stdIdx = stdString.find("", 5, 0);
    idx = string.find("", 5, 0);

    BOOST_REQUIRE(stdIdx == 5 && idx == 5);
}

BOOST_AUTO_TEST_CASE(string_find_char)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    size_t stdIdx = stdString.find('H');
    size_t idx = string.find('H');

    BOOST_REQUIRE(stdIdx != std::string::npos && idx != SketchStl::string::npos && stdIdx == idx);

    stdIdx = stdString.find('h');
    idx = string.find('h');

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find('l');
    idx = string.find('l');

    BOOST_REQUIRE(stdIdx == 2 && idx == 2);

    stdIdx = stdString.find('l', 2);
    idx = stdString.find('l', 2);

    BOOST_REQUIRE(stdIdx == 2 && idx == 2);

    stdIdx = stdString.find('l', 3);
    idx = stdString.find('l', 3);

    BOOST_REQUIRE(stdIdx == 3 && idx == 3);

    stdIdx = stdString.find('e', 2);
    idx = string.find('e', 2);

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);

    stdIdx = stdString.find('z');
    idx = string.find('z');

    BOOST_REQUIRE(stdIdx == std::string::npos && idx == SketchStl::string::npos);
}

BOOST_AUTO_TEST_CASE(string_string_compare_string)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    std::string stdStringComp = stdString;
    SketchStl::string stringComp = string;

    BOOST_REQUIRE(stdString.compare(stdStringComp) == 0 && string.compare(stringComp) == 0);

    stdStringComp = "Hello Worlc";
    stringComp = "Hello Worlc";

    BOOST_REQUIRE(stdString.compare(stdStringComp) > 0 && string.compare(stringComp) > 0);

    stdStringComp = "Hello Worle";
    stringComp = "Hello Worle";

    BOOST_REQUIRE(stdString.compare(stdStringComp) < 0 && string.compare(stringComp) < 0);

    stdStringComp = "Hello Worl";
    stringComp = "Hello Worl";

    BOOST_REQUIRE(stdString.compare(stdStringComp) > 0 && string.compare(stringComp) > 0);

    stdStringComp = "Hello Worlde";
    stringComp = "Hello Worlde";

    BOOST_REQUIRE(stdString.compare(stdStringComp) < 0 && string.compare(stringComp) < 0);
}

BOOST_AUTO_TEST_CASE(string_substring_compare_string)
{
    std::string stdString = "Hello World to everyone";
    SketchStl::string string = "Hello World to everyone";

    std::string stdStringComp = stdString;
    SketchStl::string stringComp = string;

    BOOST_REQUIRE(stdString.compare(0, std::string::npos, stdStringComp) == 0 && string.compare(0, SketchStl::string::npos, stringComp) == 0);

    stdStringComp = "Hello World";
    stringComp = "Hello World";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp) == 0 && string.compare(0, 11, stringComp) == 0);

    stdStringComp = "Hello Worlc";
    stringComp = "Hello Worlc";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp) > 0 && string.compare(0, 11, stringComp) > 0);

    stdStringComp = "Hello Worle";
    stringComp = "Hello Worle";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp) < 0 && string.compare(0, 11, stringComp) < 0);

    stdStringComp = "Hello Worl";
    stringComp = "Hello Worl";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp) > 0 && string.compare(0, 11, stringComp) > 0);

    stdStringComp = "Hello Worlde";
    stringComp = "Hello Worlde";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp) < 0 && string.compare(0, 11, stringComp) < 0);
}

BOOST_AUTO_TEST_CASE(string_substring_compare_substring)
{
    std::string stdString = "Hello World to everyone";
    SketchStl::string string = "Hello World to everyone";

    std::string stdStringComp = stdString;
    SketchStl::string stringComp = string;

    BOOST_REQUIRE(stdString.compare(0, std::string::npos, stdStringComp, 0, std::string::npos) == 0 &&
                  string.compare(0, SketchStl::string::npos, stringComp, 0, SketchStl::string::npos) == 0);

    stdStringComp = "Hello World to everyone";
    stringComp = "Hello World to everyone";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp, 0, 11) == 0 &&
                  string.compare(0, 11, stringComp, 0, 11) == 0);

    stdStringComp = "Hello Worlc to everyone";
    stringComp = "Hello Worlc to everyone";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp, 0, 11) > 0 &&
                  string.compare(0, 11, stringComp, 0, 11) > 0);

    stdStringComp = "Hello Worle to everyone";
    stringComp = "Hello Worle to everyone";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp, 0, 11) < 0 &&
                  string.compare(0, 11, stringComp, 0, 11) < 0);

    stdStringComp = "Hello Worl to everyone";
    stringComp = "Hello Worl to everyone";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp, 0, 11) > 0 &&
                  string.compare(0, 11, stringComp, 0, 11) > 0);

    stdStringComp = "Hello Worlde to everyone";
    stringComp = "Hello Worlde to everyone";

    BOOST_REQUIRE(stdString.compare(0, 11, stdStringComp, 0, 12) < 0 &&
                  string.compare(0, 11, stringComp, 0, 12) < 0);
}

BOOST_AUTO_TEST_CASE(string_string_compare_c_string)
{
    std::string stdString = "Hello World";
    SketchStl::string string = "Hello World";

    BOOST_REQUIRE(stdString.compare("Hello World") == 0 && string.compare("Hello World") == 0);
    BOOST_REQUIRE(stdString.compare("Hello Worlc") > 0 && string.compare("Hello Worlc") > 0);
    BOOST_REQUIRE(stdString.compare("Hello Worle") < 0 && string.compare("Hello Worle") < 0);
    BOOST_REQUIRE(stdString.compare("Hello Worl") > 0 && string.compare("Hello Worl") > 0);
    BOOST_REQUIRE(stdString.compare("Hello Worlde") < 0 && string.compare("Hello Worlde") < 0);
}

BOOST_AUTO_TEST_CASE(string_substring_compare_c_string)
{
    std::string stdString = "Hello World to everyone";
    SketchStl::string string = "Hello World to everyone";

    BOOST_REQUIRE(stdString.compare(0, std::string::npos, "Hello World to everyone") == 0 && string.compare(0, SketchStl::string::npos, "Hello World to everyone") == 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello World") == 0 && string.compare(0, 11, "Hello World") == 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worlc") > 0 && string.compare(0, 11, "Hello Worlc") > 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worle") < 0 && string.compare(0, 11, "Hello Worle") < 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worl") > 0 && string.compare(0, 11, "Hello Worl") > 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worlde") < 0 && string.compare(0, 11, "Hello Worlde") < 0);
}

BOOST_AUTO_TEST_CASE(string_substring_compare_buffer)
{
    std::string stdString = "Hello World to everyone";
    SketchStl::string string = "Hello World to everyone";

    BOOST_REQUIRE(stdString.compare(0, std::string::npos, "Hello World to everyone and all", 23) == 0 && string.compare(0, SketchStl::string::npos, "Hello World to everyone and all", 23) == 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello World to everyone", 11) == 0 && string.compare(0, 11, "Hello World to everyone", 11) == 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worlc to everyone", 11) > 0 && string.compare(0, 11, "Hello Worlc to everyone", 11) > 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worle to everyone", 11) < 0 && string.compare(0, 11, "Hello Worle to everyone", 11) < 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worl to everyone", 11) > 0 && string.compare(0, 11, "Hello Worl to everyone", 11) > 0);
    BOOST_REQUIRE(stdString.compare(0, 11, "Hello Worlde to everyone", 12) < 0 && string.compare(0, 11, "Hello Worlde to everyone", 12) < 0);
}

BOOST_AUTO_TEST_CASE(string_concatenation_operators)
{
    std::string stdLhs = "Hello ";
    std::string stdRhs = "World";
    SketchStl::string lhs = "Hello ";
    SketchStl::string rhs = "World";

    std::string stdResult = stdLhs + stdRhs;
    SketchStl::string result = lhs + rhs;

    CompareStr(stdResult, result, "Hello World");

    stdResult = stdLhs + "World";
    result = lhs + "World";

    CompareStr(stdResult, result, "Hello World");

    stdResult = "Hello " + stdRhs;
    result = "Hello " + rhs;

    CompareStr(stdResult, result, "Hello World");

    stdResult = stdLhs + 'W';
    result = lhs + 'W';

    CompareStr(stdResult, result, "Hello W");

    stdResult = '!' + stdRhs;
    result = '!' + rhs;

    CompareStr(stdResult, result, "!World");
}

BOOST_AUTO_TEST_CASE(string_relational_operators)
{
    std::string stdLhs = "Hello World";
    std::string stdRhs = "Hello World";
    SketchStl::string lhs = "Hello World";
    SketchStl::string rhs = "Hello World";

    BOOST_REQUIRE(stdLhs == stdRhs && lhs == rhs);
    BOOST_REQUIRE(stdLhs == "Hello World" && lhs == "Hello World");
    BOOST_REQUIRE("Hello World" == stdRhs && "Hello World" == lhs);

    stdRhs = "Greetings";
    rhs = "Greetings";

    BOOST_REQUIRE(stdLhs != stdRhs && lhs != rhs);
    BOOST_REQUIRE(stdLhs != "Greetings" && lhs != "Greetings");
    BOOST_REQUIRE("Hello World" != stdRhs && "Hello World" != rhs);

    stdRhs = "Hello Worlde";
    rhs = "Hello Worlde";

    BOOST_REQUIRE(stdLhs < stdRhs && lhs < rhs);
    BOOST_REQUIRE(stdLhs < "Hello Worlde" && lhs < "Hello Worlde");
    BOOST_REQUIRE("Hello World" < stdRhs && "Hello World" < rhs);

    stdRhs = "Hello Worl";
    rhs = "Hello Worl";

    BOOST_REQUIRE(stdLhs > stdRhs && lhs > rhs);
    BOOST_REQUIRE(stdLhs > "Hello Worl" && lhs > "Hello Worl");
    BOOST_REQUIRE("Hello World" > stdRhs && "Hello World" > rhs);
}