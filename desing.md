# Desing

## Package 1 - Basic

This package contains basic classes and enums for the whole application.

```mermaid
classDiagram
    class ContextType {
        <<enum>>
        + empire
        + system
        + stellar body
        + district
        + job
    }

    class Resources {
        <<enum>>
        + energy = 0
        + minerals
        + food
        + alloys = 10
        + consumer goods
        + crystals = 20
        + gases
        + motes
        + unity = 40
        + research
        + trade
    }
```
The ContextType enum defines the types that the abstract class Context can have.

The Resources enum defines the types of resources that exist. The resources between 0 and 9 will be considered basic, the resources between 10 and 19 will be considered advanced, the resources between 20 and 39 will be considered strategic, the resources between 40 and 49 will be considered abstract.

```mermaid
classDiagram
    class Context {
        <<abstract>>
        - ContextType type
        - string& tag
        - Context& parent
        - vector~Context&~ children
        - map~string&, float~ propertiesBaseValues
        - map~string&, float~ propertiesFlatModifiers
        - map~string&, float~ propertiesPercentageModifiers
        + Context(ContexType type, string* tag)
        + abstract update()
        + property(string&) float
    }
    class Modifier {
        - float value
        - boolean flat
        - string& propertyName
        - ContextType level
        + apply(Context&)
        + remove(Context&)
    }
    Modifier --> "*" Context : appliedModifiers
    class TechModule {
        <<abstract>>

    }
```

The Context class is an abstract class that represent a generic element in the game (as suggested by the ContextType enum). Contexts are organized hierarchycally, in a tree, whit Empires on top, then the Systems of an Empire, the stellar bodies in them (planets, stars, asteroids, space structures...), the districts on planets and jobs in districts. Contexts have a map of properties (name, value) that represents the a generic value of the context, and also their flat and percentage modifiers. The total value of a property is calculated as:
> total = (base value + flat modifiers) * percentage modifiers

When a modifier is applied to a context, first the context's type is evaluated: if it's superior or inferior to the "level" of the modifier, the modifier is applied to all the children or to the parent (respectively) of the context, until it reaches the correct level. Then, the modifier will be added to the "appliedModifiers" array, and its value will be added to the "flat modifiers" of the property associated to the modifier (its propertyName string), if the flat attribute is true, else it will be added to the "percentage modifiers".

When a modifier is removed, it will be removed by the appliedModifiers array and its effects will be removed from the maps.