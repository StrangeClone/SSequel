#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

class Context
{

    friend Modifier;

private:
    ContextType type;
    const string &tag;
    Context *parent;
    vector<Context *> children;
    vector<const Modifier *> appliedModifiers;
    unordered_map<const string &, float, std::hash<string>> propertiesBaseValue;
    unordered_map<const string &, float, std::hash<string>> propertiesFlatModifiers;
    unordered_map<const string &, float, std::hash<string>> propertiesPercentageModifiers;

public:
    Context(ContextType type, const string &tag);
    virtual void update();
    float property(const string &property) const;
};

class Modifier
{
private:
    float value;
    bool flat;
    const string &propertyName;
    const ContextType level;

public:
    Modifier(const string &propertyName, float value, bool flat, const ContextType level);
    void apply(Context &context) const;
    void remove(Context &context) const;
};

enum ContextType
{
    empire = 0,
    system,
    celestial_body,
    district,
    job
};