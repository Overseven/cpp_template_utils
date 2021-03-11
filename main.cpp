#include <iostream>
#include "append.h"

struct A{
    int val = 0;
    void push_back(const int &a){
        std::cout << __PRETTY_FUNCTION__ << " val: " << a << std::endl;
        val = a;
    }
};

struct B{
    float val = 0;
    float push_back(const float &b){
        std::cout << __PRETTY_FUNCTION__ << " val: " << b << std::endl;
        val = b;
        return 5.0;
    }
};

struct C{
    int val = 0;
    void append(const int &c){
        std::cout << __PRETTY_FUNCTION__ << " val: " << c << std::endl;
        val = c;
    }
};

struct D{
    double val = 0;
    double append(const double &d){
        std::cout << __PRETTY_FUNCTION__ << " val: " << d << std::endl;
        val = d;
        return 8.0;
    }
};

struct E{
    float val = 0;
    float push(const float &e){
        std::cout << __PRETTY_FUNCTION__ << " val: " << e << std::endl;
        val = e;
        return 8.0f;
    }
};

M_UTIL_COMPOSE(Append, append, push_back, push)



template<typename T>
void test(T t){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main() {
    A a;
    B b;
    C c;
    D d;
    E e;
    Append(a, 11);
    auto b_res = Append(b, 12.0f);
    Append(c, 13);
    auto d_res = Append(d, 14.0);
    Append(e, 24);
    std::cout << "\na.val: " << a.val << "\nb.val: " << b.val << "\nc.val: " << c.val << "\nd.val: " << d.val << std::endl;

    std::cout << "\nb_res: " << b_res << std::endl;
    std::cout << "\nd_res: " << d_res << std::endl;
    return 0;
}
