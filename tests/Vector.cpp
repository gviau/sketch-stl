#include <boost/test/unit_test.hpp>

#include "sketch_vector.h"
#include <vector>

struct ConstructorComparison {
    ConstructorComparison() {
    }

    void setup() {
        stdNumConstructorCalls = stdNumDestructorCalls = numConstructorCalls = numDestructorCalls = 0;
    }

    bool EqualNumCalls() {
        return stdNumConstructorCalls == numConstructorCalls &&
               stdNumDestructorCalls == numDestructorCalls;
    }

    int stdNumConstructorCalls, stdNumDestructorCalls;
    int numConstructorCalls, numDestructorCalls;
};
ConstructorComparison fixture;

struct VectorFixture {
    VectorFixture() {
        fixture.setup();
    }
};

struct StdFoo {
    StdFoo(int val=0) : val_(val) {
        fixture.stdNumConstructorCalls += 1;
    }

    ~StdFoo() {
        fixture.stdNumDestructorCalls += 1;
    }

    int val_;
};

struct Foo {
    Foo(int val=0) : val_(val) {
        fixture.numConstructorCalls += 1;
    }

    ~Foo() {
        fixture.numDestructorCalls += 1;
    }

    int val_;
};

bool CompareVectorsValueType(const std::vector<int>& stdVec, const SketchStl::vector<int>& vec) {
    if (stdVec.size() != vec.size()) {
        return false;
    }

    for (size_t i = 0; i < stdVec.size(); i++) {
        if (stdVec[i] != vec[i]) {
            return false;
        }
    }

    return true;
}

bool CompareVectorsClassType(const std::vector<StdFoo>& stdVec, const SketchStl::vector<Foo>& vec) {
    if (stdVec.size() != vec.size()) {
        return false;
    }

    for (size_t i = 0; i < stdVec.size(); i++) {
        if (stdVec[i].val_ != vec[i].val_) {
            return false;
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////
// TESTS WITH VALUE TYPES
BOOST_AUTO_TEST_CASE(vector_value_type_constructor)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_fill_constructor)
{
    std::vector<int> stdVec(5);
    SketchStl::vector<int> vec(5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_copy_constructor)
{
    std::vector<int> stdVec(5);
    SketchStl::vector<int> vec(5);

    std::vector<int> stdCopyVec(stdVec);
    SketchStl::vector<int> copyVec(vec);

    BOOST_REQUIRE(CompareVectorsValueType(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_assignment_operator)
{
    std::vector<int> stdVec(5);
    SketchStl::vector<int> vec(5);

    std::vector<int> stdCopyVec;
    SketchStl::vector<int> copyVec;

    stdCopyVec = stdVec;
    copyVec = vec;

    BOOST_REQUIRE(CompareVectorsValueType(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_resize)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    stdVec.resize(5);
    vec.resize(5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.resize(8, 100);
    vec.resize(8, 100);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.resize(12);
    vec.resize(12);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_reserve)
{
    std::vector<int> stdVec(5, 5);;
    SketchStl::vector<int> vec(5, 5);

    stdVec.reserve(25);
    vec.reserve(25);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.reserve(5);
    vec.reserve(5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_assign_fill)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    stdVec.assign(5, 5);
    vec.assign(5, 5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.assign(3, 3);
    vec.assign(3, 3);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.assign(10, 5);
    vec.assign(10, 5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_push_back)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_pop_back)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.pop_back();
    vec.pop_back();

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_clear)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.clear();
    vec.clear();

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

/////////////////////////////////////////////////////////////////////////
// TESTS WITH VALUE CLASSES
BOOST_AUTO_TEST_CASE(vector_value_class_constructor)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_fill_constructor)
{
    std::vector<StdFoo> stdVec(5);
    SketchStl::vector<Foo> vec(5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_copy_constructor)
{
    std::vector<StdFoo> stdVec(5);
    SketchStl::vector<Foo> vec(5);

    std::vector<StdFoo> stdCopyVec(stdVec);
    SketchStl::vector<Foo> copyVec(vec);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_assignment_operator)
{
    std::vector<StdFoo> stdVec(5);
    SketchStl::vector<Foo> vec(5);

    std::vector<StdFoo> stdCopyVec;
    SketchStl::vector<Foo> copyVec;

    stdCopyVec = stdVec;
    copyVec = vec;

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_resize)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    stdVec.resize(5);
    vec.resize(5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.resize(8, StdFoo(100));
    vec.resize(8, Foo(100));

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.resize(12);
    vec.resize(12);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_reserve)
{
    std::vector<StdFoo> stdVec(5, 5);
    SketchStl::vector<Foo> vec(5, 5);

    stdVec.reserve(25);
    vec.reserve(25);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.reserve(5);
    vec.reserve(5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_assign_fill)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    stdVec.assign(5, StdFoo(5));
    vec.assign(5, Foo(5));

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.assign(3, StdFoo(3));
    vec.assign(3, Foo(3));

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
    
    stdVec.assign(10, StdFoo(5));
    vec.assign(10, Foo(5));

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_push_back)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(StdFoo(i));
        vec.push_back(Foo(i));
    }

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_pop_back)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(StdFoo(i));
        vec.push_back(Foo(i));
    }

    stdVec.pop_back();
    vec.pop_back();

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_clear)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(StdFoo(i));
        vec.push_back(Foo(i));
    }

    stdVec.clear();
    vec.clear();

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

/////////////////////////////////////////////////////////////////////////
// TESTS WITH POINTER TYPES

/////////////////////////////////////////////////////////////////////////
// TESTS WITH POINTER CLASSES