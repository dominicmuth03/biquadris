#ifndef _SUBJECT_
#define _SUBJECT_

#include <vector>
#include <memory>
#include "observer.h"

class Observer;

class Subject
{
    std::vector<Observer *> observers;

public:
    virtual ~Subject() = default;

    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    
    virtual std::vector<std::vector<char>> getState() = 0;
};

#endif
