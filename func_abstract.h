//
// Created by Bogdanovskiy on 11.03.2021.
//

#ifndef META_UTILS_ABSTRACT_H
#define META_UTILS_ABSTRACT_H
#include "common.h"

#define UTIL_ABSTRACT_HAS_FUNC_STRUCT(FuncName)         \
template <typename T>                                   \
class has_##FuncName                                    \
{                                                       \
    typedef char one;                                   \
    struct two { char x[2]; };                          \
    template <typename C>                               \
    static one test( decltype(&C::FuncName) ){          \
        return one{};                                   \
    }                                                   \
                                                        \
    template <typename C>                               \
    static two test(...){                               \
        return two{};                                   \
    }                                                   \
public:                                                 \
    enum { value = sizeof(test<T>(0)) == sizeof(char) };\
};


#define UTIL_HELPER_FUNC(FuncName)                      \
template<typename Class, typename...Args>               \
auto func_helper_##FuncName (Class& c, Args&&...args){  \
    return c.FuncName(std::forward<Args>(args)...);     \
}


// Main macros
template<class ...>
typename std::false_type always_false{};

#define UTIL_ABSTRACT(FuncName, ...)                                  \
  FOR_EACH(UTIL_ABSTRACT_HAS_FUNC_STRUCT, __VA_ARGS__)                \
  FOR_EACH(UTIL_HELPER_FUNC, __VA_ARGS__)                             \
                                                                      \
template <typename Class, typename...Args>                            \
auto FuncName(Class& c, Args&&...args){                               \
    UTIL_ABSTRACT_IF_BRANCH(GET_HEAD(__VA_ARGS__))                    \
    FOR_EACH(UTIL_ABSTRACT_ELSE_BRANCH, GET_TAIL(__VA_ARGS__) )       \
    else{                                                             \
        static_assert(always_false<Class>, "No one suitable "         \
        "function is found!");                                        \
    }                                                                 \
}


#define UTIL_ABSTRACT_IF_BRANCH(Name)                   \
if constexpr (UTIL_ABSTRACT_HAS_FUNC(Class, Name)){     \
    return c.Name(std::forward<Args>(args)...);         \
}


#define UTIL_ABSTRACT_ELSE_BRANCH(Name)                     \
else if constexpr (UTIL_ABSTRACT_HAS_FUNC(Class, Name)){    \
    return c.Name(std::forward<Args>(args)...);             \
}

#define UTIL_ABSTRACT_HAS_FUNC(ClassName, FuncName) \
has_##FuncName <ClassName>::value


#endif //META_UTILS_ABSTRACT_H