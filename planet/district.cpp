#include "district.h"

#include <stdarg.h>

District::District(const DistrictDesign* design) : design(design) {}

long District::getUpkeep() const {
    return design->getUpkeep();
}

DistrictDesign::DistrictDesign(const DistrictPrimaryModule *primary, const DistrictHousingModule *housing, int aux, ...) : primary(primary), housing(housing)
{
    if (aux > 5)
    {
        aux = 5;
    }
    va_list arguments;
    va_start(arguments, aux);
    for (int i = 0; i < aux; i++)
    {
        addAuxiliary(va_arg(arguments, DistrictAuxiliaryModule *));
    }
}

void DistrictDesign::setPrimary(const DistrictPrimaryModule *pr) {
    primary = pr;
}

void DistrictDesign::setHousing(const DistrictHousingModule *hs) {
    housing = hs;
}

void DistrictDesign::addAuxiliary(const DistrictAuxiliaryModule *aux) {
    auxiliaries.insert(aux);
}

void DistrictDesign::removeAuxiliary(const DistrictAuxiliaryModule *aux) {
    auxiliaries.erase(auxiliaries.find(aux));
}

std::unordered_map<const JobDesign*, long>* DistrictDesign::availableJobs() const {
    std::unordered_map<const JobDesign*, long>* result = new std::unordered_map<const JobDesign*, long>();
    for (const auto& entry : primary->availableJobs) {
        result->operator[](entry.first) += entry.second;
    }
    for (const DistrictAuxiliaryModule* aux : auxiliaries) {
        for (const auto& entry : aux->extraJobs) {
            result->operator[](entry.first) += entry.second;
        }
    }
    return result;
}

long DistrictDesign::getHousing() const {
    return housing->number;
}

long DistrictDesign::getUpkeep() const {
    return primary->upkeep + housing->upkeep;
}