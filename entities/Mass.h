#ifndef MASS_H_
#define MASS_H_

// C & C++ system includes
#include <cstdint>
#include <string>
#include <vector>

// Own includes
#include "defines/Defines.h"

// Forward declarations

class Mass
{
  public:
    Mass() = default;
    ~Mass() = default;
    int32_t init(const std::string &massName, int32_t massType, int32_t maxStorageCapacity,
                 const std::vector<int32_t> &refiningTimes, const std::vector<int32_t> &conchingTimes,
                 int32_t startingVolume, int32_t *needsByShift, int32_t totalVolumeToBeUsed);

    void setPriority(int32_t priority);
    void addRefiningTimes(int32_t newRefiningTime);
    void addConchingTimes(int32_t newConchingTime);

    std::string getMassName() const;
    int32_t getMassType() const;
    int32_t getMaxStorageCapacity() const;
    int32_t getStartingVolume() const;
    int32_t getCurrentVolume() const;
    int32_t getTotalVolumeToBeUsed() const;
    int32_t getTotalNeededVolume() const;
    int32_t getPriority() const;
    std::vector<int32_t> getRefiningTimes() const;
    std::vector<int32_t> getConchingTimes() const;
    int32_t *getNeedsByShift();
    int32_t *getSupplyByShift();

    void updatePriority(int32_t index); // contains all logic for calculating priority
    void updateCurrentVolume(int32_t volumeChange);
    void updateTotalNeededVolume(int32_t volumeChange);
    int32_t updateSupplyByShift(int32_t shiftIdx, int32_t volumeChange);

  private:
    std::string _massName;
    int32_t _massType = -1;
    int32_t _maxStorageCapacity = 0;
    std::vector<int32_t> _refiningTimes;
    std::vector<int32_t> _conchingTimes;

    int32_t _startingVolume = 0;
    int32_t _currentVolume = 0;
    int32_t _totalVolumeToBeUsed = 0;
    int32_t _totalNeededVolume = 0;
    int32_t _priority = 0;
    int32_t _needsByShift[Constants::SHIFTS_IN_WEEK]{};
    int32_t _supplyByShift[Constants::SHIFTS_IN_WEEK]{};
};

#endif //! MASS_H_