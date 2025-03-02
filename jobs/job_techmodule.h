#pragma once

#include "../basic/techmodule.h"
#include "../basic/resources.h"
#include "../basic/context.h"

#include <unordered_map>

using std::unordered_map;

/**
 * TechModule used as primary technology for a job
 */
class PrimaryJobModule : public TechModule
{
    friend class JobDesign;

private:
    const string& tag;
    unordered_map<Resources, float> production;
    unordered_map<Resources, float> upkeep;

public:
    PrimaryJobModule(const string &name, const string& tag);
    TechModule *upgrade() const;

    /**
     * Defines the production of a resource
     */
    void addProduction(Resources res, float amount);
    /**
     * Defines the upkeep of a resource
     */
    void addUpkeep(Resources res, float amount);
};

/**
 * TechModule used as auxiliary technology for a job. It's defined as a series of modifiers that will be applied to all associated jobslots
 */
class AuxiliaryJobModule : public TechModule
{
    friend class JobDesign;

private:
    vector<const Modifier*> modifiers;

public:
    AuxiliaryJobModule(const string &name);
    ~AuxiliaryJobModule();
    void addModifier(const Modifier* modifier);
    TechModule *upgrade() const;
};