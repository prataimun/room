#include "person.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << "Person{x="     << p.x     <<
                      ", y="     << p.y     <<
                      ", z="     << p.z     <<
                      ", alpha=" << p.alpha <<
                      ", beta="  << p.beta  <<
                      ", gamma=" << p.gamma <<
                      "}";
}
