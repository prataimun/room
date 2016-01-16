#ifndef PERSON_H
#define PERSON_H

#include <iostream>

/* A person at a position facing a direction. */
class Person {
public:
    Person(double x     = 0.0, double y    = 1.0 , double z     = 0.0,
           double alpha = 0.0, double beta = 90.0, double gamma = 0.0) :
    x(x), y(y), z(z), alpha(alpha), beta(beta), gamma(gamma) {}
    double x, y, z, alpha, beta, gamma;
};

std::ostream& operator<<(std::ostream& os, const Person& p);

#endif
