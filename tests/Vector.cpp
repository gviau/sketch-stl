#define _CRTDBG_MAP_ALLOC
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

bool CompareVectorsValuePointer(const std::vector<int*>& stdVec, const SketchStl::vector<int*>& vec) {
    if (stdVec.size() != vec.size()) {
        return false;
    }

    for (size_t i = 0; i < stdVec.size(); i++) {
        if (stdVec[i] != nullptr && vec[i] != nullptr) {
            if (*stdVec[i] != *vec[i]) {
                return false;
            }
        } else if ((stdVec[i] == nullptr && vec[i] != nullptr) || (stdVec[i] != nullptr && vec[i] == nullptr)) {
            return false;
        }
    }

    return true;
}

bool CompareVectorsClassPointer(const std::vector<StdFoo*>& stdVec, const SketchStl::vector<Foo*>& vec) {
    if (stdVec.size() != vec.size()) {
        return false;
    }

    for (size_t i = 0; i < stdVec.size(); i++) {
        if (stdVec[i] != nullptr && vec[i] != nullptr) {
            if (stdVec[i]->val_ != vec[i]->val_) {
                return false;
            }
        } else if ((stdVec[i] == nullptr && vec[i] != nullptr) || (stdVec[i] != nullptr && vec[i] == nullptr)) {
            return false;
        }
    }

    return true;
}

void FreeVectorsValue(const std::vector<int*>& stdVec, const SketchStl::vector<int*>& vec) {
    for (size_t i = 0; i < stdVec.size(); i++) {
        delete stdVec[i];
    }

    for (size_t i = 0; i < vec.size(); i++) {
        delete vec[i];
    }
}

void FreeVectorsClass(const std::vector<StdFoo*>& stdVec, const SketchStl::vector<Foo*>& vec) {
    for (size_t i = 0; i < stdVec.size(); i++) {
        delete stdVec[i];
    }

    for (size_t i = 0; i < vec.size(); i++) {
        delete vec[i];
    }
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

BOOST_AUTO_TEST_CASE(vector_value_type_range_constructor)
{
    std::vector<int> stdVec(5);
    SketchStl::vector<int> vec(5);

    std::vector<int> stdRangeVec(stdVec.begin(), stdVec.end());
    SketchStl::vector<int> rangeVec(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValueType(stdRangeVec, rangeVec));
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
    std::vector<int> stdVec(5, 5);
    SketchStl::vector<int> vec(5, 5);

    stdVec.reserve(25);
    vec.reserve(25);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.reserve(5);
    vec.reserve(5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_assign_range)
{
    std::vector<int> stdVec(5, 5);
    SketchStl::vector<int> vec(5, 5);

    std::vector<int> stdRangeVec;
    SketchStl::vector<int> rangeVec;

    stdRangeVec.assign(stdVec.begin(), stdVec.end());
    rangeVec.assign(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValueType(stdRangeVec, rangeVec));
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

BOOST_AUTO_TEST_CASE(vector_value_type_insert)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    stdVec.insert(stdVec.begin(), 0);
    vec.insert(vec.begin(), 0);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    for (size_t i = 1; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.insert(stdVec.end() - 1, 5);
    vec.insert(vec.end() - 1, 5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.insert(stdVec.begin() + 2, 10);
    vec.insert(vec.begin() + 2, 10);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_insert_fill)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    stdVec.insert(stdVec.begin(), 3, 0);
    vec.insert(vec.begin(), 3, 0);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    for (size_t i = 1; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.insert(stdVec.end() - 1, 2, 5);
    vec.insert(vec.end() - 1, 2, 5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.insert(stdVec.begin() + 2, 2, 10);
    vec.insert(vec.begin() + 2, 2, 10);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_insert_range)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    std::vector<int> stdInsertVec;
    SketchStl::vector<int> insertVec;

    stdInsertVec.insert(stdInsertVec.begin(), stdVec.begin(), stdVec.end());
    insertVec.insert(insertVec.begin(), vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValueType(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.end() - 1, stdVec.begin(), stdVec.end() - 2);
    insertVec.insert(insertVec.end() - 1, vec.begin(), vec.end() - 2);

    BOOST_REQUIRE(CompareVectorsValueType(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.begin() + 2, stdVec.begin() + 2, stdVec.end());
    insertVec.insert(insertVec.begin() + 2, vec.begin() + 2, vec.end());

    BOOST_REQUIRE(CompareVectorsValueType(stdInsertVec, insertVec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_erase)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.erase(stdVec.begin());
    vec.erase(vec.begin());

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.erase(stdVec.begin() + 2);
    vec.erase(vec.begin() + 2);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.erase(stdVec.end() - 1);
    vec.erase(vec.end() - 1);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_type_erase_range)
{
    std::vector<int> stdVec;
    SketchStl::vector<int> vec;

    for (size_t i = 0; i < 20; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.erase(stdVec.begin() + 3, stdVec.begin() + 5);
    vec.erase(vec.begin() + 3, vec.begin() + 5);

    BOOST_REQUIRE(CompareVectorsValueType(stdVec, vec));

    stdVec.erase(stdVec.begin(), stdVec.end());
    vec.erase(vec.begin(), vec.end());

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

BOOST_AUTO_TEST_CASE(vector_value_class_range_constructor)
{
    std::vector<StdFoo> stdVec(5);
    SketchStl::vector<Foo> vec(5);

    std::vector<StdFoo> stdRangeVec(stdVec.begin(), stdVec.end());
    SketchStl::vector<Foo> rangeVec(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassType(stdRangeVec, rangeVec));
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

BOOST_AUTO_TEST_CASE(vector_value_class_assign_range)
{
    std::vector<StdFoo> stdVec(5, 5);
    SketchStl::vector<Foo> vec(5, 5);

    std::vector<StdFoo> stdRangeVec;
    SketchStl::vector<Foo> rangeVec;

    stdRangeVec.assign(stdVec.begin(), stdVec.end());
    rangeVec.assign(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassType(stdRangeVec, rangeVec));
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

BOOST_AUTO_TEST_CASE(vector_value_class_insert)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    stdVec.insert(stdVec.begin(), 0);
    vec.insert(vec.begin(), 0);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    for (size_t i = 1; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.insert(stdVec.end() - 1, 5);
    vec.insert(vec.end() - 1, 5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.insert(stdVec.begin() + 2, 10);
    vec.insert(vec.begin() + 2, 10);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_insert_fill)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    stdVec.insert(stdVec.begin(), 3, 0);
    vec.insert(vec.begin(), 3, 0);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    for (size_t i = 1; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.insert(stdVec.end() - 1, 2, 5);
    vec.insert(vec.end() - 1, 2, 5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.insert(stdVec.begin() + 2, 2, 10);
    vec.insert(vec.begin() + 2, 2, 10);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_insert_range)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    std::vector<StdFoo> stdInsertVec;
    SketchStl::vector<Foo> insertVec;

    stdInsertVec.insert(stdInsertVec.begin(), stdVec.begin(), stdVec.end());
    insertVec.insert(insertVec.begin(), vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassType(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.end() - 1, stdVec.begin(), stdVec.end() - 2);
    insertVec.insert(insertVec.end() - 1, vec.begin(), vec.end() - 2);

    BOOST_REQUIRE(CompareVectorsClassType(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.begin() + 2, stdVec.begin() + 2, stdVec.end());
    insertVec.insert(insertVec.begin() + 2, vec.begin() + 2, vec.end());

    BOOST_REQUIRE(CompareVectorsClassType(stdInsertVec, insertVec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_erase)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.erase(stdVec.begin());
    vec.erase(vec.begin());

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.erase(stdVec.begin() + 2);
    vec.erase(vec.begin() + 2);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.erase(stdVec.end() - 1);
    vec.erase(vec.end() - 1);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_class_erase_range)
{
    std::vector<StdFoo> stdVec;
    SketchStl::vector<Foo> vec;

    for (size_t i = 0; i < 20; i++) {
        stdVec.push_back(i);
        vec.push_back(i);
    }

    stdVec.erase(stdVec.begin() + 3, stdVec.begin() + 5);
    vec.erase(vec.begin() + 3, vec.begin() + 5);

    BOOST_REQUIRE(CompareVectorsClassType(stdVec, vec));

    stdVec.erase(stdVec.begin(), stdVec.end());
    vec.erase(vec.begin(), vec.end());

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
BOOST_AUTO_TEST_CASE(vector_value_pointer_constructor)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_fill_constructor)
{
    std::vector<int*> stdVec(5);
    SketchStl::vector<int*> vec(5);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_range_constructor)
{
    std::vector<int*> stdVec(5);
    SketchStl::vector<int*> vec(5);

    std::vector<int*> stdRangeVec(stdVec.begin(), stdVec.end());
    SketchStl::vector<int*> rangeVec(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdRangeVec, rangeVec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_copy_constructor)
{
    std::vector<int*> stdVec(5);
    SketchStl::vector<int*> vec(5);

    std::vector<int*> stdCopyVec(stdVec);
    SketchStl::vector<int*> copyVec(vec);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_assignment_operator)
{
    std::vector<int*> stdVec(5);
    SketchStl::vector<int*> vec(5);

    std::vector<int*> stdCopyVec;
    SketchStl::vector<int*> copyVec;

    stdCopyVec = stdVec;
    copyVec = vec;

    BOOST_REQUIRE(CompareVectorsValuePointer(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_resize)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    stdVec.resize(5);
    vec.resize(5);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int val = 100;
    stdVec.resize(8, &val);
    vec.resize(8, &val);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    stdVec.resize(12);
    vec.resize(12);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_reserve)
{
    int val = 5;
    std::vector<int*> stdVec(5, &val);
    SketchStl::vector<int*> vec(5, &val);

    stdVec.reserve(25);
    vec.reserve(25);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    stdVec.reserve(5);
    vec.reserve(5);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_assign_range)
{
    int val = 5;
    std::vector<int*> stdVec(5, &val);
    SketchStl::vector<int*> vec(5, &val);

    std::vector<int*> stdRangeVec;
    SketchStl::vector<int*> rangeVec;

    stdRangeVec.assign(stdVec.begin(), stdVec.end());
    rangeVec.assign(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdRangeVec, rangeVec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_assign_fill)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    int val1 = 5;
    stdVec.assign(5, &val1);
    vec.assign(5, &val1);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int val2 = 3;
    stdVec.assign(3, &val2);
    vec.assign(3, &val2);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int val3 = 5;
    stdVec.assign(10, &val3);
    vec.assign(10, &val3);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_push_back)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new int(i));
        vec.push_back(new int(i));
    }

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
    FreeVectorsValue(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_pop_back)
{
    int values[] = { 0, 1, 2, 3, 4 };
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(&values[i]);
        vec.push_back(&values[i]);
    }

    stdVec.pop_back();
    vec.pop_back();

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_insert)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    int val1 = 0;
    stdVec.insert(stdVec.begin(), &val1);
    vec.insert(vec.begin(), &val1);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int values[] = { 1, 2, 3, 4 };
    for (size_t i = 0; i < 4; i++) {
        stdVec.push_back(&values[i]);
        vec.push_back(&values[i]);
    }

    int val2 = 5;
    stdVec.insert(stdVec.end() - 1, &val2);
    vec.insert(vec.end() - 1, &val2);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int val3 = 10;
    stdVec.insert(stdVec.begin() + 2, &val3);
    vec.insert(vec.begin() + 2, &val3);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_insert_fill)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    int val1 = 0;
    stdVec.insert(stdVec.begin(), 3, &val1);
    vec.insert(vec.begin(), 3, &val1);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int values[] = { 1, 2, 3, 4 };
    for (size_t i = 0; i < 4; i++) {
        stdVec.push_back(&values[i]);
        vec.push_back(&values[i]);
    }

    int val2 = 5;
    stdVec.insert(stdVec.end() - 1, 2, &val2);
    vec.insert(vec.end() - 1, 2, &val2);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    int val3 = 10;
    stdVec.insert(stdVec.begin() + 2, 2, &val3);
    vec.insert(vec.begin() + 2, 2, &val3);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_insert_range)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new int(i));
        vec.push_back(new int(i));
    }

    std::vector<int*> stdInsertVec;
    SketchStl::vector<int*> insertVec;

    stdInsertVec.insert(stdInsertVec.begin(), stdVec.begin(), stdVec.end());
    insertVec.insert(insertVec.begin(), vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.end() - 1, stdVec.begin(), stdVec.end() - 2);
    insertVec.insert(insertVec.end() - 1, vec.begin(), vec.end() - 2);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.begin() + 2, stdVec.begin() + 2, stdVec.end());
    insertVec.insert(insertVec.begin() + 2, vec.begin() + 2, vec.end());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdInsertVec, insertVec));

    FreeVectorsValue(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_erase)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new int(i));
        vec.push_back(new int(i));
    }

    delete *(stdVec.begin());
    stdVec.erase(stdVec.begin());

    delete *(vec.begin());
    vec.erase(vec.begin());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    delete *(stdVec.begin() + 2);
    stdVec.erase(stdVec.begin() + 2);

    delete *(vec.begin() + 2);
    vec.erase(vec.begin() + 2);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    delete *(stdVec.end() - 1);
    stdVec.erase(stdVec.end() - 1);

    delete *(vec.end() - 1);
    vec.erase(vec.end() - 1);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    FreeVectorsValue(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_erase_range)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    for (size_t i = 0; i < 20; i++) {
        stdVec.push_back(new int(i));
        vec.push_back(new int(i));
    }

    std::vector<int*>::iterator stdIt = stdVec.begin() + 3;
    for (; stdIt != (stdVec.begin() + 5); ++stdIt) {
        delete *stdIt;
    }
    stdVec.erase(stdVec.begin() + 3, stdVec.begin() + 5);

    SketchStl::vector<int*>::iterator it = vec.begin() + 3;
    for (; it != (vec.begin() + 5); ++it) {
        delete *it;
    }
    vec.erase(vec.begin() + 3, vec.begin() + 5);

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    for (stdIt = stdVec.begin(); stdIt != stdVec.end(); ++stdIt) {
        delete *stdIt;
    }
    stdVec.erase(stdVec.begin(), stdVec.end());

    for (it = vec.begin(); it != vec.end(); ++it) {
        delete *it;
    }
    vec.erase(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));

    FreeVectorsValue(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_value_pointer_clear)
{
    std::vector<int*> stdVec;
    SketchStl::vector<int*> vec;

    int values[] = { 0, 1, 2, 3, 4 };
    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(&values[i]);
        vec.push_back(&values[i]);
    }

    stdVec.clear();
    vec.clear();

    BOOST_REQUIRE(CompareVectorsValuePointer(stdVec, vec));
}

/////////////////////////////////////////////////////////////////////////
// TESTS WITH POINTER CLASSES
BOOST_AUTO_TEST_CASE(vector_class_pointer_constructor)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_fill_constructor)
{
    std::vector<StdFoo*> stdVec(5);
    SketchStl::vector<Foo*> vec(5);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_range_constructor)
{
    std::vector<StdFoo*> stdVec(5);
    SketchStl::vector<Foo*> vec(5);

    std::vector<StdFoo*> stdRangeVec(stdVec.begin(), stdVec.end());
    SketchStl::vector<Foo*> rangeVec(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdRangeVec, rangeVec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_copy_constructor)
{
    std::vector<StdFoo*> stdVec(5);
    SketchStl::vector<Foo*> vec(5);

    std::vector<StdFoo*> stdCopyVec(stdVec);
    SketchStl::vector<Foo*> copyVec(vec);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_assignment_operator)
{
    std::vector<StdFoo*> stdVec(5);
    SketchStl::vector<Foo*> vec(5);

    std::vector<StdFoo*> stdCopyVec;
    SketchStl::vector<Foo*> copyVec;

    stdCopyVec = stdVec;
    copyVec = vec;

    BOOST_REQUIRE(CompareVectorsClassPointer(stdCopyVec, copyVec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_resize)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    stdVec.resize(5);
    vec.resize(5);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdVal(100);
    Foo val(100);
    stdVec.resize(8, &stdVal);
    vec.resize(8, &val);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    stdVec.resize(12);
    vec.resize(12);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_reserve)
{
    StdFoo stdVal(5);
    Foo val(5);
    std::vector<StdFoo*> stdVec(5, &stdVal);
    SketchStl::vector<Foo*> vec(5, &val);

    stdVec.reserve(25);
    vec.reserve(25);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    stdVec.reserve(5);
    vec.reserve(5);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_assign_range)
{
    StdFoo stdVal(5);
    Foo val(5);
    std::vector<StdFoo*> stdVec(5, &stdVal);
    SketchStl::vector<Foo*> vec(5, &val);

    std::vector<StdFoo*> stdRangeVec;
    SketchStl::vector<Foo*> rangeVec;

    stdRangeVec.assign(stdVec.begin(), stdVec.end());
    rangeVec.assign(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdRangeVec, rangeVec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_assign_fill)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    StdFoo stdVal1(5);
    Foo val1(5);
    stdVec.assign(5, &stdVal1);
    vec.assign(5, &val1);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdVal2(3);
    Foo val2(3);
    stdVec.assign(3, &stdVal2);
    vec.assign(3, &val2);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdVal3(5);
    Foo val3(5);
    stdVec.assign(10, &stdVal3);
    vec.assign(10, &val3);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_push_back)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new StdFoo(i));
        vec.push_back(new Foo(i));
    }

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
    FreeVectorsClass(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_pop_back)
{
    StdFoo stdValues[] = { StdFoo(0), StdFoo(1), StdFoo(2), StdFoo(3), StdFoo(4) };
    Foo values[] = { Foo(0), Foo(1), Foo(2), Foo(3), Foo(4) };
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(&stdValues[i]);
        vec.push_back(&values[i]);
    }

    stdVec.pop_back();
    vec.pop_back();

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_insert)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    StdFoo stdVal1(0);
    Foo val1(0);
    stdVec.insert(stdVec.begin(), &stdVal1);
    vec.insert(vec.begin(), &val1);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdValues[] = { StdFoo(1), StdFoo(2), StdFoo(3), StdFoo(4) };
    Foo values[] = { Foo(1), Foo(2), Foo(3), Foo(4) };
    for (size_t i = 0; i < 4; i++) {
        stdVec.push_back(&stdValues[i]);
        vec.push_back(&values[i]);
    }

    StdFoo stdVal2(5);
    Foo val2(5);
    stdVec.insert(stdVec.end() - 1, &stdVal2);
    vec.insert(vec.end() - 1, &val2);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdVal3(10);
    Foo val3(10);
    stdVec.insert(stdVec.begin() + 2, &stdVal3);
    vec.insert(vec.begin() + 2, &val3);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_insert_fill)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    StdFoo stdVal1(0);
    Foo val1(0);
    stdVec.insert(stdVec.begin(), 3, &stdVal1);
    vec.insert(vec.begin(), 3, &val1);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdValues[] = { StdFoo(1), StdFoo(2), StdFoo(3), StdFoo(4) };
    Foo values[] = { Foo(1), Foo(2), Foo(3), Foo(4) };
    for (size_t i = 0; i < 4; i++) {
        stdVec.push_back(&stdValues[i]);
        vec.push_back(&values[i]);
    }

    StdFoo stdVal2(5);
    Foo val2(5);
    stdVec.insert(stdVec.end() - 1, 2, &stdVal2);
    vec.insert(vec.end() - 1, 2, &val2);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    StdFoo stdVal3(10);
    Foo val3(10);
    stdVec.insert(stdVec.begin() + 2, 2, &stdVal3);
    vec.insert(vec.begin() + 2, 2, &val3);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_insert_range)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new StdFoo(i));
        vec.push_back(new Foo(i));
    }

    std::vector<StdFoo*> stdInsertVec;
    SketchStl::vector<Foo*> insertVec;

    stdInsertVec.insert(stdInsertVec.begin(), stdVec.begin(), stdVec.end());
    insertVec.insert(insertVec.begin(), vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.end() - 1, stdVec.begin(), stdVec.end() - 2);
    insertVec.insert(insertVec.end() - 1, vec.begin(), vec.end() - 2);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdInsertVec, insertVec));

    stdInsertVec.insert(stdInsertVec.begin() + 2, stdVec.begin() + 2, stdVec.end());
    insertVec.insert(insertVec.begin() + 2, vec.begin() + 2, vec.end());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdInsertVec, insertVec));

    FreeVectorsClass(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_erase)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(new StdFoo(i));
        vec.push_back(new Foo(i));
    }

    delete *(stdVec.begin());
    stdVec.erase(stdVec.begin());

    delete *(vec.begin());
    vec.erase(vec.begin());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    delete *(stdVec.begin() + 2);
    stdVec.erase(stdVec.begin() + 2);

    delete *(vec.begin() + 2);
    vec.erase(vec.begin() + 2);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    delete *(stdVec.end() - 1);
    stdVec.erase(stdVec.end() - 1);

    delete *(vec.end() - 1);
    vec.erase(vec.end() - 1);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    FreeVectorsClass(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_erase_range)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    for (size_t i = 0; i < 20; i++) {
        stdVec.push_back(new StdFoo(i));
        vec.push_back(new Foo(i));
    }

    std::vector<StdFoo*>::iterator stdIt = stdVec.begin() + 3;
    for (; stdIt != (stdVec.begin() + 5); ++stdIt) {
        delete *stdIt;
    }
    stdVec.erase(stdVec.begin() + 3, stdVec.begin() + 5);

    SketchStl::vector<Foo*>::iterator it = vec.begin() + 3;
    for (; it != (vec.begin() + 5); ++it) {
        delete *it;
    }
    vec.erase(vec.begin() + 3, vec.begin() + 5);

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    for (stdIt = stdVec.begin(); stdIt != stdVec.end(); ++stdIt) {
        delete *stdIt;
    }
    stdVec.erase(stdVec.begin(), stdVec.end());

    for (it = vec.begin(); it != vec.end(); ++it) {
        delete *it;
    }
    vec.erase(vec.begin(), vec.end());

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));

    FreeVectorsClass(stdVec, vec);
}

BOOST_AUTO_TEST_CASE(vector_class_pointer_clear)
{
    std::vector<StdFoo*> stdVec;
    SketchStl::vector<Foo*> vec;

    StdFoo stdValues[] = { StdFoo(0), StdFoo(1), StdFoo(2), StdFoo(3), StdFoo(4) };
    Foo values[] = { Foo(0), Foo(1), Foo(2), Foo(3), Foo(4) };
    for (size_t i = 0; i < 5; i++) {
        stdVec.push_back(&stdValues[i]);
        vec.push_back(&values[i]);
    }

    stdVec.clear();
    vec.clear();

    BOOST_REQUIRE(CompareVectorsClassPointer(stdVec, vec));
}