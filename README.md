# cpp_template_utils
Header-only compile-time templates.

## Abstraction of functions
Macro ``M_UTIL_ABSTRACT(arg0, arg1, ...)`` create template function with ``arg0`` name, which abstract a class member functions with one of the name ``arg1, arg2, ...``. 
Max count of abstracted functions is 5, but it can be change with edit ``FOR_EACH`` macros.    
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

// The macro below create abstraction of "print", "Log", "OutMessage" 
// functions with name "PrintFunction"
M_UTIL_ABSTRACT(PrintFunction, print, Log, OutMessage)

int main() {
    A a;
    B b;
    C c;
    // Using the new function
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