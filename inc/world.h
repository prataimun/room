#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <ctime>
#include "person.h"

/* This class is responsible for the connection with the graphical framework. */
class World {
    static void (*nullOperation)(double, int, int, Person *);
    /* This maps an input character with a certain function. The mapped function
     * is in the second position of the pair. The first function in the pair is
     * either the nullOperation or the mapped function depending on if the key
     * is pressed or not.*/
    std::map<char, std::pair<void (*)(double, int, int, Person *),
             void (*)(double, int, int, Person *)>> controls;
    clock_t lastClock;
    bool trackMouse;
    Person victor;
public:
    World() {}
    void init(int width, int height);
    void idle();
    void display();
    void reshape(int width, int height);
    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void mouseClick(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    int width, height;
};

#endif
