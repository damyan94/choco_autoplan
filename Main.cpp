//
// Avtoplanovik-300 (R)
// by Damyan Damyanov 2022
//
// ----------
//
// Open source and free for use, just remember to give credit to the original autor.
// In case of questions, do not hesitate to contact me on my e-mail: damyandamyanov_94@yahoo.com
//
// For more information about latest version and how to use, please refer to the readme.txt file
//
// ----------
//

// C & C++ system includes
#include <cstdint>
#include <cstdlib>
#include <iostream>

// Own includes
#include "PlanGenerator.h"

int32_t main(int32_t /*argC*/, char * /*argV*/[])
{
    int32_t mode = 0;
    bool intEntered = false;
    std::string input;

    do
    {
        std::cout << "Please choose plan generation mode:\n\n";
        std::cout << "1. Match demand and produce at max.\n";
        std::cout << "2. Match demand and fill up buffers to maximum capacity.\n";
        std::cout << "3. Match demand and do not fill buffers.\n";

        std::cin >> input;

        mode = std::stoi(input);

        if (mode == 1 || mode == 2 || mode == 3)
            intEntered = true;

        else
            std::cout << "Please enter a valid mode.\n\n";

    } while (!intEntered);

    if (EXIT_SUCCESS != PlanGenerator::generatePlan(mode))
    {
        std::cerr << "Error, PlanGenerator::generatePlan() failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "\nPress Enter to close the program." << std::endl;

    std::cin.ignore();
    std::cin.get();

    return EXIT_SUCCESS;
}
