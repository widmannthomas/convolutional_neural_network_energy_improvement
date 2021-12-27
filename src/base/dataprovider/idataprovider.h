#ifndef SRC_BASE_DATAPROVIDER_IDATAPROVIDER
#define SRC_BASE_DATAPROVIDER_IDATAPROVIDER

#include "pico/stdlib.h"

class IDataProvider
{
public:
    virtual ~IDataProvider() {};
    virtual void fetchData(uint8_t* pData, unsigned int unSize) = 0;
};

#endif /* SRC_BASE_DATAPROVIDER_IDATAPROVIDER */
