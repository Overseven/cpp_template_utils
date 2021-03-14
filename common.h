//
// Created by overseven on 13.03.2021.
//

#ifndef TEST_META_UTILS_COMMON_H
#define TEST_META_UTILS_COMMON_H

// Make a FOREACH macro
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME
#define FOR_EACH(action,...) \
  GET_MACRO(_0,__VA_ARGS__,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action,__VA_ARGS__)


// FOREACH macro
#define FE_2_0(WHAT)
#define FE_2_1(WHAT, Arg1, Arg2, X) WHAT(Arg1, Arg2, X)
#define FE_2_2(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_1(WHAT, Arg1, Arg2, __VA_ARGS__)
#define FE_2_3(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_2(WHAT, Arg1, Arg2, __VA_ARGS__)
#define FE_2_4(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_3(WHAT, Arg1, Arg2, __VA_ARGS__)
#define FE_2_5(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_4(WHAT, Arg1, Arg2, __VA_ARGS__)
#define FE_2_6(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_5(WHAT, Arg1, Arg2, __VA_ARGS__)
#define FE_2_7(WHAT, Arg1, Arg2, X, ...) WHAT(Arg1, Arg2, X)FE_2_6(WHAT, Arg1, Arg2, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO_2(_0,_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME

#define FOR_EACH_2(action,Arg1, Arg2,...) \
  GET_MACRO_2(_0,Arg1, Arg2, __VA_ARGS__,FE_2_5,FE_2_4,FE_2_3,FE_2_2,FE_2_1,FE_2_0)(action,Arg1, Arg2,__VA_ARGS__)


#define GET_HEAD(Head, ...) Head
#define GET_TAIL(Head, ...) __VA_ARGS__




template<typename...Types>
struct TypeList;

template<typename H, typename...T>
struct TypeList<H, T...> : TypeList<T...>{
    using Head = H;
    using Tail = TypeList<T...>;
};

template<>
struct TypeList<>{};


#endif //TEST_META_UTILS_COMMON_H
