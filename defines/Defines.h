#ifndef DEFINES_H_
#define DEFINES_H_

// C & C++ system includes
#include <cstdint>

// Own includes

// Forward declarations

namespace FileNames
{
constexpr const char *CONCHES_CFG_FILENAME = "../cfg/conches_cfg.txt";
constexpr const char *MASSES_CFG_FILENAME = "../cfg/masses_cfg.txt";
constexpr const char *DEMANDS_FILENAME = "../cfg/demands.txt";
constexpr const char *PROD_PLAN_FILENAME = "../cfg/production_plan.txt";
} // namespace FileNames

namespace Constants
{
constexpr int32_t TIME_IN_DAY = 24 * 60;
constexpr int32_t SHIFTS_IN_DAY = 3;
constexpr int32_t DAYS_IN_WEEK = 7;
constexpr int32_t SHIFTS_IN_WEEK = SHIFTS_IN_DAY * DAYS_IN_WEEK;
constexpr int32_t TIME_IN_SHIFTS[3] = {8 * 60 + 30, 8 * 60 + 30, 7 * 60};
constexpr int32_t TIME_IN_WEEK = TIME_IN_DAY * DAYS_IN_WEEK;

constexpr int32_t VERY_LOW_PRIORITY = -1000000;
constexpr int32_t LOW_PRIORITY_TRESHOLD = -150000;
constexpr int32_t NORMAL_PRIORITY_TRESHOLD = -15000;
constexpr int32_t HIGH_PRIORITY_TRESHOLD = -1500;
constexpr int32_t MAX_CAPACITY_TOLERANCE = 5000;
} // namespace Constants

#endif //! DEFINES_H_