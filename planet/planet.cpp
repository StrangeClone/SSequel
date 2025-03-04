#include "planet.h"

#include <algorithm>

Planet::Planet(const string& name) : Context(ContextType::celestial_body, name) {
    setPropertyBaseValue(&maxDistrictsProperty, 20);
    setPropertyBaseValue(storageProperty(minerals), 2e+9);
    setPropertyBaseValue(storageProperty(food), 2e+9);
    setPropertyBaseValue(storageProperty(energy), 2e+9);
}

void Planet::addResources(Resources res, float amount) {
    resourcesStored[res] = std::min(resourcesStored[res] + amount, property(storageProperty(res)));
}

void Planet::removeReources(Resources res, float amount) {
    resourcesStored[res] = std::max(resourcesStored[res] - amount, 0.f);
}

void Planet::addDistrict(const DistrictDesign* design) {
    if (property(&maxDistrictsProperty) > districts.size() + 1) {
        districts.push_back(new District(design));
        unordered_map<const JobDesign*, long>* designJobs = design->availableJobs();
        for (const auto& entry : *designJobs) {
            jobs[entry.first] += entry.second;
        }
        delete designJobs;
    }
}

void Planet::addPops(JobDesign* job, long amount) {
    bool present = false;
    for (Context* child : getChildren()) {
        PopGroup* group = dynamic_cast<PopGroup*>(child);
        if (group != NULL && group->getJob() == job) {
            present = true;
            group->increaseAmount(amount);
            break;
        }
    }
    if (!present) {
        addChild(new PopGroup(job->getTag(), job, amount));
    }
}

void Planet::update() {
    Context::update();
    for (District* district : districts) {
        removeReources(energy, district->getUpkeep());
    }
}

const string* storageProperty(Resources res) {
    static unordered_map<Resources, const string*> propertyNames;
    if (propertyNames.find(res) != propertyNames.end()) {
        return propertyNames[res];
    } else {
        propertyNames.insert({res, new string("str" + std::to_string(res))});
        return propertyNames[res];
    }
}