#ifndef PLANGENERATORUTILS_H_
#define PLANGENERATORUTILS_H_

// C & C++ system includes
#include <cstdint>
#include <string>
#include <vector>

// Own includes

// Forward declarations
class Conche;
class Mass;

namespace PlanGeneratorUtils
{
int32_t initConches(std::vector<Conche> &conches);
int32_t initMasses(std::vector<Mass> &masses, int32_t concheTypesCount);

std::vector<std::string> getConcheNames(const std::vector<Conche> &conches);
int32_t getMaxPriorityMassIdx(const std::vector<Mass> &masses);
int32_t getShiftFromTime(int32_t time);
}; // namespace PlanGeneratorUtils

#endif //! PLANGENERATORUTILS_H_