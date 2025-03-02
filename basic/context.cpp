#include "context.h"
#include "random.h"

#include <algorithm>

Context::Context(ContextType type, const string &tag) : type(type),
                                                        tag(tag)
{
}

void Context::update()
{
    for (Context *child : children)
    {
        child->update();
    }
}

const string& Context::getTag() const {
    return tag;
}

float Context::property(const string *property)
{
    return (propertiesBaseValue[property] + propertiesFlatModifiers[property]) * (1 + propertiesPercentageModifiers[property]);
}

void Context::setPropertyBaseValue(const string *property, float value)
{
    propertiesBaseValue[property] = value;
}

Modifier::Modifier(const string *propertyName, float value, bool flat, ContextType level, const ContextCondition *condition) : propertyName(propertyName),
                                                                                                                               value(value),
                                                                                                                               flat(flat),
                                                                                                                               level(level),
                                                                                                                               condition(condition)
{
}

void Modifier::apply(Context &c) const
{
    if (c.type == level &&
        (condition == NULL || condition->check(c)) &&
        std::find(c.appliedModifiers.begin(), c.appliedModifiers.end(), this) == c.appliedModifiers.end())
    {
        if (flat)
        {
            c.propertiesFlatModifiers[propertyName] += value;
        }
        else
        {
            c.propertiesPercentageModifiers[propertyName] += value;
        }
        c.appliedModifiers.push_back(this);
    }
    else if (c.type < level)
    {
        for (Context *child : c.children)
        {
            apply(*child);
        }
    }
    else if (c.parent != NULL)
    {
        apply(*c.parent);
    }
}

void Modifier::remove(Context &c) const
{
    std::vector<const Modifier *>::iterator position = std::find(c.appliedModifiers.begin(), c.appliedModifiers.end(), this);
    if (c.type == level && position != c.appliedModifiers.end())
    {
        if (flat)
        {
            c.propertiesFlatModifiers[propertyName] -= value;
        }
        else
        {
            c.propertiesPercentageModifiers[propertyName] -= value;
        }
        c.appliedModifiers.erase(position);
    }
    if (c.type < level)
    {
        for (Context *child : c.children)
        {
            remove(*child);
        }
    }
    else if (c.parent != NULL)
    {
        remove(*c.parent);
    }
}

Modifier *Modifier::upgrade() const
{
    if (flat)
    {
        return new Modifier(propertyName, value + uniform(2), flat, level, condition);
    }
    else
    {
        return new Modifier(propertyName, value + uniform(0.2), flat, level, condition);
    }
}