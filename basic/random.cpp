#include "random.h"

float uniform() {
    return (float) rand() / (float)RAND_MAX;
}

float uniform(float top) {
    return uniform() * top;
}

float uniform(float bottom, float top) {
    if (bottom > top) {
        return bottom;
    } else {
        return bottom + uniform() * (top - bottom);
    }
}