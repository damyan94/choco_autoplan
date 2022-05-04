// Coresponding header
#include "utils/PlanGeneratorUtils.h"

// C & C++ system includes
#include <iostream>
#include <sstream>
#include <vector>

// Own includes
#include "defines/Defines.h"
#include "entities/Conche.h"
#include "entities/Mass.h"
#include "utils/ReadWriteFile.h"

// Initialize conches
int32_t PlanGeneratorUtils::initConches(std::vector<Conche> &conches)
{
    std::vector<std::string> inputStrings;
    if (EXIT_SUCCESS != ReadWriteFile::readFromFile(FileNames::CONCHES_CFG_FILENAME, inputStrings))
    {
        std::cerr << "Error, ReadWriteFile::readFromFile() failed." << std::endl;
        return EXIT_FAILURE;
    }

    for (int32_t i = 0; i < int32_t(inputStrings.size()); i++)
    {
        std::string concheName;
        int32_t concheType = 0;
        int32_t concheCapacity = 0;

        std::istringstream iss(inputStrings[i]);
        iss >> concheName >> concheType >> concheCapacity;

        Conche newConche;
        if (EXIT_SUCCESS != newConche.init(concheName, concheType, concheCapacity))
        {
            std::cerr << "Error, Conche.init() failed." << std::endl;
            return EXIT_FAILURE;
        }

        conches.push_back(newConche);
    }

    // --- BEGIN CHECK ---

    /*std::cout << "Name\tType\tCapac\tAvlbl?\tRemTime" << std::endl;
    for (Conche conche : conches)
    {
        std::cout << conche.getConcheName() << "\t" << conche.getConcheType() << "\t" << conche.getConcheCapacity() <<
            "\t" << conche.getIsAvailable() << "\t" << conche.getRemainingTime() << std::endl;
    }
    std::cout << std::endl;*/

    // --- END CHECK ---

    return EXIT_SUCCESS;
}

// Initialize masses
int32_t PlanGeneratorUtils::initMasses(std::vector<Mass> &masses, int32_t concheTypesCount)
{
    std::vector<std::string> inputStringsCfg;
    std::vector<std::string> inputStringsDemands;

    if (EXIT_SUCCESS != ReadWriteFile::readFromFile(FileNames::MASSES_CFG_FILENAME, inputStringsCfg))
    {
        std::cerr << "Error, ReadWriteFile::readFromFile() failed." << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != ReadWriteFile::readFromFile(FileNames::DEMANDS_FILENAME, inputStringsDemands))
    {
        std::cerr << "Error, ReadWriteFile::readFromFile() failed." << std::endl;
        return EXIT_FAILURE;
    }

    if (inputStringsDemands.size() != inputStringsCfg.size())
    {
        std::cerr << "Error, different numbers of lines in input files:\n\t" << FileNames::MASSES_CFG_FILENAME << "\n\t"
                  << FileNames::DEMANDS_FILENAME << std::endl;
        return EXIT_FAILURE;
    }

    for (int32_t i = 0; i < int32_t(inputStringsCfg.size()); i++)
    {
        std::string massName;
        int32_t massType = 0;
        int32_t maxStorageCapacity = 0;
        std::vector<int32_t> refiningTimes;
        std::vector<int32_t> conchingTimes;

        std::istringstream issCfg(inputStringsCfg[i]);
        issCfg >> massName >> massType >> maxStorageCapacity;

        for (int32_t j = 0; j < concheTypesCount; j++)
        {
            int32_t refiningTime = 0;
            issCfg >> refiningTime;
            refiningTimes.push_back(refiningTime);
        }

        for (int32_t j = 0; j < concheTypesCount; j++)
        {
            int32_t conchingTime = 0;
            issCfg >> conchingTime;
            conchingTimes.push_back(conchingTime);
        }

        int32_t startingVolume = 0;
        int32_t needsByShift[7 * 3];
        int32_t totalVolumeToBeUsed = 0;

        std::istringstream issDemands(inputStringsDemands[i]);
        issDemands >> startingVolume;

        for (int32_t &shiftDemand : needsByShift)
        {
            issDemands >> shiftDemand;
            totalVolumeToBeUsed += shiftDemand;
        }

        Mass newMass;
        if (EXIT_SUCCESS != newMass.init(massName, massType, maxStorageCapacity, refiningTimes, conchingTimes,
                                         startingVolume, needsByShift, totalVolumeToBeUsed))
        {
            std::cerr << "Error, Mass.init() failed." << std::endl;
            return EXIT_FAILURE;
        }

        newMass.updatePriority(0);

        masses.push_back(newMass);
    }

    // --- BEGIN CHECK ---

    /*std::cout << "Name\tType\tV0\tVtotal\tVneeded\tPriority" << std::endl;
    for (Mass& mass : masses)
    {
        std::cout << mass.getMassName() << "\t" << mass.getMassType() << "\t" << mass.getStartingVolume() << "\t" <<
            mass.getTotalVolumeToBeUsed() << "\t" << mass.getTotalNeededVolume() << "\t" << mass.getPriority() <<
    std::endl;
    }
    std::cout << std::endl;*/

    // --- END CHECK ---

    return EXIT_SUCCESS;
}

// Helper function - get conche names
std::vector<std::string> PlanGeneratorUtils::getConcheNames(const std::vector<Conche> &conches)
{
    std::vector<std::string> concheNames;
    for (const Conche &conche : conches)
    {
        bool isUniqueName = true;

        if (concheNames.size() == 0)
            concheNames.push_back(conche.getConcheName());

        else
        {
            for (const std::string &name : concheNames)
                if (conche.getConcheName() == name)
                    isUniqueName = false;

            if (isUniqueName)
                concheNames.push_back(conche.getConcheName());
        }
    }

    return concheNames;
}

// Helper function - get index of the current max priority mass
int32_t PlanGeneratorUtils::getMaxPriorityMassIdx(const std::vector<Mass> &masses)
{
    int32_t max = Constants::VERY_LOW_PRIORITY;
    int32_t idx = 0;
    int32_t i = 0;

    for (const Mass &mass : masses)
    {
        if (mass.getPriority() > max)
        {
            max = mass.getPriority();
            idx = i;
        }

        i++;
    }

    return idx;
}

// Helper function - get shift number from current time in minutes
int32_t PlanGeneratorUtils::getShiftFromTime(int32_t time)
{
    int32_t normalizedTime = time % Constants::TIME_IN_DAY;
    int32_t shift = 0;

    for (int i = 0; i < Constants::SHIFTS_IN_DAY; i++)
    {
        if (normalizedTime >= Constants::TIME_IN_SHIFTS[i] && normalizedTime < Constants::TIME_IN_SHIFTS[i + 1])
        {
            shift = i + 1;
        }
    }

    return shift;
}