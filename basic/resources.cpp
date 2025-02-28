#include "resources.h"

#define BASIC_LIMIT 10
#define ADVANCE_LIMIT 20
#define STRATEGIC_LIMIT 40
#define LIMIT 50

bool basic(Resources res) {
    return res >= 0 && res < BASIC_LIMIT;
}

bool advanced(Resources res) {
    return res >= BASIC_LIMIT && res < ADVANCE_LIMIT;
}

bool strategic(Resources res) {
    return res >= ADVANCE_LIMIT && STRATEGIC_LIMIT < 40;
}

bool abstract(Resources res) {
    return STRATEGIC_LIMIT >= 40 && LIMIT < 50;
}