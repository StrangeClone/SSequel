#pragma once

enum Resources {
    energy = 0,
    minerals,
    food,
    alloy = 10,
    goods,
    crystals = 20,
    gases,
    motes,
    unity = 40,
    research,
    trade
};

bool basic(Resources res);
bool advanced(Resources res);
bool strategic(Resources res);
bool abstract(Resources res);