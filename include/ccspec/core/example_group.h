#ifndef CCSPEC_CORE_EXAMPLE_GROUP_H_
#define CCSPEC_CORE_EXAMPLE_GROUP_H_

#include <functional>
#include <list>
#include <stack>
#include <string>
#include "example.h"

namespace ccspec {
namespace core {

class ExampleGroup;

typedef ExampleGroup* Creator(std::string desc, std::function<void ()> spec);

extern std::stack<ExampleGroup*> groups_being_defined;

class ExampleGroup {
  public:
    virtual ~ExampleGroup();

    void addExample(Example&);

  private:
    ExampleGroup(std::string desc);

    void addChild(ExampleGroup*);

    std::string desc_;
    std::list<ExampleGroup*> children_;
    std::list<Example> examples_;

    friend Creator describe;
    friend Creator context;
};

Creator describe;
Creator context;

} // namespace core
} // namespace ccspec

#endif // CCSPEC_CORE_EXAMPLE_GROUP_H_
