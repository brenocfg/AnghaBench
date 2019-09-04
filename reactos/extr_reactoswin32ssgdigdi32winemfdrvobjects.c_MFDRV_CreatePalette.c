#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int rdSize; int* rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  int /*<<< orphan*/  LOGPALETTE ;
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  META_CREATEPALETTE ; 
 int /*<<< orphan*/  META_SELECTPALETTE ; 
 int MFDRV_AddHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL MFDRV_CreatePalette(PHYSDEV dev, HPALETTE hPalette, LOGPALETTE* logPalette, int sizeofPalette)
{
    int index;
    BOOL ret;
    METARECORD *mr;

    mr = HeapAlloc( GetProcessHeap(), 0, sizeof(METARECORD) + sizeofPalette - sizeof(WORD) );
    mr->rdSize = (sizeof(METARECORD) + sizeofPalette - sizeof(WORD)) / sizeof(WORD);
    mr->rdFunction = META_CREATEPALETTE;
    memcpy(&(mr->rdParm), logPalette, sizeofPalette);
    if (!(MFDRV_WriteRecord( dev, mr, mr->rdSize * sizeof(WORD))))
    {
        HeapFree(GetProcessHeap(), 0, mr);
        return FALSE;
    }

    mr->rdSize = sizeof(METARECORD) / sizeof(WORD);
    mr->rdFunction = META_SELECTPALETTE;

    if ((index = MFDRV_AddHandle( dev, hPalette )) == -1) ret = FALSE;
    else
    {
        *(mr->rdParm) = index;
        ret = MFDRV_WriteRecord( dev, mr, mr->rdSize * sizeof(WORD));
    }
    HeapFree(GetProcessHeap(), 0, mr);
    return ret;
}