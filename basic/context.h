#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

/**
 * Defines the types of context and also their hierarchy: the smaller values are at the top
 */
enum ContextType
{
    empire = 0,
    stellar_system,
    celestial_body,
    job
};

class Context;

/**
 * Checks if a Context respects a specific condition
 */
class ContextCondition
{
public:
    /**
     * Returns if the Context respects the condition
     */
    virtual bool check(const Context &c) const = 0;
    virtual ~ContextCondition() {}
};

/**
 * Applies a change to a property of a Context
 */
class Modifier
{
private:
    float value;
    bool flat;
    const string *propertyName;
    const ContextType level;
    const ContextCondition *condition;

public:
    /**
     * Constructs a Modifier
     * @param propertyName  the name of the property to modify
     * @param value         the value change applied to property
     * @param flat          if true, the value will be added; if false, multiplied
     * @param level         the level of the target Context: if the modifier is applied to a Context of incorrect level, the Modifier will be applied
     * to all the children or to the parent of such Context that have the correct level.
     * @param condition     a condition on the Context, can be NULL (no conditions checked)
     */
    Modifier(const string *propertyName, float value, bool flat, ContextType level, const ContextCondition *condition);
    /**
     * Applies the modifier to the given Context. Each modifier can be applied only once to a specific Context
     */
    void apply(Context &context) const;
    /**
     * Removes the modifier from the given Context, if it's applied
     */
    void remove(Context &context) const;
    /**
     * Returns an upgraded version of the Modifier
     */
    Modifier *upgrade() const;
};

/**
 * Represents a basic element of the game: a jobslot, a celestial body (planet, star, space structures, ...) et cetera.
 */
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
    /**
     * Updates the Context, called every month
     */
    virtual void update();

    const string& getTag() const;
    /**
     * Returns the value of such property. Warning: it will create a slot fot the property if it does not exist, with value 0, and than return it,
     * creating, de facto, a new property with value 0
     */
    float property(const string *property);
    /**
     * Sets the base value of a property. It will create a new property if it does not exist.
     */
    void setPropertyBaseValue(const string *property, float value);
};