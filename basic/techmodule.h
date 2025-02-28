#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class TechModule
{
private:
    string name;
    vector<TechLabel> labels;

public:
    TechModule(string name) : name(name) {}
    void addLabel(TechLabel label) {
        labels.push_back(label);
    }

    virtual TechModule* upgrade() const = 0;
};

enum TechLabel {
    job_primary,
    job_auxiliar,
    energy,
    minerals,
    food
};