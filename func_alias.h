//
// Created by overseven on 13.03.2021.
//

#ifndef TEST_META_UTILS_FUNC_ALIAS_H
#define TEST_META_UTILS_FUNC_ALIAS_H

#include "common.h"

#define ALIAS_SIGNATURE_PACK(PackName, ReturnType, ...) \
using Return_##PackName = ReturnType;                   \
using Args_##PackName = TypeList<__VA_ARGS__>;


#define ALIAS_HAS_FUNC_STRUCT(FuncName) \
template <typename Class, typename Return, typename...T>            \
class alias_has_##FuncName;                                         \
                                                                    \
template <typename Class, typename Return, typename ...Args>        \
class alias_has_##FuncName<Class, Return, TypeList<Args...>>        \
{                                                                   \
typedef char one;                                                   \
struct two { char x[2]; };                                          \
                                                                    \
template<typename U, Return (U::*f)(Args...)>                       \
struct SFINAE_NO_CONST {};                                          \
                                                                    \
template<typename U,  Return (U::*f)(Args...) const>                \
struct SFINAE_CONST {};                                             \
                                                                    \
template<typename U>                                                \
static one test(SFINAE_NO_CONST<U, &U::FuncName>*){ return one(); };\
                                                                    \
template<typename U>                                                \
static one test(SFINAE_CONST<U, &U::FuncName>*){ return one(); };   \
                                                                    \
template <typename C>                                               \
static two test(...){ return two(); }                               \
                                                                    \
public:                                                             \
enum { value = sizeof(test<Class>(0)) == sizeof(one) };             \
};





#define ALIAS_FUNC(Alias, PackName, ...)                                        \
FOR_EACH(ALIAS_HAS_FUNC_STRUCT, __VA_ARGS__)                                    \
                                                                                \
template<class Class, typename Return, typename...Args>                         \
struct Internal_##Alias;                                                        \
                                                                                \
                                                                                \
                                                                                \
template<class Class, typename...Args>                                          \
struct Internal_##Alias<Class, Return_##PackName, TypeList<Args...>>{           \
    template<class ...>                                                         \
    static constexpr std::false_type always_false{};                            \
    Return_##PackName call(Class &c, Args&&...args) {                           \
        ALIAS_IF_BRANCH(PackName, GET_HEAD(__VA_ARGS__))                        \
        FOR_EACH_2(ALIAS_ELSE_BRANCH, PackName, 0, GET_TAIL(__VA_ARGS__) )      \
        else{                                                                   \
            static_assert(always_false<Class>, "No one suitable "               \
            "function is found!");                                              \
        }                                                                       \
    }                                                                           \
};                                                                              \
                                                                                \
template<class Class, typename ...Args>                                         \
Return_##PackName Alias(Class &c, Args&&...args) {                              \
    return Internal_##Alias<Class, Return_##PackName,                           \
    Args_##PackName>{}.call(c, std::forward<Args>(args)...);                    \
}


#define ALIAS_IF_BRANCH(PackName, FuncName)             \
if constexpr (ALIAS_HAS_FUNC(PackName, FuncName)){      \
    return c.FuncName(std::forward<Args>(args)...);     \
}


#define ALIAS_ELSE_BRANCH(PackName, Unused, FuncName)   \
else if constexpr (ALIAS_HAS_FUNC(PackName, FuncName)){ \
    return c.FuncName(std::forward<Args>(args)...);     \
}

#define ALIAS_HAS_FUNC(PackName, FuncName) \
alias_has_##FuncName <Class, Return_##PackName, Args_##PackName>::value


#endif //TEST_META_UTILS_FUNC_ALIAS_H
