#ifndef SRC_MNIST_TEST_DATA_DATAPROVIDERTEST
#define SRC_MNIST_TEST_DATA_DATAPROVIDERTEST

#include "../../base/dataprovider/idataprovider.h"

class DataProviderStatic : public IDataProvider
{
public:
    void fetchData(uint8_t* pData, unsigned int unSize) override;
};

#endif /* SRC_MNIST_TEST_DATA_DATAPROVIDERTEST */
