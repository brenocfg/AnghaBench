#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
struct TYPE_8__ {size_t NumberOfSections; } ;
struct TYPE_11__ {TYPE_1__ FileHeader; } ;
struct TYPE_9__ {scalar_t__ VirtualSize; } ;
struct TYPE_10__ {scalar_t__ PointerToRawData; scalar_t__ SizeOfRawData; scalar_t__ VirtualAddress; TYPE_2__ Misc; } ;
typedef  TYPE_3__ IMAGE_SECTION_HEADER ;
typedef  TYPE_4__ IMAGE_NT_HEADERS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_3__* IMAGE_FIRST_SECTION (TYPE_4__*) ; 

__attribute__((used)) static DWORD rva_to_offset(IMAGE_NT_HEADERS *nthdrs, DWORD rva)
{
    DWORD offset = rva, limit;
    IMAGE_SECTION_HEADER *img;
    WORD i;

    img = IMAGE_FIRST_SECTION(nthdrs);

    if (rva < img->PointerToRawData)
        return rva;

    for (i = 0; i < nthdrs->FileHeader.NumberOfSections; i++)
    {
        if (img[i].SizeOfRawData)
            limit = img[i].SizeOfRawData;
        else
            limit = img[i].Misc.VirtualSize;

        if (rva >= img[i].VirtualAddress &&
            rva < (img[i].VirtualAddress + limit))
        {
            if (img[i].PointerToRawData != 0)
            {
                offset -= img[i].VirtualAddress;
                offset += img[i].PointerToRawData;
            }

            return offset;
        }
    }

    return 0;
}