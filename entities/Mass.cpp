// Coresponding header
#include "entities/Mass.h"

// C & C++ system includes
#include <iostream>

// Own includes

int32_t Mass::init(const std::string &massName, int32_t massType, int32_t maxStorageCapacity,
                   const std::vector<int32_t> &refiningTimes, const std::vector<int32_t> &conchingTimes,
                   int32_t startingVolume, int32_t *needsByShift, int32_t totalVolumeToBeUsed)
{
    this->_massName = massName;
    this->_massType = massType;
    this->_maxStorageCapacity = maxStorageCapacity;

    if (refiningTimes.size() != conchingTimes.size())
    {
        std::cerr << "Error, different number of refining times and conching times for mass: " << massName << std::endl;
        return EXIT_FAILURE;
    }

    for (int32_t refiningTime : refiningTimes)
        this->_refiningTimes.push_back(refiningTime);

    for (int32_t conchingTime : conchingTimes)
        this->_conchingTimes.push_back(conchingTime);

    this->_startingVolume = startingVolume;
    this->_totalVolumeToBeUsed = totalVolumeToBeUsed;
    for (int32_t i = 0; i < Constants::SHIFTS_IN_WEEK; i++)
        this->_needsByShift[i] = needsByShift[i];

    this->_totalNeededVolume = totalVolumeToBeUsed - startingVolume;
    this->_currentVolume = this->_startingVolume;

    return EXIT_SUCCESS;
}

// --- BEGIN SETTERS ---

void Mass::setPriority(int32_t priority)
{
    this->_priority = priority;
}

void Mass::addRefiningTimes(int32_t newRefiningTime)
{
    this->_refiningTimes.push_back(newRefiningTime);
}

void Mass::addConchingTimes(int32_t newConchingTime)
{
    this->_conchingTimes.push_back(newConchingTime);
}

// --- END SETTERS ---

// --- BEGIN GETTERS ---

std::string Mass::getMassName() const
{
    return this->_massName;
}

int32_t Mass::getMassType() const
{
    return this->_massType;
}

int32_t Mass::getMaxStorageCapacity() const
{
    return this->_maxStorageCapacity;
}

int32_t Mass::getStartingVolume() const
{
    return this->_startingVolume;
}

int32_t Mass::getCurrentVolume() const
{
    return this->_currentVolume;
}

int32_t Mass::getTotalVolumeToBeUsed() const
{
    return this->_totalVolumeToBeUsed;
}

int32_t Mass::getTotalNeededVolume() const
{
    return this->_totalNeededVolume;
}

int32_t Mass::getPriority() const
{
    return this->_priority;
}

std::vector<int32_t> Mass::getRefiningTimes() const
{
    return this->_refiningTimes;
}

std::vector<int32_t> Mass::getConchingTimes() const
{
    return this->_conchingTimes;
}

int32_t *Mass::getNeedsByShift()
{
    return this->_needsByShift;
}

int32_t *Mass::getSupplyByShift()
{
    return this->_supplyByShift;
}

// --- END GETTERS ---

void Mass::updatePriority(int32_t currShift) // contains all logic for calculating priority
{
    int32_t needsShift1 = 0;
    int32_t needsShift2 = 0;
    int32_t needsShift3 = 0;
    int32_t needsTotalNext3Shifts = 0;

    if (currShift == Constants::SHIFTS_IN_WEEK)
    {
        std::cerr
            << "Error, Mass::updatePriority() received an index that exceeds the maximum number of shifts in a week."
            << std::endl;
        return;
    }

    if (currShift + 1 < Constants::SHIFTS_IN_WEEK)
        needsShift1 = this->_needsByShift[currShift + 1];

    if (currShift + 2 < Constants::SHIFTS_IN_WEEK)
        needsShift2 = this->_needsByShift[currShift + 2];

    if (currShift + 3 < Constants::SHIFTS_IN_WEEK)
        needsShift3 = this->_needsByShift[currShift + 3];

    needsTotalNext3Shifts = needsShift1 + needsShift2 + needsShift3;

    this->_priority = -(this->_currentVolume - needsTotalNext3Shifts);
}

void Mass::updateCurrentVolume(int32_t volumeChange)
{
    this->_currentVolume += volumeChange;
}

void Mass::updateTotalNeededVolume(int32_t volumeChange)
{
    this->_totalNeededVolume += volumeChange;
}

int32_t Mass::updateSupplyByShift(int32_t shiftIdx, int32_t volumeChange)
{
    if (shiftIdx < 0 || shiftIdx >= Constants::SHIFTS_IN_WEEK)
    {
        std::cerr << "Error, received invalid shift index." << std::endl;
        return EXIT_FAILURE;
    }

    this->_supplyByShift[shiftIdx] += volumeChange;

    return EXIT_SUCCESS;
}