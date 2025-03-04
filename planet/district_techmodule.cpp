#include "district_techmodule.h"
#include "../basic/random.h"

DistrictPrimaryModule::DistrictPrimaryModule(const string& name, const string& tag, long upkeep) : TechModule(name), upkeep(upkeep), tag(&tag) {}

void DistrictPrimaryModule::addJob(const JobDesign* job, long n) {
    availableJobs[job] = n;
}

TechModule* DistrictPrimaryModule::upgrade() const {
    DistrictPrimaryModule* upgraded = new DistrictPrimaryModule(name, *tag, upkeep + integerUniform(5, 20) * 1e7);
    upgraded->copyLabels(this);
    for (const auto& entry : availableJobs) {
        upgraded->addJob(entry.first, entry.second + integerUniform(10, 25) * 1e7);
    }
    return upgraded;
}

DistrictHousingModule::DistrictHousingModule(const string& name, long number, long upkeep) : TechModule(name), number(number), upkeep(upkeep) {}

TechModule* DistrictHousingModule::upgrade() const {
    DistrictHousingModule* upgraded = new DistrictHousingModule(name, number + integerUniform(10, 17) * 1e7, upkeep + integerUniform(5, 20) * 1e7);
    upgraded->copyLabels(this);
    return upgraded;
}

DistrictAuxiliaryModule::DistrictAuxiliaryModule(const string& name) : TechModule(name) {}

void DistrictAuxiliaryModule::addModifier(const Modifier* mod) {
    modifiers.insert(mod);
}

void DistrictAuxiliaryModule::addJob(const JobDesign* job, long n) {
    extraJobs[job] = n;
}

TechModule* DistrictAuxiliaryModule::upgrade() const {
    DistrictAuxiliaryModule* upgraded = new DistrictAuxiliaryModule(name);
    upgraded->copyLabels(this);
    for (const auto& entry : extraJobs) {
        upgraded->addJob(entry.first, entry.second + integerUniform(25, 60) * 1000000);
    }
    for (const Modifier* modifier : modifiers) {
        upgraded->addModifier(modifier->upgrade());
    }
    return upgraded;
}
