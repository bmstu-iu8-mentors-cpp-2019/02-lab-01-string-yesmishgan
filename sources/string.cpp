// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com
#include "string.hpp"
#include <iostream>
#include <cstring>

//Деструктор объекта класса
String::~String() {delete[] Data;}

//Конструктор объекта класса по умолчанию
String::String() {
    Data = new char[1];
    Data[0] = '\0';
    size_string = 0;
}

//Конструктор копирования
String::String(const String& rhs):String(rhs.Data){}

//Конструктор пользовательский
String::String(const char* data){
    size_string = std::strlen(data);
    Data = new char[size_string + 1];
    std::copy(data, data+size_string + 1, Data);
    Data[size_string] = '\0';
}
//Оператор присвания
String& String::operator=(const String& rhs){
    if (this != &rhs){
        if (!Data) {
        }else{
            delete[] Data;
        }
        size_string = rhs.size_string;
        Data = new char[size_string + 1];
        std::copy(rhs.Data, rhs.Data + rhs.size_string + 1, Data);
    }
    return *this;
}

//Оператор +=
String& String::operator+=(const String& rhs){
    char *temp;
    temp = new char[std::strlen(rhs.Data) + std::strlen(Data) + 1];
    std::copy(Data, Data + std::strlen(Data) + 1, temp);
    std::copy(rhs.Data, rhs.Data + std::strlen(rhs.Data) + 1,
              temp + std::strlen(Data));
    delete[] Data;
    Data = temp;
    //Data[strlen(Data)] = '\0';
    size_string = std::strlen(temp);
    return *this;
}

//Оператор *=
String& String::operator*=(unsigned int m){
    char *temp = new char[std::strlen(Data)*m + 1];
    for (size_t i = 0, t = 0; i < m; ++i, t += std::strlen(Data)){
        std::copy(Data, Data + std::strlen(Data), temp + t);
    }
    temp[std::strlen(Data) * m] = '\0';
    delete[] Data;
    Data = temp;

    size_string = std::strlen(Data);
    return *this;
}

// Оператор ==
bool String::operator==(const String& rhs) const {
    return !std::strcmp(Data, rhs.Data);
}

//Оператор <
bool String::operator<(const String& rhs) const {
    return std::strcmp(Data, rhs.Data) < 0;
}
//Функция длины строки
size_t String::Size() const{ return size_string; }

//Функция проверки на пустоту
bool String::Empty() const{ return size_string == 0; }

//Оператор [] без доступа к элементу
char String::operator[](size_t index) const{
    if (size_string - 1 < index) {
        throw std::out_of_range("You have a problem, out list of range");
        return 0;
    }
    return Data[index];
}

//Оператор [] с доступом к элементу
char& String::operator[](size_t index){
    if (size_string - 1 < index) {
        throw std::out_of_range("You have a problem, out list of range");
    }
    return Data[index];
}

//Функция поиска
size_t String::Find(const String& substr) const{
    bool flag = false;
    int pos = 0;
    for (size_t i = 0; i < size_string - substr.size_string + 1; ++i){
        if (substr.Data[0] == Data[i]){
            pos = i;
            size_t k = 1;
            flag = true;
            for (size_t j = i+1; j < size_string && k < substr.size_string;
            ++j, ++k){
                if (Data[j] == substr.Data[k]){
                    flag = true;
                } else {
                    flag = false;
                    break;
                }
                flag = true;
            }
            if (flag == true) break;
        }
    }
    if (flag == true){
        return pos;
    }else {
        return -1;
    }
}

//Функция замены символов
void String::Replace(char oldSymbol, char newSymbol){
    for (size_t i = 0; i < size_string; ++i) {
        if (Data[i] == oldSymbol) {
            Data[i] = newSymbol;
        }
    }
}

void String::RTrim(char symbol){
    size_t size = 0;
    for (size_t i = size_string - 1; i > 0; --i) {
        if (Data[i] == symbol) {
            size += 1;
        }else{
            break;
        }
    }
    char* temp = new char[size_string - size + 1];
    for (size_t j = 0; j < size_string - size; ++j){
        temp[j] = Data[j];
    }
    temp[size_string - size] = '\0';
    delete[] Data;
    Data = temp;
    size_string = std::strlen(Data);
}

void String::LTrim(char symbol){
    size_t size = 0;
    for (size_t i = 0; i < size_string; ++i) {
        if (Data[i] == symbol) {
            size += 1;
        }else{
            break;
        }
    }
    char* temp = new char[size_string - size + 1];
    std::copy(Data + size, Data + size_string + 1, temp);
    delete[] Data;
    Data = temp;
    size_string = std::strlen(Data);
}

void String::swap(String& oth){
    std::swap(*this, oth);
}

//Оператор +
String operator+(const String& a, const String& b){
    String Result;
    Result += a;
    Result += b;
    return Result;
}

//Оператор *
String operator*(const String& a, unsigned int b){
    String Result = a;
    Result *= b;
    return Result;
}

//Оператор &gt
bool operator>(const String& a, const String& b){
    return b < a;
}

//Оператор !=
bool operator!=(const String& a, const String& b){
    return a > b || a < b;
}

//Оператор <<
std::ostream& operator<<(std::ostream& out, const String& str){
    for (size_t i = 0; i < str.size_string; ++i){
        out << str.Data[i];
    }
    return out;
}
