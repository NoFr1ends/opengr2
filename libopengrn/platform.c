/*!
	Project: libopengrn
	File: platform.c
	Platform utility

	Copyright (C) 2021 Arves100
*/
#include "platform.h"


/*!
	Gets the pointer size of the platform
	@return the pointer size
*/
OG_DLLAPI int Platform_GetPointerSize() {
    return sizeof(void*);
}

/*!
	Checks if the platform is big endian
	@return true if the platform is big endian
*/
OG_DLLAPI bool Platform_IsBigEndian()
{
    uint16_t t = 1;
    const unsigned char* c = (unsigned char*)(&t);

    /*
		*c == 1 -> little endian
		*c != 1 -> big endian
	*/

    return *c != 1;
}

/*!
	Swap bytes for endianness mismatch (type1)
	@param data the data to swap
	@param len the length of the data
*/
OG_DLLAPI void Platform_Swap1(uint8_t* data, size_t len)
{
	if (len < 4)
		return;

	for (size_t i = 0; i < len / 4; i++)
	{
		uint8_t d3 = data[i + 3], d2 = data[i + 2];

		data[i + 3] = data[i];
		data[i + 2] = data[i + 1];
		data[i + 1] = d2;
		data[i] = d3;
	}
}

/*!
	Swap bytes for endianness mismatch (type2)
	@param data the data to swap
	@param len the length of the data
*/
OG_DLLAPI void Platform_Swap2(uint8_t* data, size_t len)
{
	if (len < 4)
		return;

	for (size_t i = 0; i < len / 4; i++)
	{
		uint8_t d0 = data[i], d2 = data[i + 2];

		data[i] = data[i + 1];
		data[i + 1] = d0;
		data[i + 2] = data[i + 3];
		data[i + 3] = d2;
	}
}
