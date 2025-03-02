#include "context_conditions.h"

class TagCondition : public ContextCondition {
    private:
        string tag;
    
    public:
        TagCondition(const string& tag) : tag(tag) {}
        bool check(const Context& context) const  {
            return context.getTag() == tag;
        }
};

ContextCondition* checkTag(const string& tag) {
    static unordered_map<string, TagCondition*> tagConditions;
    if (tagConditions.find(tag) != tagConditions.end()) {
        return tagConditions[tag];
    } else {
        tagConditions[tag] = new TagCondition(tag);
        return tagConditions[tag];
    }
}