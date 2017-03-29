// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "patientqueue.h"

PatientQueue::PatientQueue() {
    // TODO: write this constructor
    this->head = nullptr;
}

PatientQueue::~PatientQueue() {
   clear();
}

void PatientQueue::clear() {
    // TODO: write this function
    PatientNode* temp;
    while (this->head) {
        temp = this->head->next;
        delete this->head;
        this->head = temp;
    }
}

string PatientQueue::frontName() {
    // TODO: write this function
    if (!this->head)
        throw new string("The patient queue is empty. Call to frontName invalid.");
    return this->head->name;
}

int PatientQueue::frontPriority() {
    // TODO: write this function
    if (!this->head)
        throw new string("The patient queue is empty. Call to frontPriority invalid.");
    return this->head->priority;
}

bool PatientQueue::isEmpty() {
    // TODO: write this function
    return ! this->head;
}

void PatientQueue::newPatient(string name, int priority) {
    PatientNode* patient = new PatientNode(name, priority);
    PatientNode* before = findPred(priority);
    if (!before) {
        newHead(patient);
        return;
    }
    insertAfter(before, patient);
}

string PatientQueue::processPatient() {
    if (!this->head)
        throw new string("The patient queue is empty. Call to processPatient invalid.");
    PatientNode* oldHead = this->head;
    this->head = oldHead->next;
    string s = oldHead->name;
    delete oldHead;
    return s;
    // TODO: write this function
}

void PatientQueue::upgradePatient(string name, int newPriority) {
    PatientNode* pred = findPred(name);
    PatientNode* toInsert = deleteAfter(pred);
    toInsert->priority = newPriority;
    PatientNode* before = findPred(newPriority);
    if (!before) {
        newHead(toInsert);
        return;
    }
    insertAfter(before, toInsert);
    // TODO: write this function
}

ostream& operator <<(ostream& out, const PatientQueue& queue) {
    out << "{";
    if (queue.head) {
        out << *queue.head;
        PatientNode* pointer = queue.head->next;
        while (pointer) {
            out << ", ";
            out << *pointer;
            pointer = pointer->next;
        }
    }
    out << "}";
    // TODO: write this function
    return out;
}

PatientNode* PatientQueue::findPred(int priority) {
    if (!this->head || priority < this->head->priority)
        return nullptr;
    PatientNode* before = this->head;
    PatientNode* after = before->next;
    while (after && after->priority < priority) {
        before = after;
        after = after->next;
    }
    return before;
}
PatientNode* PatientQueue::findPred(string name) {
    if (!this->head || this->head->name == name)
        return nullptr;
    PatientNode* before = this->head;
    PatientNode* after = before->next;
    while (after->name != name) {
        before = after;
        after = after->next;
    }
    return before;
}

PatientNode* PatientQueue::deleteAfter(PatientNode* node) {
    PatientNode* temp = node->next;
    node->next = temp->next;
    return temp;
}

void PatientQueue::insertAfter(PatientNode* node, PatientNode* toInsert) {
    toInsert->next = node->next;
    node->next = toInsert;
}

void PatientQueue::deleteHead() {
    PatientNode* temp = this->head;
    this->head = head->next;
    delete temp;
}

void PatientQueue::newHead(PatientNode* head) {
    head->next = this->head;
    this->head = head;
}
