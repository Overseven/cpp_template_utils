//
// Created by overseven on 13.03.2021.
//
#include "../func_alias.h"
#include <memory>
#include <iostream>

struct Aa{
    int fooAa(const float& bb, int& value){
        return bb + value;
    }

};

struct Bb{
    int fooBb(const float& bb, int &value) const{
        auto result = bb * value;
        value = 777;
        return result;
    }
};


ALIAS_SIGNATURE_PACK(A, int, const float&, int&)
ALIAS_FUNC(MyAlias, A, fooAa, fooBb)


template<typename...T>
void print(){
    std::cout << __PRETTY_FUNCTION__  << std::endl;
}


void alias(){
    Aa a;
    Bb b;

    int g = 3;

    auto re = MyAlias(a, 14.5f, g);
    auto re2 = MyAlias(b, 14.5f, g);
    std::cout << "Aa: " << re << " Bb: " << re2 << " g: " << g <<  std::endl;
}