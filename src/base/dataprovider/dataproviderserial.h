#ifndef SRC_BASE_DATAPROVIDER_DATAPROVIDERSERIAL
#define SRC_BASE_DATAPROVIDER_DATAPROVIDERSERIAL

#include "idataprovider.h"

class DataProviderSerial : public IDataProvider
{
public:
    void fetchData(uint8_t* pData, unsigned int unSize) override;
};

#endif /* SRC_BASE_DATAPROVIDER_DATAPROVIDERSERIAL */
