#include "jobslot.h"

#include <stdarg.h>
#include <algorithm>

JobSlot::JobSlot(const string& tag) : Context(ContextType::job, tag) {}

void JobSlot::update() {
    //TODO: add/remove resources from the planet's storage
}

void JobSlot::resetProperties() {
    propertiesBaseValue.clear();
    propertiesFlatModifiers.clear();
    propertiesPercentageModifiers.clear();
    appliedModifiers.clear();
}

JobDesign::JobDesign(PrimaryJobModule *primary, int aux, ...) : tag(primary->tag), primary(primary)
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

void JobDesign::addAuxiliary(const AuxiliaryJobModule* aux) {
    if (auxiliaries.size() < 3) {
        auxiliaries.push_back(aux);
    }
}

void JobDesign::removeAuxiliary(const AuxiliaryJobModule* aux) {
    auxiliaries.erase(std::find(auxiliaries.begin(), auxiliaries.end(), aux));
}

void JobDesign::apply(JobSlot* slot) {
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
    for(JobSlot* slot : associatedSlots) {
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