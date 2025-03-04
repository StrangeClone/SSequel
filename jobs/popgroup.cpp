#include "popgroup.h"
#include "../planet/planet.h"

#include <stdarg.h>
#include <algorithm>

PopGroup::PopGroup(const string& tag, JobDesign* design, long amount) : Context(ContextType::pop_group, tag), design(design), n(amount) {
    design->apply(this);
}

void PopGroup::update() {
    Planet* planet = dynamic_cast<Planet*>(getParent());
    if (planet != NULL) {
        for (const auto& property : propertiesBaseValue) {
            const string* name = property.first;
            int res = std::stoi(property.first->substr(3));
            if (name->find("prd") == 0) {
                planet->addResources((Resources)res, property.second * n);
            }
            if (name->find("upk") == 0) {
                planet->removeReources((Resources)res, property.second * n);
            }
        }
    }
}

void PopGroup::resetProperties() {
    propertiesBaseValue.clear();
    propertiesFlatModifiers.clear();
    propertiesPercentageModifiers.clear();
    appliedModifiers.clear();
}

const JobDesign* PopGroup::getJob() const {
    return design;
}

void PopGroup::increaseAmount(long amount) {
    n += amount;
}

JobDesign::JobDesign(const PrimaryJobModule *primary, int aux, ...) : tag(primary->tag), primary(primary)
{
    if (aux > 3)
    {
        aux = 3;
    }
    va_list arguments;
    va_start(arguments, aux);
    for (int i = 0; i < aux; i++) {
        addAuxiliary(va_arg(arguments, AuxiliaryJobModule*));
    }
}

void JobDesign::setPrimary(const PrimaryJobModule* pr) {
    primary = pr;
}

void JobDesign::addAuxiliary(const AuxiliaryJobModule* aux) {
    if (auxiliaries.size() < 3) {
        auxiliaries.insert(aux);
    }
}

void JobDesign::removeAuxiliary(const AuxiliaryJobModule* aux) {
    auxiliaries.erase(std::find(auxiliaries.begin(), auxiliaries.end(), aux));
}

const string& JobDesign::getTag() const {
    return *tag;
}

void JobDesign::apply(PopGroup* slot) {
    slot->resetProperties();
    for (const auto& entry : primary->production) {
        slot->setPropertyBaseValue(productionProperty(entry.first), entry.second);
    }
    for (const auto& entry : primary->upkeep) {
        slot->setPropertyBaseValue(upkeepProperty(entry.first), entry.second);
    }
    for (const AuxiliaryJobModule* aux : auxiliaries) {
        for (const Modifier* mod : aux->modifiers) {
            mod->apply(*slot);
        }
    }
    associatedSlots.insert(slot);
}

void JobDesign::upgradeAllSlots() {
    for(PopGroup* slot : associatedSlots) {
        apply(slot);
    }
}

const string* productionProperty(Resources res) {
    static unordered_map<Resources, const string*> propertyNames;
    if (propertyNames.find(res) != propertyNames.end()) {
        return propertyNames[res];
    } else {
        propertyNames.insert({res, new string("prd" + std::to_string(res))});
        return propertyNames[res];
    }
}

const string* upkeepProperty(Resources res) {
    static unordered_map<Resources, const string*> propertyNames;
    if (propertyNames.find(res) != propertyNames.end()) {
        return propertyNames[res];
    } else {
        propertyNames.insert({res, new string("upk" + std::to_string(res))});
        return propertyNames[res];
    }
}