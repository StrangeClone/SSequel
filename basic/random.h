#pragma once

#include <bits/stdc++.h>

/**
 * Returns a random float between 0 and 1
 */
float uniform();
/**
 * Returns a random float between 0 and top
 */
float uniform(float top);
/**
 * Returns a random float between bottom and top, or bottom if top is smaller than bottom
 */
float uniform(float bottom, float top);