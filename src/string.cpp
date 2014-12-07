#include "string.h"

#include <assert.h>
#include <stdlib.h>

namespace SketchStl {

string::string() : data_(nullptr), length_(0), capacity_(1) {
    data_ = (char*)malloc(1);
    data_[length_] = '\0';
}

string::string(const string& str) {
    length_ = str.length_;
    capacity_ = str.capacity_;

    if (capacity_ > 0) {
        data_ = (char*)malloc(capacity_);
        for (size_t i = 0; i < length_; i++) {
            data_[i] = str.data_[i];
        }
        data_[length_] = '\0';
    }
}

string::string(const string& str, size_t pos, size_t len) : data_(nullptr), length_(len), capacity_(len) {
    if (capacity_ > 0) {
        capacity_ += 1;
        data_ = (char*)malloc(capacity_);
        size_t idx = pos;
        for (size_t i = 0; i < length_; i++) {
            data_[i] = str[pos++];
        }
        data_[length_] = '\0';
    }
}

string::string(const char* s) : data_(nullptr), length_(0), capacity_(0) {
    if (s == nullptr) {
        return;
    }

    const char* begin = s;
    while (*begin++) {
        length_ += 1;
        capacity_ += 1;
    }

    if (capacity_ > 0) {
        capacity_ += 1;

        data_ = (char*)malloc(capacity_);
        for (size_t i = 0; i < length_; i++) {
            data_[i] = *s++;
        }
        data_[length_] = '\0';
    }
}

string::string(const char* s, size_t n) : data_(nullptr), length_(n), capacity_(n) {
    if (capacity_ > 0) {
        capacity_ += 1;

        data_ = (char*)malloc(capacity_);
        for (size_t i = 0; i < length_; i++) {
            data_[i] = *s++;
        }
        data_[length_] = '\0';
    }
}

string::string(size_t n, char c) : data_(nullptr), length_(n), capacity_(n) {
    if (capacity_ > 0) {
        capacity_ += 1;

        data_ = (char*)malloc(capacity_);
        for (size_t i = 0; i < length_; i++) {
            data_[i] = c;
        }
        data_[length_] = '\0';
    }
}

string::~string() {
    free(data_);
}

string& string::operator=(const string& str) {
    if (&str != this) {
        free(data_);

        length_ = str.length_;
        capacity_ = str.capacity_;

        if (capacity_ > 0) {
            data_ = (char*)malloc(capacity_);
            for (size_t i = 0; i < length_; i++) {
                data_[i] = str.data_[i];
            }
            data_[length_] = '\0';
        }
    }

    return *this;
}

string& string::operator=(const char* s) {
    if (s != nullptr) {
        free(data_);

        const char* begin = s;
        while (*begin++) {
            length_ += 1;
            capacity_ += 1;
        }

        if (capacity_ > 0) {
            capacity_ += 1; 

            for (size_t i = 0; i < length_; i++) {
                data_[i] = *s++;
            }
            data_[length_] = '\0';
        }
    }

    return *this;
}

string& string::operator=(char c) {
    free(data_);
    if (c == '\0') {
        length_ = 0;
        capacity_ = 1;
    } else {
        length_ = 1;
        capacity_ = 2;
    }

    data_ = (char*)malloc(capacity_);
    if (length_ > 0) {
        data_[0] = c;
    }
    data_[length_] = '\0';

    return *this;
}

size_t string::size() const {
    return length_;
}

size_t string::length() const {
    return length_;
}

size_t string::max_size() const {
    return -1;
}

void string::resize(size_t n) {
    if (n != length_) {
        char* newData = (char*)malloc(n + 1);
        size_t newLength = 0;

        if (n < length_) {
            newLength = n;
        } else {
            newLength = length_;
        }

        for (size_t i = 0; i < newLength; i++) {
            newData[i] = data_[i];
        }
        newData[newLength] = '\0';

        free(data_);
        data_ = newData;
        length_ = n;
        capacity_ = length_ + 1;
    }
}

void string::resize(size_t n, char c) {
    size_t oldLength = length_;
    resize(n);

    if (oldLength < length_) {
        for (size_t i = oldLength; i < length_; i++) {
            data_[i] = c;
        }
        data_[length_] = '\0';
    }
}

size_t string::capacity() const {
    return capacity_;
}

void string::reserve(size_t n) {
    if (n > (capacity_ - 1)) {
        char* newData = (char*)malloc(n + 1);

        for (size_t i = 0; i < length_; i++) {
            newData[i] = data_[i];
        }
        newData[length_] = '\0';
        free(data_);
        data_ = newData;
        capacity_ = n + 1;
    }
}

void string::clear() {
    free(data_);
    data_ = (char*)malloc(1);
    data_[0] = '\0';
    length_ = 0;
    capacity_ = 1;
}

bool string::empty() const {
    return length_ == 0;
}

char& string::operator[](size_t pos) {
    assert(pos < length_);
    return data_[pos];
}

const char& string::operator[](size_t pos) const {
    assert(pos < length_);
    return data_[pos];
}

char& string::at(size_t pos) {
    assert(pos < length_);
    return data_[pos];
}

const char& string::at(size_t pos) const {
    assert(pos < length_);
    return data_[pos];
}

string& string::operator+=(const string& str) {
    size_t newSize = length_ + str.length_;
    if (newSize > (capacity_ - 1)) {
        char* newData = (char*)malloc(newSize + 1);

        for (size_t i = 0; i < length_; i++) {
            newData[i] = data_[i];
        }

        free(data_);
        data_ = newData;
    }

    size_t idx = 0;
    for (size_t i = length_; i < newSize; i++) {
        data_[i] = str.data_[idx++];
    }
    data_[newSize] = '\0';
    length_ = newSize;
    capacity_ = length_ + 1;

    return *this;
}

string& string::operator+=(const char* s) {
    return (*this) += string(s);
}

string& string::operator+=(char c) {
    if (length_ + 1 > (capacity_ - 1)) {
        char* newData = (char*)malloc(capacity_ + 1);

        for (size_t i = 0; i < length_; i++) {
            newData[i] = data_[i];
        }

        free(data_);
        data_ = newData;
    }

    data_[length_] = c;
    data_[length_ + 1] = '\0';
    length_ += 1;
    capacity_ += 1;

    return *this;
}

string& string::append(const string& str) {
    return (*this += str);
}

string& string::append(const string& str, size_t subpos, size_t sublen) {
    return (*this += str.substr(subpos, sublen));
}

string& string::append(const char* s) {
    return (*this += s);
}

string& string::append(const char* s, size_t n) {
    string str(s, n);
    return (*this += str);
}

string& string::append(size_t n, char c) {
    string str(n, c);
    return (*this += str);
}

void string::push_back(char c) {
    *this += c;
}

string& string::assign(const string& str) {
    return (*this = str);
}

string& string::assign(const string& str, size_t subpos, size_t sublen) {
    return (*this = str.substr(subpos, sublen));
}

string& string::assign(const char* s) {
    return (*this = s);
}

string& string::assign(const char* s, size_t n) {
    string str(s, n);
    return (*this = str);
}

string& string::assign(size_t n, char c) {
    string str(n, c);
    return (*this = str);
}

string& string::insert(size_t pos, const string& str) {
    size_t newLength = length_ + str.length_;

    if (newLength > (capacity_ - 1)) {
        // Allocate enough space and insert the string
        char* newData = (char*)malloc(newLength + 1);

        size_t endIdx = 0;
        for (; endIdx < pos; endIdx++) {
            newData[endIdx] = data_[endIdx];
        }

        size_t endPos = pos + str.length_;
        size_t idx = 0;
        for (size_t i = pos; i < endPos; i++) {
            newData[i] = str.data_[idx++];
        }

        for (size_t i = endPos; i < newLength; i++) {
            newData[i] = data_[endIdx++];
        }

        free(data_);
        data_ = newData;
        capacity_ = newLength + 1;
    } else {
        char* buffer = (char*)malloc(length_ - pos);

        // Start by copying the portion after the insertion position
        size_t idx = 0;
        for (size_t i = pos; i < str.length_; i++) {
            buffer[idx++] = data_[i];
        }

        // Overwrite the part that we just copied with the string to insert and append back the buffer
        idx = 0;
        size_t endPos = pos + str.length_;
        for (size_t i = pos; i < endPos; i++) {
            data_[i] = str.data_[idx++];
        }

        idx = 0;
        for (size_t i = endPos; i < newLength; i++) {
            data_[i] = buffer[idx++];
        }

        free(buffer);
    }

    length_ = newLength;

    return *this;
}

string& string::insert(size_t pos, const string& str, size_t subpos, size_t sublen) {
    return insert(pos, str.substr(subpos, sublen));
}

string& string::insert(size_t pos, const char* s) {
    string str(s);
    return insert(pos, str);
}

string& string::insert(size_t pos, const char* s, size_t n) {
    string str(s, n);
    return insert(pos, str);
}

string& string::insert(size_t pos, size_t n, char c) {
    string str(n, c);
    return insert(pos, str);
}

string& string::erase(size_t pos, size_t len) {
    assert(pos < length_);

    // Copy the left part of the buffer
    char* leftBuffer = (char*)malloc(pos);
    for (size_t i = 0; i < pos; i++) {
        leftBuffer[i] = data_[i];
    }

    // Copy the right part of the buffer
    size_t rightSize = length_ - pos - len;
    char* rightBuffer = (char*)malloc(rightSize);

    size_t idx = pos + len;
    for (size_t i = 0; i < rightSize; i++) {
        rightBuffer[i] = data_[idx++];
    }

    // Resize and concatenate the two buffers
    free(data_);
    length_ = pos + rightSize;
    capacity_ = length_ + 1;
    data_ = (char*)malloc(capacity_);

    for (size_t i = 0; i < pos; i++) {
        data_[i] = leftBuffer[i];
    }

    idx = pos;
    for (size_t i = 0; i < rightSize; i++) {
        data_[idx++] = rightBuffer[i];
    }

    data_[length_] = '\0';

    free(leftBuffer);
    free(rightBuffer);

    return *this;
}

string& string::replace(size_t pos, size_t len, const string& str) {
    assert(pos < length_);

    size_t lengthToReplace = len;
    if (lengthToReplace > str.length_) {
        lengthToReplace = str.length_;
    }

    size_t endPos = pos + lengthToReplace;
    if (endPos > length_) {
        endPos = length_;
    }

    size_t idx = 0;
    for (size_t i = pos; i < endPos; i++) {
        data_[i] = str.data_[idx++];
    }

    return *this;
}

string& string::replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) {
    return replace(pos, len, str.substr(subpos, sublen));
}

string& string::replace(size_t pos, size_t len, const char* s) {
    return replace(pos, len, string(s));
}

string& string::replace(size_t pos, size_t len, const char* s, size_t n) {
    return replace(pos, len, string(s, n));
}

string& string::replace(size_t pos, size_t len, size_t n, char c) {
    return replace(pos, len, string(n, c));
}

void string::swap(string& str) {
    char* tmpBuffer = data_;
    size_t tmpLength = length_;
    size_t tmpCapacity = capacity_;

    data_ = str.data_;
    length_ = str.length_;
    capacity_ = str.capacity_;
    str.data_ = tmpBuffer;
    str.length_ = tmpLength;
    str.capacity_ = tmpCapacity;
}

const char* string::c_str() const {
    return data_;
}

const char* string::data() const {
    return data_;
}

size_t string::copy(char* s, size_t len, size_t pos) {
    assert(pos < length_);
    size_t endPos = pos + len;
    if (endPos > length_) {
        endPos = length_;
    }

    size_t idx = 0;
    for (size_t i = pos; i < endPos; i++) {
        s[idx++] = data_[i];
    }

    return idx;
}

string string::substr(size_t pos, size_t len) const {
    assert(pos < length_);

    size_t endPos = pos + len;
    if (endPos > length_) {
        endPos = length_;
    }

    size_t size = endPos - pos;
    string substring;
    substring.reserve(size);

    size_t idx = 0;
    for (size_t i = pos; i < endPos; i++) {
        substring.data_[idx++] = data_[i];
    }
    substring.data_[substring.length_] = '\0';

    return substring;
}

int string::compare(const string& str) const {
    if (length_ < str.length_) {
        return -1;
    } else if (length_ > str.length_) {
        return 1;
    }

    int comp = 0;
    for (size_t i = 0; i < length_; i++) {
        comp = data_[i] - str.data_[i];
        
        if (comp < 0) {
            return -1;
        } else if (comp > 0) {
            return 1;
        }
    }

    return 0;
}

int string::compare(size_t pos, size_t len, const string& str) const {
    return substr(pos, len).compare(str);
}

int string::compare(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) const {
    return compare(pos, len, str.substr(subpos, sublen));
}

int string::compare(const char* s) const {
    return compare(string(s));
}

int string::compare(size_t pos, size_t len, const char* s) const {
    return substr(pos, len).compare(s);
}

int string::compare(size_t pos, size_t len, const char* s, size_t n) const {
    return substr(pos, len).compare(string(s, n));
}

string operator+(const string& lhs, const string& rhs) {
    size_t newSize = lhs.length_ + rhs.length_;

    string result;
    result.reserve(newSize);

    for (size_t i = 0; i < lhs.length_; i++) {
        result.data_[i] = lhs.data_[i];
    }

    size_t idx = 0;
    for (size_t i = lhs.length_; i < rhs.length_; i++) {
        result.data_[i] = rhs.data_[idx++];
    }
    result.data_[newSize] = '\0';
    result.length_ = newSize;

    return result;
}

string operator+(const string& lhs, const char* rhs) {
    return lhs + string(rhs);
}

string operator+(const char* lhs, const string& rhs) {
    return string(lhs) + rhs;
}

string operator+(const string& lhs, char rhs) {
    size_t newSize = lhs.length_ + 1;

    string result;
    result.reserve(newSize);

    for (size_t i = 0; i < lhs.length_; i++) {
        result.data_[i] = lhs.data_[i];
    }
    result.data_[lhs.length_] = rhs;
    result.data_[newSize] = '\0';
    result.length_ = newSize;

    return result;
}

string operator+(char lhs, const string& rhs) {
    size_t newSize = rhs.length_ + 1;

    string result;
    result.reserve(newSize);

    result.data_[0] = lhs;
    for (size_t i = 0; i < rhs.length_; i++) {
        result.data_[i + 1] = rhs.data_[i];
    }

    result.data_[newSize] = '\0';
    result.length_ = newSize;

    return result;
}

bool operator==(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) == 0;
}

bool operator==(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) == 0;
}

bool operator==(const char* lhs, const string& rhs) {
    return rhs.compare(lhs) == 0;
}

bool operator!=(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) != 0;
}

bool operator!=(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) != 0;
}

bool operator!=(const char* lhs, const string& rhs) {
    return rhs.compare(lhs) != 0;
}

bool operator<(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) < 0;
}

bool operator<(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) < 0;
}

bool operator<(const char* lhs, const string& rhs) {
    return rhs.compare(lhs) > 0;
}

bool operator<=(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) <= 0;
}

bool operator<=(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) <= 0;
}

bool operator<=(const char* lhs, const string& rhs) {
    return rhs.compare(lhs)>= 0;
}

bool operator>(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) > 0;
}

bool operator>(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) > 0;
}

bool operator>(const char* lhs, const string& rhs) {
    return rhs.compare(lhs) < 0;
}

bool operator>=(const string& lhs, const string& rhs) {
    return lhs.compare(rhs) >= 0;
}

bool operator>=(const string& lhs, const char* rhs) {
    return lhs.compare(rhs) >= 0;
}

bool operator>=(const char* lhs, const string& rhs) {
    return rhs.compare(lhs) <= 0;
}

}