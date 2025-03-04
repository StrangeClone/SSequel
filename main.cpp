#include "basic/context.h"
#include "jobs/popgroup.h"
#include "basic/context_conditions.h"
#include "planet/planet.h"

#include <iostream>

int main() {
    string jobTag("miner");
    string districtTag("mining");

    PrimaryJobModule* minerPrimary = new PrimaryJobModule("mining laser-drills", jobTag);
    minerPrimary->addProduction(minerals, 5);
    minerPrimary->addUpkeep(energy, 0.5f);
    
    AuxiliaryJobModule* minerAuxiliary1 = new AuxiliaryJobModule("short-range geo-scans");
    minerAuxiliary1->addModifier(new Modifier(productionProperty(minerals), 0.15, false, pop_group, checkTag(jobTag)));
    
    AuxiliaryJobModule* minerAuxiliary2 = new AuxiliaryJobModule("support mining drones");
    minerAuxiliary2->addModifier(new Modifier(productionProperty(minerals), 0.20, false, pop_group, checkTag(jobTag)));
    minerAuxiliary2->addModifier(new Modifier(upkeepProperty(energy), 0.15, false, pop_group, checkTag(jobTag)));

    JobDesign* minerDesing = new JobDesign(minerPrimary, 2, minerAuxiliary1, minerAuxiliary2);

    PrimaryJobModule* researcherPrimary = new PrimaryJobModule("quantum theory", "researcher");
    researcherPrimary->addProduction(research, 3);
    JobDesign* researcherDesign = new JobDesign(researcherPrimary);
    
    DistrictPrimaryModule* miningPrimary = new DistrictPrimaryModule("strategic strip mining", districtTag, 1e+7);
    miningPrimary->addJob(minerDesing, 500e+6);

    DistrictHousingModule* housing = new DistrictHousingModule("meta-concrete complexes", 400e+6, 1e+7);

    DistrictAuxiliaryModule* miningAuxiliary1 = new DistrictAuxiliaryModule("laboratories for geological research");
    miningAuxiliary1->addJob(researcherDesign, 25e+6);

    DistrictDesign* miningDesing = new DistrictDesign(miningPrimary, housing, 1, miningAuxiliary1);

    Planet* planet = new Planet("Ukoob");
    planet->addDistrict(miningDesing);
    planet->addDistrict(miningDesing);
    planet->addResources(energy, 1e10);
    planet->addPops(minerDesing, 1e9);
    planet->addPops(researcherDesign, 1e7);
    planet->update();
}