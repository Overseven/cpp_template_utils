# cpp_template_utils
Header-only compile-time templates.

## Contents
- [Abstraction](#abstraction)
- [Alias](#alias)
- [Examples of substitution](#examples-of-substitution)
  - [Abstraction macros substitution](#abstraction-macros-substitution)
  - [Alias macros substitution](#alias-macros-substitution)


## Abstraction
The abstraction utility has one macro:
- ``UTIL_ABSTRACT(AbstrName, FuncName1, FuncName2, ...)`` 
  
Which creates template function with ``AbstrName`` name, 
which abstracts class member functions with one of the name ``FuncName1, FuncName2, ...``, ***without strong conformance of signature***.  

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

// The macro below creates abstraction of "print", "Log", "OutMessage" 
// functions with name "PrintFunction"
UTIL_ABSTRACT(PrintFunction, print, Log, OutMessage)

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

## Alias
The alias utility has two macros:

1. ``UTIL_ALIAS_SIGNATURE_PACK(SignPackName, ReturnType, ArgType1, ArgType2, ...)``
2. ``UTIL_ALIAS(AliasName, SignPackName, FuncName1, FuncName2, ...)``

The first macro is just creates two type aliases:
```c++
using Return_PackName = ReturnType;
using Args_PackName = TypeList<ArgType1, ArgType2, ...>;
```

The second macro creates template function with ``AliasName`` name,
which abstracts class member functions with one of the names ``FuncName1, FuncName2, ...``
***with strong conformance of signature***, but with variations of ***const*** function tag existence.

### Example

```c++
#include "func_alias.h"
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

// This macro creates aliases for return and input arguments types
UTIL_ALIAS_SIGNATURE_PACK(A, int, const float&, int&)

// This macro creates aliases for function fooTest1, fooTest2 with signature, described in signature pack A
UTIL_ALIAS(MyAlias, A, fooTest1, fooTest2)


int main(){
    AliasTest1 a;
    AliasTest2 b;

    int value = 3;
    // Using the new function
    auto result1 = MyAlias(a, 10.5f, value);
    auto result2 = MyAlias(b, 14.1f, value);

    std::cout << "result1: " << result1 << std::endl
              << "result2: " << result2 << std::endl
              << "value: "   << value   << std::endl;
    return 0;
}
```

Console output:

````
result1: 13
result2: 42
value: 777
````


## Examples of substitution

For get more detail of created templates, 
this section presents examples of code after macros substitution.


### Abstraction macros substitution
Macro:
```c++
UTIL_ABSTRACT(PrintFunction, print, Log, OutMessage)
```
Generate code:
```c++
template<typename T>
class has_print {
    typedef char one;
    struct two {
        char x[2];
    };
    template<typename C>
    static one test(decltype(&C::print)) { return one{}; }
    
    template<typename C>
    static two test(...) { return two{}; }
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<typename T>
class has_Log {
    typedef char one;
    struct two {
        char x[2];
    };
    template<typename C>
    static one test(decltype(&C::Log)) { return one{}; }
    template<typename C>
    static two test(...) { return two{}; }
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<typename T>
class has_OutMessage {
    typedef char one;
    struct two {
        char x[2];
    };
    template<typename C>
    static one test(decltype(&C::OutMessage)) { return one{}; }
    template<typename C>
    static two test(...) { return two{}; }
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};


template<typename Class, typename...Args>
auto PrintFunction(Class &c, Args &&...args) {
    if constexpr(has_print<Class>::value) {
        return c.print(std::forward<Args>(args)...);
    
    }else if constexpr(has_Log<Class>::value) {
        return c.Log(std::forward<Args>(args)...);
    
    }else if constexpr(has_OutMessage<Class>::value) {
        return c.OutMessage(std::forward<Args>(args)...);
    
    }else { 
        static_assert(always_false<Class>, "No one suitable function is found!");
    }
}
```

### Alias macros substitution
Macros:
```c++
UTIL_ALIAS_SIGNATURE_PACK(A, int, const float&, int&)

UTIL_ALIAS(MyAlias, A, fooTest1, fooTest2)
```
Generate code:
```c++
using Return_A = int;
using Args_A = TypeList<const float &, int &>;

template<typename Class, typename Return, typename...T>
class alias_has_fooTest1;

template<typename Class, typename Return, typename...Args>
class alias_has_fooTest1<Class, Return, TypeList<Args...>> {
    typedef char one;
    struct two {
        char x[2];
    };
    template<typename U, Return(U::*f)(Args...)>
    struct SFINAE_NO_CONST {};
    
    template<typename U, Return(U::*f)(Args...) const>
    struct SFINAE_CONST {};
    
    template<typename U>
    static one test(SFINAE_NO_CONST<U, &U::fooTest1> *) { return one(); };
    
    template<typename U>
    static one test(SFINAE_CONST<U, &U::fooTest1> *) { return one(); };

    template<typename C>
    static two test(...) { return two(); }
public:
    enum { value = sizeof(test<Class>(0)) == sizeof(one) };
};

template<typename Class, typename Return, typename...T>
class alias_has_fooTest2;

template<typename Class, typename Return, typename...Args>
class alias_has_fooTest2<Class, Return, TypeList<Args...>> {
    typedef char one;
    struct two {
        char x[2];
    };

    template<typename U, Return(U::*f)(Args...)>
    struct SFINAE_NO_CONST {};

    template<typename U, Return(U::*f)(Args...) const>
    struct SFINAE_CONST {};

    template<typename U>
    static one test(SFINAE_NO_CONST<U, &U::fooTest2> *) { return one(); };

    template<typename U>
    static one test(SFINAE_CONST<U, &U::fooTest2> *) { return one(); };

    template<typename C>
    static two test(...) { return two(); }
public:
    enum { value = sizeof(test<Class>(0)) == sizeof(one) };
};

template<class Class, typename Return, typename...Args>
struct Internal_MyAlias;

template<class Class, typename...Args>
struct Internal_MyAlias<Class, Return_A, TypeList<Args...>> {
    template<class...> static constexpr std::false_type always_false{};
    
    static Return_A call(Class &c, Args &&...args) {
        if constexpr(alias_has_fooTest1<Class, Return_A, Args_A>::value) {
            return c.fooTest1(std::forward<Args>(args)...);
        
        }else if constexpr(alias_has_fooTest2<Class, Return_A, Args_A>::value) {
            return c.fooTest2(std::forward<Args>(args)...);
        
        }else { 
            static_assert(always_false < Class > , "No one suitable function is found!"); 
        }
    }
};

template<class Class, typename...Args>
Return_A MyAlias(Class &c, Args &&...args) {
    return Internal_MyAlias<Class, Return_A, Args_A>::call(c, std::forward<Args>(args)...);
}
```
