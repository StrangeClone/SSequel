#pragma once

#include "../basic/context.h"
#include "../basic/resources.h"
#include "../jobs/popgroup.h"
#include "district.h"

/**
 * Represents a planet that can have a standard colony
 */
class Planet : public Context
{
private:
    unordered_map<Resources, float> resourcesStored;
    unordered_map<const JobDesign*, long> jobs;

    vector<District*> districts;

public:
    Planet(const string& name);

    void addResources(Resources res, float amount);
    void removeReources(Resources res, float amount);
    void addPops(JobDesign* job, long amount);
    void addDistrict(const DistrictDesign* district);
    void update();
};

/**
 * Property: max number of districts on a planet
 */
const string maxDistrictsProperty("maxd");
/**
 * Property: max storage of a resource on a planet
 */
const string* storageProperty(Resources res);
/**
 * Property: housing on a planet
 */
const string housingProperty("hsng");