#pragma once

#include "../basic/techmodule.h"
#include "../jobs/popgroup.h"

/**
 * Primary TechModule of a district, defining the base jobs available
 */
class DistrictPrimaryModule : public TechModule
{
    friend class DistrictDesign;

private:
    const string* tag;
    unordered_map<const JobDesign *, long> availableJobs;
    long upkeep;

public:
    DistrictPrimaryModule(const string &name, const string& tag, long upkeep);
    void addJob(const JobDesign *job, long n);
    TechModule *upgrade() const;
};

/**
 * TechModule of a district, defining housing
 */
class DistrictHousingModule : public TechModule
{
    friend class DistrictDesign;

private:
    long number;
    long upkeep;

public:
    DistrictHousingModule(const string &name, long housing, long upkeep);
    TechModule *upgrade() const;
};

/**
 * Auxiliary TechModule of a district, defining various bonuses, as well as some extra jobs
 */
class DistrictAuxiliaryModule : public TechModule
{
    friend class DistrictDesign;

private:
    set<const Modifier *> modifiers;
    unordered_map<const JobDesign *, long> extraJobs;

public:
    DistrictAuxiliaryModule(const string &name);
    void addModifier(const Modifier *modifier);
    void addJob(const JobDesign *job, long n);
    TechModule *upgrade() const;
};