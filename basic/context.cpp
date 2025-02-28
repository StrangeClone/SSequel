#include <context.h>

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

float Context::property(const string &property) const
{
    return (propertiesBaseValue.at(property) + propertiesFlatModifiers.at(property)) * propertiesPercentageModifiers.at(property);
}

Modifier::Modifier(const string &propertyName, float value, bool flat, const ContextType level) : propertyName(propertyName),
                                                                                                  value(value),
                                                                                                  flat(flat),
                                                                                                  level(level)
{
}

void Modifier::apply(Context &c) const
{
    if (c.type == level && std::find(c.appliedModifiers.begin(), c.appliedModifiers.end(), this) == c.appliedModifiers.end())
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