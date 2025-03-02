#pragma once

#include "context.h"

/**
 * Returns a Condition tha checks if a Context has the tag passed as parameter
 */
ContextCondition* checkTag(const string& tag);