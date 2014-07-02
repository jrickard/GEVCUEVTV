/*
#include <Arduino.h>  // for type definitions
#include <MemCache.h>
MemCache* EmemCache2;

template <class T> int EEPROM_writeAnything(uint32_t ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EmemCache2->Write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(uint32_t ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
           EmemCache2->Read(ee++, p++);
    return i;
}
*/
