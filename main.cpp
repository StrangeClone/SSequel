#include "basic/context.h"
#include "jobs/jobslot.h"
#include "basic/context_conditions.h"

#include <iostream>

int main() {
    PrimaryJobModule* primary = new PrimaryJobModule("mining laser-drills", "miner");
    primary->addProduction(minerals, 5);
    primary->addUpkeep(energy, 0.5f);
    
    AuxiliaryJobModule* aux1 = new AuxiliaryJobModule("short-range geo-scans");
    Modifier* aux1modifier = new Modifier(productionProperty(minerals), 0.15, false, job, checkTag("miner"));
    aux1->addModifier(aux1modifier);
    
    AuxiliaryJobModule* aux2 = new AuxiliaryJobModule("support mining drones");
    Modifier* aux2modifier = new Modifier(productionProperty(minerals), 0.20, false, job, checkTag("miner"));
    aux2->addModifier(aux2modifier);
    Modifier* aux2modifier2 = new Modifier(upkeepProperty(energy), 0.15, false, job, checkTag("miner"));
    aux2->addModifier(aux2modifier2);

    JobDesign* desing = new JobDesign(primary, 1, aux1);
    desing->addAuxiliary(aux2);
    desing->removeAuxiliary(aux1);
    desing->addAuxiliary(aux1);

    JobSlot* slot = new JobSlot("miner");
    desing->apply(slot);

    std::cout << "Production in minerals: " << slot->property(productionProperty(minerals)) << "; ";
    std::cout << "Upkeep in energy: " << slot->property(upkeepProperty(energy)) << std::endl;

    desing->setPrimary((PrimaryJobModule*)primary->upgrade());
    desing->upgradeAllSlots();

    std::cout << "Production in minerals: " << slot->property(productionProperty(minerals)) << "; ";
    std::cout << "Upkeep in energy: " << slot->property(upkeepProperty(energy)) << std::endl;
}