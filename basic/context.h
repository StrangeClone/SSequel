#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

enum ContextType
{
    empire = 0,
    stellar_system,
    celestial_body,
    job
};

class Context;

class ContextCondition
{
public:
    virtual bool check(const Context &c) const = 0;
    virtual ~ContextCondition() {}
};

class Modifier
{
private:
    float value;
    bool flat;
    const string *propertyName;
    const ContextType level;
    const ContextCondition *condition;

public:
    Modifier(const string *propertyName, float value, bool flat, ContextType level, const ContextCondition *condition);
    void apply(Context &context) const;
    void remove(Context &context) const;
    Modifier *upgrade() const;
};

class Context
{

    friend class Modifier;

private:
    ContextType type;
    const string &tag;
    Context *parent;
    vector<Context *> children;

protected:
    vector<const Modifier *> appliedModifiers;
    unordered_map<const string *, float, std::hash<const string *>> propertiesBaseValue;
    unordered_map<const string *, float, std::hash<const string *>> propertiesFlatModifiers;
    unordered_map<const string *, float, std::hash<const string *>> propertiesPercentageModifiers;

public:
    Context(ContextType type, const string &tag);
    virtual void update();

    const string& getTag() const;
    float property(const string *property);
    void setPropertyBaseValue(const string *property, float value);
};