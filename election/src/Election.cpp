#include <iostream>
#include "simpio.h"
#include "random.h"
#include "genlib.h"

bool simElection(int& voters, double& p1, double& p2, double& error) {
    int v1 = 0;
    int v2 = 0;
    for (int i = 0; i < voters; i++) {
        bool v = randomChance(p1);
        if (randomChance(error))
            v = !v;
        if (v)
            v1++;
        else
            v2++;
    }
    return v1 > v2;
}

double trials(int& trials, int& voters, double& spread, double& error) {
    double false_trials = 0;
    double p1 = 0.5 + spread/2;
    double p2 = 0.5 - spread/2;
    for (int i = 0; i < trials; i++) {
        if (!simElection(voters, p1, p2, error))
            false_trials += 1;
    }
    return false_trials / trials;
}


int main() {
    int voters = getInteger("Number of voters");
    double spread = getReal("Spread?");
    double error = getReal("Error");
    int num_trials = 500;
    double percentage = trials(num_trials, voters, spread, error) * 100;
    cout << "Chance of invalid election result after 500 trials = ";
    cout << percentage;
    cout << "%";
    return 0;
}
