#ifndef CONCHE_H_
#define CONCHE_H_

// C & C++ system includes
#include <cstdint>
#include <string>
#include <vector>

// Own includes
#include "defines/Defines.h"

// Forward declarations

class Conche
{
  public:
    Conche() = default;
    ~Conche() = default;
    int32_t init(std::string concheName, int32_t concheType, int32_t capacity);

    void setRemainingTime(int32_t remainingTime);
    void setIsAvailable(bool isAvailable);

    std::string getConcheName() const;
    int32_t getConcheType() const;
    int32_t getConcheCapacity() const;
    int32_t getRemainingTime() const;
    bool getIsAvailable() const;

    void startProductionOnConche(int32_t conchingTime);
    void resetConche();

  private:
    std::string _concheName;
    int32_t _concheType = -1;
    int32_t _concheCapacity = 0;
    int32_t _remainingTime = 0;
    bool _isAvailable = true;
};

#endif //! CONCHE_H_