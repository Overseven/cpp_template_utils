//
// Created by Bogdanovskiy on 11.03.2021.
//

#ifndef META_UTILS_APPEND_H
#define META_UTILS_APPEND_H


#define M_UTIL_HELPERFUNC(FuncName)                 \
template<typename C, typename...Args>               \
auto func_helper_##FuncName (C& c, Args...args){    \
    return c.FuncName(args...);                     \
}

#define M_UTIL_HELPERFUNC_WITH_VOID_CHECK(FuncName) \
template<typename C, typename...Args> \
auto func_helper_##FuncName (C& c, Args...args){ \
    constexpr bool IsVoid = std::is_void_v<std::invoke_result_t<decltype(&C::FuncName), C, args...>>; \
    if constexpr (IsVoid){ \
        std::cout << #FuncName ". void. val: " << val << std::endl; \
        c.FuncName(args...); \
    }else{ \
        std::cout << "func_helper_" #FuncName ". non-void. val: " << val << std::endl; \
        return c.FuncName(args...); \
    } \
}


#define M_UTIL_HASFUNCSTRUCT(FuncName)                  \
template <typename T>                                   \
class has_##FuncName                                    \
{                                                       \
    typedef char one;                                   \
    struct two { char x[2]; };                          \
    template <typename C>                               \
    static one test( decltype(&C::FuncName) ) {}        \
    template <typename C>                               \
    static two test(...){}                              \
public:                                                 \
    enum { value = sizeof(test<T>(0)) == sizeof(char) };\
};

#define M_UTIL_HASFUNC(ClassName, FuncName) \
has_##FuncName <ClassName>::value


// Make a FOREACH macro
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO(_0,_1,_2,_3,_4,_5,NAME,...) NAME
#define FOR_EACH(action,...) \
  GET_MACRO(_0,__VA_ARGS__,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action,__VA_ARGS__)

#define GET_HEAD(Head, ...) Head
#define GET_TAIL(Head, ...) __VA_ARGS__

// Main macros
#define M_UTIL_COMPOSE(FuncName, ...) \
FOR_EACH(M_UTIL_HASFUNCSTRUCT, __VA_ARGS__)                            \
FOR_EACH(M_UTIL_HELPERFUNC, __VA_ARGS__)                               \
                                                                       \
template <typename C, typename...Args>                                 \
auto FuncName(C& c, Args...args){                                      \
    M_UTIL_IF_BRANCH(GET_HEAD(__VA_ARGS__))                            \
    FOR_EACH(M_UTIL_ELSE_BRANCH, GET_TAIL(__VA_ARGS__) )               \
}



#define M_UTIL_IF_BRANCH(Name) \
if constexpr (M_UTIL_HASFUNC(C, Name)){          \
    return M_UTIL_HELP_F( Name)<C, Args...>(c, args...); \
}

#define M_UTIL_ELSE_BRANCH(Name) \
else if constexpr (M_UTIL_HASFUNC(C, Name)){          \
    return M_UTIL_HELP_F( Name)<C, Args...>(c, args...); \
}



#define M_UTIL_HELP_F(FuncName) \
func_helper_##FuncName



#endif //META_UTILS_APPEND_H
