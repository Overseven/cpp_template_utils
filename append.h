//
// Created by Bogdanovskiy on 11.03.2021.
//

#ifndef META_UTILS_APPEND_H
#define META_UTILS_APPEND_H

#define M_UTIL_HELPERFUNC(FuncName)                             \
template<typename Cont, typename T>                             \
auto func_helper_##FuncName (Cont& container, const T& val){    \
    return container.FuncName(val);                             \
}

#define M_UTIL_HELPERFUNC_WITH_VOID_CHECK(FuncName) \
template<typename Cont, typename T> \
auto func_helper_##FuncName (Cont& container, const T& val){ \
    constexpr bool IsVoid = std::is_void_v<std::invoke_result_t<decltype(&Cont::FuncName), Cont, const T&>>; \
    if constexpr (IsVoid){ \
        std::cout << #FuncName ". void. val: " << val << std::endl; \
        container.FuncName(val); \
    }else{ \
        std::cout << "func_helper_" #FuncName ". non-void. val: " << val << std::endl; \
        return container.FuncName(val); \
    } \
}

#define M_UTIL_HELP_F(FuncName) \
func_helper_##FuncName


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


#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x)\
  FOR_EACH_1(what,  __VA_ARGS__);
#define FOR_EACH_3(what, x, ...)\
  what(x)\
  FOR_EACH_2(what, __VA_ARGS__);
#define FOR_EACH_4(what, x, ...)\
  what(x)\
  FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...)\
  what(x)\
 FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...)\
  what(x)\
  FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...)\
  what(x)\
  FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...)\
  what(x)\
  FOR_EACH_7(what,  __VA_ARGS__);


#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  arg1##arg2

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)




#define M_UTIL_COMPOSE(FuncName, InternalFuncName1, InternalFuncName2) \
                                                                       \
FOR_EACH(M_UTIL_HASFUNCSTRUCT, append, push_back)                      \
FOR_EACH(M_UTIL_HELPERFUNC, append, push_back)                         \
                                                                       \
template <typename Cont, typename T>                                   \
auto FuncName(Cont& c, const T& t){                                    \
    if constexpr (M_UTIL_HASFUNC(Cont, InternalFuncName1)){            \
        return M_UTIL_HELP_F(InternalFuncName1)<Cont, T>(c, t);        \
    }else if (M_UTIL_HASFUNC(Cont, InternalFuncName2)){                \
        return M_UTIL_HELP_F(InternalFuncName2)<Cont, T>(c, t);        \
    }                                                                  \
}

#endif //META_UTILS_APPEND_H
