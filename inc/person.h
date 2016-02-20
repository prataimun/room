#ifndef PERSON_H
#define PERSON_H

#include <iostream>

/* A person at a position facing a direction. */
class Person {
private:
    double xdpOld, zdpOld;
public:
    double x, y, z, xd, yd, zd;
    Person(double x         = 0.0, double y         =   0.0, double z = 5.0,
           double xyDegrees = 0.0, double zxDegrees = 0.0);
    void moveForward(double);
    void strafeRight(double);
    void ascend(double);
    void rotateVertical(double);
    void rotateHorizontal(double);
};

std::ostream& operator<<(std::ostream& os, const Person& p);

#endif
