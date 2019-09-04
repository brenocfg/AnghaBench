#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  void* UINT ;
struct TYPE_12__ {int biSizeImage; } ;
struct TYPE_14__ {TYPE_1__ bmiHeader; } ;
struct TYPE_13__ {int rdSize; void** rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_2__ METARECORD ;
typedef  TYPE_3__* LPCVOID ;
typedef  void* INT16 ;
typedef  void* INT ;
typedef  int DWORD ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  META_SETDIBTODEV ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int get_dib_info_size (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  memcpy (void**,TYPE_3__*,int) ; 

INT MFDRV_SetDIBitsToDevice( PHYSDEV dev, INT xDst, INT yDst, DWORD cx,
                             DWORD cy, INT xSrc, INT ySrc, UINT startscan,
                             UINT lines, LPCVOID bits, BITMAPINFO *info, UINT coloruse )

{
    DWORD infosize = get_dib_info_size(info, coloruse);
    DWORD len = sizeof(METARECORD) + 8 * sizeof(WORD) + infosize + info->bmiHeader.biSizeImage;
    METARECORD *mr = HeapAlloc( GetProcessHeap(), 0, len );
    if(!mr) return 0;

    mr->rdSize = len / 2;
    mr->rdFunction = META_SETDIBTODEV;
    mr->rdParm[0] = coloruse;
    mr->rdParm[1] = lines;
    mr->rdParm[2] = startscan;
    mr->rdParm[3] = (INT16)ySrc;
    mr->rdParm[4] = (INT16)xSrc;
    mr->rdParm[5] = (INT16)cy;
    mr->rdParm[6] = (INT16)cx;
    mr->rdParm[7] = (INT16)yDst;
    mr->rdParm[8] = (INT16)xDst;
    memcpy(mr->rdParm + 9, info, infosize);
    memcpy(mr->rdParm + 9 + infosize / 2, bits, info->bmiHeader.biSizeImage);
    MFDRV_WriteRecord( dev, mr, mr->rdSize * 2 );
    HeapFree( GetProcessHeap(), 0, mr );
    return lines;
}