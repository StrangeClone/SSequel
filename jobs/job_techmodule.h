#pragma once

#include "../basic/techmodule.h"
#include "../basic/resources.h"
#include "../basic/context.h"

#include <unordered_map>

using std::unordered_map;

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

    void addProduction(Resources res, float amount);
    void addUpkeep(Resources res, float amount);
};

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