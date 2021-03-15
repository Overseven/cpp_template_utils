#include <iostream>
#include "../func_abstract.h"
#include <memory>

struct S{
    UTIL_ABSTRACT(Print, print, Log, log, OutMessage, println)
};

struct A{
    int val = 0;
    void push_back(const int &a){
        std::cout << __PRETTY_FUNCTION__ << " val: " << a << std::endl;
        val = a;
    }
    void print(){
        std::cout << __FUNCTION__ << " without args" << std::endl;
    }
};

struct B{
    float val = 0;
    float push_back(const float &b, int b2){
        std::cout << __PRETTY_FUNCTION__ << " val: " << b << " second arg: " << b2 << std::endl;
        val = b;
        return 5.0;
    }
    void Log(std::string text){
        std::cout << __FUNCTION__ << " " << text << std::endl;
    }
};

struct C{
    int val = 0;
    void append(const int &c){
        std::cout << __PRETTY_FUNCTION__ << " val: " << val << std::endl;
    }
    void log(std::string text){
        std::cout << __FUNCTION__ << " " << text << std::endl;
    }
};

struct D{
    double val = 0;
    double append(const double &d){
        std::cout << __PRETTY_FUNCTION__ << " val: " << d << std::endl;
        val = d;
        return 8.0;
    }
    void OutMessage(std::string text){
        std::cout << __FUNCTION__ << " " << text << std::endl;
    }
};

struct E{
    float val = 0;
    float push(const float &e){
        std::cout << __PRETTY_FUNCTION__ << " val: " << e << std::endl;
        val = e;
        return 8.0f;
    }
    void println(std::string text){
        std::cout << __FUNCTION__ << " " << text << std::endl;
    }
};


UTIL_ABSTRACT(MyAbstraction, append, push_back, push)

UTIL_ABSTRACT(PrintFunction, print, Log, OutMessage)


void abstract() {
    A a;
    B b;
    C c;
    D d;
    E e;
    MyAbstraction(a, 11);
    auto b_res = MyAbstraction(b, 12.0f, 3);
    MyAbstraction(c, 13);
    auto d_res = MyAbstraction(d, 14.0);
    MyAbstraction(e, 24);
    std::cout << "\na.val: " << a.val << "\nb.val: " << b.val << "\nc.val: " << c.val << "\nd.val: " << d.val << std::endl;

    std::cout << "\nb_res: " << b_res << std::endl;
    std::cout << "d_res: " << d_res << std::endl << std::endl;

    S s;
    s.Print(a);
    s.Print(b, "b?");
    s.Print(c, "c?");
    s.Print(d, "d?");
    s.Print(e, "e?");
}
