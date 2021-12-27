#include "dataprovidertest.h"
#include "test_data.h"

void DataProviderStatic::fetchData(uint8_t* pData, unsigned int unSize)
{
    for(int i=0; i<28; i++)
    {
        for(int j=0;j<28;j++)
        {
            int nPos = i*28 + j;
            pData[nPos] = test_data[i][j];
        }
    }
}