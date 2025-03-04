#pragma once

#include "../basic/context.h"
#include "job_techmodule.h"

#include <set>

using std::set;

class PopGroup;

/**
 * Contains the Technologies used for a job
 */
class JobDesign {
private:
    const string* tag;
    const PrimaryJobModule* primary;
    set<const AuxiliaryJobModule*> auxiliaries;
    set<PopGroup*> associatedSlots;

public:
    /**
     * Constructs a JobDesign
     * 
     * @param primary   the primary technology used
     * @param n         the number of auxiliary technologies used (max 3)
     * @param ...       the auxiliary technogies used
     */
    JobDesign(const PrimaryJobModule* primary, int auxiliaries=0, ...);
    void setPrimary(const PrimaryJobModule* pr);
    void addAuxiliary(const AuxiliaryJobModule* aux);
    void removeAuxiliary(const AuxiliaryJobModule* aux);
    const string& getTag() const;

    /**
     * Applies the Design to the passed group
     */
    void apply(PopGroup* slot);
    /**
     * Re-applies the Design to all the associated groups (useful after an upgrade)
     */
    void upgradeAllSlots();
};

/**
 * A Context that represents all the pops on a planet associated to a specific job design
 * 
 * Here, the tag represent the class of job: miners, farmers, technicians, and so on
 */
class PopGroup : public Context
{
private:
    long n;
    const JobDesign* design;

public:
    PopGroup(const string &tag, JobDesign* desing, long amount);
    /**
     * Produces and consumes the resources for the job
     */
    void update();
    /**
     * Resets all properties to 0 and removes all the modifiers. Used if there's a change of design
     */
    void resetProperties();
    const JobDesign* getJob() const;
    void increaseAmount(long amount);
};

/**
 * Returns the group job production property for the given resource
 */
const string* productionProperty(Resources res);
/**
 * Returns the group job upkeep property for the given resource
 */
const string* upkeepProperty(Resources res);