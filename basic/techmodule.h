#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

enum TechLabel {
    job_primary,
    job_auxiliar,
    energetic,
    mining,
    agricoltural,
    tool
};

class TechModule
{
protected:
    const string name;
    vector<TechLabel> labels;

public:
    TechModule(const string& name) : name(name) {}
    void addLabel(TechLabel label) {
        labels.push_back(label);
    }

    virtual TechModule* upgrade() const = 0;
};