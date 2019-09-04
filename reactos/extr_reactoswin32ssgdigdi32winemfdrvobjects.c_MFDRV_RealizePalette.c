#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int UINT ;
struct TYPE_3__ {int rdSize; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  META_REALIZEPALETTE ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

UINT MFDRV_RealizePalette(PHYSDEV dev, HPALETTE hPalette, BOOL dummy)
{
    char buffer[sizeof(METARECORD) - sizeof(WORD)];
    METARECORD *mr = (METARECORD *)&buffer;

    mr->rdSize = (sizeof(METARECORD) - sizeof(WORD)) / sizeof(WORD);
    mr->rdFunction = META_REALIZEPALETTE;

    if (!(MFDRV_WriteRecord( dev, mr, mr->rdSize * sizeof(WORD)))) return 0;

    /* The return value is suppose to be the number of entries
       in the logical palette mapped to the system palette or 0
       if the function failed. Since it's not trivial here to
       get that kind of information and since it's of little
       use in the case of metafiles, we'll always return 1. */
    return 1;
}