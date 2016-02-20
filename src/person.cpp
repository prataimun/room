#include "person.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265
const static double degreesToRadians = PI / 180.0;

Person::Person(double x        , double y        , double z,
               double xyDegrees, double zxDegrees) {
    this->x = x;
    this->y = y;
    this->z = z;
    xd = 0.0;
    yd = 0.0;
    zd = -1.0;
    xdpOld = 0.0;
    zdpOld = -1.0;
    rotateVertical(xyDegrees);
    rotateHorizontal(zxDegrees);
}

void Person::moveForward(double distance) {
    x += distance * xd;
    y += distance * yd;
    z += distance * zd;
}

void Person::strafeRight(double distance) {
    // TODO orthonormalize the movement
    x -= distance * zd;
    z += distance * xd;
}

void Person::ascend(double distance) {
    y += distance;
}

void Person::rotateVertical(double degrees) {
    // Orthonormalize the direction onto the x z plane, [dxp, dzp] represents
    // the orthonormalized vector.
    double xdp;
    double zdp;
    if (xd != 0.0) {
        // The following holds:
        // dxp^2 + dzp^2 = 1
        // dxp / dzp = dx / dz
        xdp = 1 / sqrt(1 + (zd*zd)/(xd*xd));
        xdp = xd < 0.0 ? -xdp : xdp; // This is to not loose the sign.
        zdp = xdp * zd / xd;
    } else if (zd != 0.0) {
        // pick the vector in the z direction since xd == 0.0
        xdp = 0.0;
        zdp = zd < 0.0 ? -1.0 : 1.0;
    } else {
        // pick the previous orthonormilization since there isn't a current one.
        xdp = xdpOld;
        zdp = zdpOld;
    }
    xdpOld = xdp;
    zdpOld = zdp;

    // std::cout << "xpdOld: " << xdpOld << ", zpdOld: " << zdpOld << std::endl;

    // Find a perpendicular vector
    double ux = -zdp;
    double uz = xdp;

    // calculate the angle cosinus and sinus
    double rad = degrees * degreesToRadians;
    double cosRad = cos(rad);
    double sinRad = sin(rad);

    // construct the rotation matrix
    double R[3][3];
    R[0][0] = cosRad + ux * ux * (1 - cosRad);
    R[0][1] = -uz * sinRad;
    R[0][2] = ux * uz * (1 - cosRad);
    R[1][0] = uz * sinRad;
    R[1][1] = cosRad;
    R[1][2] = -ux * sinRad;
    R[2][0] = uz * ux * (1 - cosRad);
    R[2][1] = ux * sinRad;
    R[2][2] = cosRad + uz * uz * (1 - cosRad);

    // multiply the rotation matrix with the direction vector
    double xdOld = xd;
    double ydOld = yd;
    double zdOld = zd;
    xd = R[0][0] * xdOld + R[0][1] * ydOld + R[0][2] * zdOld;
    yd = R[1][0] * xdOld + R[1][1] * ydOld + R[1][2] * zdOld;
    zd = R[2][0] * xdOld + R[2][1] * ydOld + R[2][2] * zdOld;

    // TODO when rotating past the y axis we should be facing in the y axis directly
    // don't rotate past the y axis
    if ((xd > 0 && xdOld < 0) || (xd < 0 && xdOld > 0) ||
        (zd > 0 && zdOld < 0) || (zd < 0 && zdOld > 0)) {
        xd = -xd;
        zd = -zd;
    }
    // std::cout << "xd: " << xd << ", yd: " << yd << ", zd: " << zd << std::endl;
}

void Person::rotateHorizontal(double degrees) {
    double xdOld = xd;
    double rad = degrees * degreesToRadians;
    xd =  xdOld * cos(rad) + zd * sin(rad);
    zd = -xdOld * sin(rad) + zd * cos(rad);
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << "Person{x="  << p.x  <<
                      ", y="  << p.y  <<
                      ", z="  << p.z  <<
                      ", xd=" << p.xd <<
                      ", yd=" << p.yd <<
                      ", zd=" << p.zd <<
                      "}";
}
