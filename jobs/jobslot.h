#pragma once

#include "../basic/context.h"
#include "job_techmodule.h"

#include <set>

using std::set;

/**
 * A Context that represents all the jobs on a planet associated to a specific popgroup
 * 
 * Here, the tag represent the class of job: miners, farmers, technicians, and so on
 */
class JobSlot : public Context
{
private:
    int n;

public:
    JobSlot(const string &tag);
    /**
     * Produces and consumes the resources for the job
     */
    void update();
    /**
     * Resets all properties to 0 and removes all the modifiers. Used if there's a change of design
     */
    void resetProperties();
};

/**
 * Contains the Technologies used for a jobslot
 */
class JobDesign {
private:
    const string& tag;
    const PrimaryJobModule* primary;
    vector<const AuxiliaryJobModule*> auxiliaries;
    set<JobSlot*> associatedSlots;

public:
    /**
     * Constructs a JobDesign
     * 
     * @param primary   the primary technology used
     * @param n         the number of auxiliary technologies used (max 3)
     * @param ...       the auxiliary technogies used
     */
    JobDesign(PrimaryJobModule* primary, int auxiliaries=0, ...);
    void setPrimary(const PrimaryJobModule* pr);
    void addAuxiliary(const AuxiliaryJobModule* aux);
    void removeAuxiliary(const AuxiliaryJobModule* aux);

    /**
     * Applies the Design to the passed slot
     */
    void apply(JobSlot* slot);
    /**
     * Re-applies the Design to all the associated slots (useful after an upgrade)
     */
    void upgradeAllSlots();
};

/**
 * Returns the job production property for the given resource
 */
const string* productionProperty(Resources res);
/**
 * Returns the job upkeep property for the given resource
 */
const string* upkeepProperty(Resources res);