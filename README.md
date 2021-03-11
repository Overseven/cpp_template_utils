# cpp_template_utils

## Abstraction of functions
### Example
```c++
#include <iostream>
#include "func_abstract.h"

struct A{
    void print(){
        std::cout << "A::print() without args" << std::endl;
    }
};

struct B{
    void Log(std::string text){
        std::cout << "B::Log() " << text << std::endl;
    }
};

struct C{
    void OutMessage(std::string text, int num){
        std::cout << "C::OutMessage() " << text << " second arg: " << num << std::endl;
    }
};

M_UTIL_ABSTRACT(PrintFunction, print, Log, OutMessage)

int main() {
    A a;
    B b;
    C c;

    PrintFunction(a);
    PrintFunction(b, "b?");
    PrintFunction(c, "c?", 112);
    return 0;
}
```

Console output:

````
A::print() without args
B::Log() b?
C::OutMessage() c? second arg: 112

````