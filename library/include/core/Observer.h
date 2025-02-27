//
// Created by andrii on 1/30/25.
//

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void update(int state) = 0; // pure virtual function
    virtual ~Observer() = default; // virtual destructor
};

#endif // OBSERVER_H
