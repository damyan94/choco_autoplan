// Coresponding header
#include "PlanGenerator.h"

// C & C++ system includes
#include <iostream>
#include <sstream>
#include <vector>

// Own includes
#include "defines/Defines.h"
#include "entities/Conche.h"
#include "entities/Mass.h"
#include "utils/PlanGeneratorUtils.h"
#include "utils/ReadWriteFile.h"

using namespace PlanGeneratorUtils;

// The function that does all the magic and generates the production plan
int32_t static populateConches(std::vector<Conche> &conches, std::vector<Mass> &masses, int32_t mode)
{
    int32_t remainingRefiningTime = 0;
    bool refinersAvailable = true;
    int32_t priorityTreshold = 0;

    if (mode == 1 || mode == 2)
        priorityTreshold = Constants::LOW_PRIORITY_TRESHOLD;

    else if (mode == 3)
        priorityTreshold = Constants::NORMAL_PRIORITY_TRESHOLD;

    // Iterate for every day and shift and update demands appropriately
    for (int32_t weekDay = 0; weekDay < Constants::DAYS_IN_WEEK; weekDay++)
        for (int32_t shift = 0; shift < Constants::SHIFTS_IN_DAY; shift++)
        {
            int32_t shiftIdx = weekDay * Constants::SHIFTS_IN_DAY + shift;

            for (Mass &mass : masses)
            {
                mass.updateCurrentVolume(-mass.getNeedsByShift()[shiftIdx]);
                mass.updatePriority(shiftIdx);
            }

            // For every minute in the shift if the refiners are available, start production of the
            // current max priority mass on the first available conche you find.
            // TODO this can be optimized to take into account the capacity for the given mass on the given conche type.
            // TODO e.g. to run Africana only on the CM conches and to prefer to run BV Dark on the ELK conche.
            for (int32_t time = 0; time < Constants::TIME_IN_SHIFTS[shift]; time++)
            {
                if (refinersAvailable)
                {
                    for (Conche &conche : conches)
                    {
                        if (conche.getIsAvailable())
                        {
                            int32_t currMaxPriorityMassIdx = getMaxPriorityMassIdx(masses);

                            // if this is checked, the plan will generate so as to fill up the buffers
                            if (mode == 2)
                            {
                                if (masses[currMaxPriorityMassIdx].getCurrentVolume() >=
                                    masses[currMaxPriorityMassIdx].getMaxStorageCapacity() -
                                        Constants::MAX_CAPACITY_TOLERANCE)
                                    masses[currMaxPriorityMassIdx].setPriority(Constants::VERY_LOW_PRIORITY);
                            }

                            if (masses[currMaxPriorityMassIdx].getPriority() < priorityTreshold)
                                break;

                            refinersAvailable = false;
                            remainingRefiningTime =
                                masses[currMaxPriorityMassIdx].getRefiningTimes()[conche.getConcheType()];

                            int32_t conchingTime =
                                masses[currMaxPriorityMassIdx].getConchingTimes()[conche.getConcheType()];
                            conche.startProductionOnConche(conchingTime);

                            int32_t currConcheCapacity = conche.getConcheCapacity();
                            masses[currMaxPriorityMassIdx].updateCurrentVolume(currConcheCapacity);
                            masses[currMaxPriorityMassIdx].updateTotalNeededVolume(-currConcheCapacity);
                            masses[currMaxPriorityMassIdx].updatePriority(shiftIdx);

                            if (EXIT_SUCCESS !=
                                masses[currMaxPriorityMassIdx].updateSupplyByShift(shiftIdx, currConcheCapacity))
                            {
                                std::cerr << "Error, updateSupplyByShift() failed." << std::endl;
                                return EXIT_FAILURE;
                            }

                            break;
                        }
                    }
                }

                // If the refiners are not available, just pass the time, updating all conching times, until they are
                // available
                else //! refinersAvailable
                {
                    if (remainingRefiningTime <= 0)
                        refinersAvailable = true;
                }

                for (Conche &conche : conches)
                {
                    if (conche.getRemainingTime() <= 0)
                        conche.resetConche();

                    else
                        conche.setRemainingTime(conche.getRemainingTime() - 1);
                }

                remainingRefiningTime--;
            }
        }

    return EXIT_SUCCESS;
}

// Export the generated production plan to a file on the disk
int32_t static exportProductionPlan(const std::vector<Mass> &masses)
{
    std::string writeString;

    for (auto mass : masses)
    {
        for (int32_t i = 0; i < Constants::SHIFTS_IN_WEEK; i++)
        {
            writeString += std::to_string(mass.getSupplyByShift()[i]);
            writeString += "\t";
        }

        writeString += "\n";
    }

    if (EXIT_SUCCESS != ReadWriteFile::writeToFile(FileNames::PROD_PLAN_FILENAME, writeString, WriteMode::OUT))
    {
        std::cerr << "Error, ReadWriteFile::writeToFile() failed." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// This function that generates the plan is called in the int main()
int32_t PlanGenerator::generatePlan(int32_t mode)
{
    std::vector<Conche> conches;
    std::vector<Mass> masses;
    int32_t concheTypesCount;

    std::cout << "\nInitializing conches... ";
    if (EXIT_SUCCESS != initConches(conches))
    {
        std::cerr << "Error, initConches() failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Done!\nInitializing masses... ";
    concheTypesCount = getConcheNames(conches).size();
    if (EXIT_SUCCESS != initMasses(masses, concheTypesCount))
    {
        std::cerr << "Error, initMasses() failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Done!\nPopulating conches... ";
    if (EXIT_SUCCESS != populateConches(conches, masses, mode))
    {
        std::cerr << "Error, populateConches() failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Done!\nExporting production plan... ";
    if (EXIT_SUCCESS != exportProductionPlan(masses))
    {
        std::cerr << "Error, exportProductionPlan() failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Done!\n\nDone! Plan generated successfully and exported to: " << FileNames::PROD_PLAN_FILENAME
              << std::endl;

    return EXIT_SUCCESS;
}