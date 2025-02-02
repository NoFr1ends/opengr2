/*!
	Project: libopengrn
	File: gr2nfo.c
	Low level information dump of a gr2

	Copyright (C) 2021 Arves100
*/
#include <stdio.h>
#include <stdlib.h>
#include "../libopengrn/gr2.h"
#include "../libopengrn/debug.h"

int main(int argc, char** argv)
{
	FILE* fp;
	size_t l;
	TGr2 gr2;
	uint8_t* data;

	DumpMemLeak();

	printf("Granny2 dumper with Low Level libopengrn API (Copyright (C) 2021 Arves100)\n");

	fopen_s(&fp, argv[1], "rb");

	if (!fp)
	{
		printf("cannot open %s\n", argv[1]);
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	l = ftell(fp);
	rewind(fp);

	data = (uint8_t*)malloc(l);

	if (!data)
	{
		fclose(fp);
		printf("out of memory\n");
		return 1;
	}

	if (fread(data, l, 1, fp) != 1)
	{
		fclose(fp);
		free(data);
		printf("cannot read entire file content\n");
		return 1;
	}

	fclose(fp);

	Gr2_Init(&gr2);
	if (!Gr2_Load(data, l, &gr2))
	{
		free(data);
		printf("Cannot load gr2 file\n");
		return 1;
	}

	free(data);

	printf("Header info:\n\tMagic:%lu %lu %lu %lu", gr2.header.magic[0], gr2.header.magic[1], gr2.header.magic[2], gr2.header.magic[3]);
	printf("\n\tSize with sectors : %u\n\tFormat: %u\n\tExtra:", gr2.header.sizeWithSectors, gr2.header.format);

	for (size_t i = 0; i < 8; i++)
		printf(" %u", gr2.header.extra[i]);

	printf("\n");

	printf("File info:\n\tFormat: %d\n\tFile info size: %u\n\tSector count: %u\n\tTotal size: %u\n\tTag: %x\n\tCRC32: %xRoot reference: Sector: %u Position: %u\n\tType reference: Sector: %u Position: %u\n\tExtra:", gr2.fileInfo.format, gr2.fileInfo.fileInfoSize, gr2.fileInfo.sectorCount, gr2.fileInfo.totalSize, gr2.fileInfo.tag, gr2.fileInfo.crc32, gr2.fileInfo.root.sector, gr2.fileInfo.root.position, gr2.fileInfo.type.sector,gr2.fileInfo.type.position);

	for (size_t i = 0; i < 32; i++)
		printf(" %u", gr2.fileInfo.extra[i]);

	printf("\n");

	for (size_t i = 0; i < gr2.fileInfo.sectorCount; i++)
	{
		TSector sector = gr2.sectors[i];

		printf("Sector %zu complete offset: %zu\n\t", i, gr2.sectorOffsets[i]);

		printf("Alignment: %u\n\tCompressed length: %u\n\tCompression type: %u\n\tData offset: %u\n\tDecompressed length: %u\n\tOddle Stop0: %u\n\tOodle Stop1: %u\n\tFixup: Position: %u Count: %u\n\tMarshalling: Position: %u Count: %u\n", sector.alignment, sector.compressedLen, sector.compressType, sector.dataOffset, sector.decompressLen, sector.oodleStop0, sector.oodleStop1, sector.fixupOffset, sector.fixupSize, sector.marshallOffset, sector.marshallSize);
	}

	for (size_t i = 0; i < gr2.elements.count; i++)
	{
		TElementInfo* info = (TElementInfo*)DArray_Get(&gr2.elements, i);

		printf("Element %zu: %u %u %I64u %p %s\n", i, info->info.arraySize, info->info.type, info->info.extra4, info->data, info->name);
	}

	for (size_t i = 0; i < gr2.root.children.count; i++)
	{
		size_t pos = *(size_t*)DArray_Get(&gr2.root.children, i);
		TElementInfo* info = (TElementInfo*)DArray_Get(&gr2.elements, pos);

		printf("Root children %zu: %u %u %I64u %p %s\n", i, info->info.arraySize, info->info.type, info->info.extra4, info->data, info->name);
	}

	Gr2_Free(&gr2);

	return 0;
}
