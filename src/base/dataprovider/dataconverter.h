#ifndef SRC_BASE_DATAPROVIDER_DATACONVERTER
#define SRC_BASE_DATAPROVIDER_DATACONVERTER

template<class T>
class DataConverter
{
public:
    T* fromByteStream(char* pStream, unsigned int unSize)
    {
        //unsigned int unSizeTarget(unSize / sizeof(T));

        return reinterpret_cast<T*>(pStream);
    };

private:
    union Converter
    {
        char* pBytes;
        T* p;  
    };
};

#endif /* SRC_BASE_DATAPROVIDER_DATACONVERTER */
