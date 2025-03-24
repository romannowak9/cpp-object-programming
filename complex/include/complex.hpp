#ifndef COMPLEX_1_COMPLEX_HPP
#define COMPLEX_1_COMPLEX_HPP

#include <iostream>

class Complex{
public:
    Complex(double re, double im) : re_(re), im_(im) {}
    Complex(double* data) : Complex(data[0], data[1]) {}
    double re() const { return re_; }
    double im() const { return im_; }
private:
    double re_;
    double im_;

};

#endif //COMPLEX_1_COMPLEX_HPP
