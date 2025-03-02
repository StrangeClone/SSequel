#include "job_techmodule.h"
#include "../basic/random.h"

PrimaryJobModule::PrimaryJobModule(const string& name, const string& tag) : TechModule(name), tag(tag)
{}

void PrimaryJobModule::addProduction(Resources res, float amount) {
    production[res] = amount;
}

void PrimaryJobModule::addUpkeep(Resources res, float amount) {
    upkeep[res] = amount;
}

TechModule* PrimaryJobModule::upgrade() const {
    PrimaryJobModule* updated = new PrimaryJobModule(name, tag);
    for (TechLabel label : labels) {
        updated->addLabel(label);
    }
    for (const auto& entry : production) {
        updated->addProduction(entry.first, entry.second + uniform(1, 4));
    }
    for (const auto& entry : upkeep) {
        updated->addUpkeep(entry.first, entry.second + uniform(2));
    }
    return updated;
}


AuxiliaryJobModule::AuxiliaryJobModule(const string& name) : TechModule(name) {}

AuxiliaryJobModule::~AuxiliaryJobModule() {
    for (const Modifier* mod : modifiers) {
        delete mod;
    }
}

void AuxiliaryJobModule::addModifier(const Modifier* mod) {
    modifiers.push_back(mod);
}

TechModule* AuxiliaryJobModule::upgrade() const {
    AuxiliaryJobModule* updated = new AuxiliaryJobModule(name);
    for (TechLabel label : labels) {
        updated->addLabel(label);
    }
    for (const Modifier* modifier : modifiers) {
        updated->addModifier(modifier->upgrade());
    }
    return updated;
}