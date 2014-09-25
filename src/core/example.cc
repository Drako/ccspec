#include <functional>
#include <list>
#include <ccspec/core/example.h>
#include <ccspec/core/example_group.h>
#include <ccspec/core/hooks.h>

namespace ccspec {
namespace core {

using std::function;
using std::list;
using std::string;

// Public methods.

// This function enables chaining of around hooks. Callers call this function
// inside each around hook (lambda function), then this function calls the next
// around hook in the chain.
//
// Since this function is nullary, in order to remember the state of which
// around hook to execute next, the around hooks need to be stored in a member
// variable `around_hooks_`. This also implies that `around_hooks_` must be
// mutated in this function in order to transition to the next state.
void Example::run() const {
    if (around_hooks_.empty()) {
        for (auto hook : *before_each_hooks_)
            hook();
        spec_();
        for (auto hook : *after_each_hooks_)
            hook();
    } else {
        AroundHook around_hook = around_hooks_.front();
        around_hooks_.pop_front();
        around_hook(*this);
    }
}

void Example::run(const list<BeforeHook>* before_each_hooks,
                  const list<AfterHook>* after_each_hooks,
                  list<AroundHook> around_hooks) const {
    before_each_hooks_ = before_each_hooks;
    after_each_hooks_ = after_each_hooks;
    around_hooks_ = around_hooks;
    run();
}

// Private methods.

Example::Example(string desc, std::function<void ()> spec)
    : desc_(desc), spec_(spec) {}

// Friend methods.

Example it(string desc, function<void ()> spec) {
    Example example = Example(desc, spec);
    ExampleGroup* parent_group = groups_being_defined.top();
    parent_group->addExample(example);
    return example;
}

Example example(string desc, function<void ()> spec) {
    return it(desc, spec);
}

Example specify(string desc, function<void ()> spec) {
    return it(desc, spec);
}

} // namespace core
} // namespace ccspec