#ifndef PLANGENERATOR_H_
#define PLANGENERATOR_H_

// C & C++ system includes
#include <cstdint>

// Own includes

// Forward declarations

class PlanGenerator
{
  public:
    PlanGenerator() = delete;
    ~PlanGenerator() = default;

    static int32_t generatePlan(int32_t mode);
};

#endif //! PLANGENERATOR_H_