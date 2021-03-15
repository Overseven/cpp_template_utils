//
// Created by overseven on 13.03.2021.
//

#include "../func_alias.h"
#include <memory>
#include <iostream>

struct AliasTest1{
    int fooTest1(const float& bb, int& value){
        return bb + value;
    }

};

struct AliasTest2{
    int fooTest2(const float& bb, int &value) const{
        auto result = bb * value;
        value = 777;
        return result;
    }
};


UTIL_ALIAS_SIGNATURE_PACK(A, int, const float&, int&)

UTIL_ALIAS(MyAlias, A, fooTest1, fooTest2)


void alias(){
    AliasTest1 a;
    AliasTest2 b;

    int value = 3;

    auto result1 = MyAlias(a, 10.5f, value);
    auto result2 = MyAlias(b, 14.1f, value);

    std::cout << "result1: " << result1 << std::endl
              << "result2: " << result2 << std::endl
              << "value: "   << value   << std::endl;
}