#ifndef CCSPEC_EXPECTATION_EXCEPTION_H_
#define CCSPEC_EXPECTATION_EXCEPTION_H_

#include <exception>
#include <string>

namespace ccspec {
namespace expectation {

class Exception : public std::exception {
  public:
    virtual const char* what() const noexcept;
    virtual std::string toString() const = 0;
};

} // namespace expectation
} // namespace ccspec

#endif // CCSPEC_EXPECTATION_EXCEPTION_H_
