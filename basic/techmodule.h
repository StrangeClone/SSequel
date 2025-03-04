#pragma once

#include <string>
#include <set>

using std::string;
using std::set;

enum TechLabel
{
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
    set<TechLabel> labels;

protected:
    const string name;
    void copyLabels(const TechModule *other)
    {
        for (TechLabel label : other->labels)
        {
            addLabel(label);
        }
    }

public:
    TechModule(const string &name) : name(name) {}
    void addLabel(TechLabel label)
    {
        labels.insert(label);
    }

    /**
     * Returns an upgraded version of the TechModule, with the same name
     */
    virtual TechModule *upgrade() const = 0;
};