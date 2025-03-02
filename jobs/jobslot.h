#pragma once

#include "../basic/context.h"
#include "job_techmodule.h"

#include <set>

using std::set;

class JobSlot : public Context
{
private:
    int n;

public:
    JobSlot(const string &tag);
    void update();
    void resetProperties();
};

class JobDesign {
private:
    const string& tag;
    const PrimaryJobModule* primary;
    vector<const AuxiliaryJobModule*> auxiliaries;
    set<JobSlot*> associatedSlots;

public:
    JobDesign(PrimaryJobModule* primary, int auxiliaries=0, ...);
    void addAuxiliary(const AuxiliaryJobModule* aux);
    void removeAuxiliary(const AuxiliaryJobModule* aux);

    void apply(JobSlot* slot);
    void upgradeAllSlots();
};

const string* productionProperty(Resources res);
const string* upkeepProperty(Resources res);