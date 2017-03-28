// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
using namespace std;

class PatientQueue {
public:
    PatientQueue();
    ~PatientQueue();
    void clear();
    string frontName();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);


private:
    // TODO: add specified member variable(s)
    // TODO: add any member functions necessary

    friend ostream& operator <<(ostream& out, const PatientQueue& queue);
};

/*
 */
ostream& operator <<(ostream& out, const PatientQueue& queue);

