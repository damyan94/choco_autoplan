// Coresponding header
#include "entities/Conche.h"

// C & C++ system includes
#include <iostream>

// Own includes

int32_t Conche::init(std::string concheName, int32_t concheType, int32_t capacity)
{
    this->_concheName = concheName;
    this->_concheType = concheType;
    this->_concheCapacity = capacity;

    return EXIT_SUCCESS;
}

// --- BEGIN SETTERS ---

void Conche::setRemainingTime(int32_t remainingTime)
{
    this->_remainingTime = remainingTime;
}

void Conche::setIsAvailable(bool isAvailable)
{
    this->_isAvailable = isAvailable;
}

// --- END SETTERS ---

// --- BEGIN GETTERS ---

std::string Conche::getConcheName() const
{
    return this->_concheName;
}

int32_t Conche::getConcheType() const
{
    return this->_concheType;
}

int32_t Conche::getConcheCapacity() const
{
    return this->_concheCapacity;
}

int32_t Conche::getRemainingTime() const
{
    return this->_remainingTime;
}

bool Conche::getIsAvailable() const
{
    return this->_isAvailable;
}

// --- END GETTERS ---

void Conche::startProductionOnConche(int32_t conchingTime)
{
    this->_remainingTime = conchingTime;
    this->_isAvailable = false;
}

void Conche::resetConche()
{
    this->_remainingTime = 0;
    this->_isAvailable = true;
}