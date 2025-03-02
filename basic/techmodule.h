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

/**
 * Represents a generic technology in posses of an empire
 */
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

    /**
     * Returns an upgraded version of the TechModule, with the same name
     */
    virtual TechModule* upgrade() const = 0;
};