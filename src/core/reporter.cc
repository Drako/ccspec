#include <exception>
#include <vector>
#include <ccspec/core/execution_result.h>
#include <ccspec/core/formatter.h>
#include <ccspec/core/reporter.h>

namespace ccspec {
namespace core {

using std::exception;
using std::vector;

Reporter::Reporter(const Formatter* formatter) : formatters_{formatter} {}

Reporter::Reporter(const vector<const Formatter*> formatters)
    : formatters_(formatters) {}

void Reporter::examplePassed(const ExecutionResult& execution_result) const {
    for (auto formatter : formatters_)
        formatter->examplePassed(execution_result);
}

void Reporter::exampleFailed(const ExecutionResult& execution_result) const {
    for (auto formatter : formatters_)
        formatter->exampleFailed(execution_result);
}

} // namespace core
} // namespace ccspec
