#pragma once

#include "district_techmodule.h"

#include <string>

using std::string;

class DistrictDesign
{
private:
    const string* tag;
    const DistrictPrimaryModule *primary;
    const DistrictHousingModule *housing;
    set<const DistrictAuxiliaryModule *> auxiliaries;

public:
    /**
     * Constructs a DistrictDesign
     *
     * @param primary   the primary technology used
     * @param housing   the housing technology used
     * @param n         the number of auxiliary technologies used (max 5)
     * @param ...       the auxiliary technogies used
     */
    DistrictDesign(const DistrictPrimaryModule *primary, const DistrictHousingModule *housing, int auxiliaries = 0, ...);
    void setPrimary(const DistrictPrimaryModule *pr);
    void setHousing(const DistrictHousingModule *hs);
    void addAuxiliary(const DistrictAuxiliaryModule* aux);
    void removeAuxiliary(const DistrictAuxiliaryModule *aux);

    /**
     * allocates and creates a map containing the jobs and their quantities. Should be deleted after use.
     */
    std::unordered_map<const JobDesign*, long>* availableJobs() const;
    long getHousing() const;
    long getUpkeep() const;
};

class District
{
private:
    const DistrictDesign *design;

public:
    District(const DistrictDesign *design);
    long getUpkeep() const;
};