#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cur_handles; scalar_t__* handles; } ;
struct TYPE_4__ {int rdSize; size_t* rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  scalar_t__ PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  TYPE_2__ METAFILEDRV_PDEVICE ;
typedef  size_t INT16 ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  META_DELETEOBJECT ; 
 size_t MFDRV_FindObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL MFDRV_DeleteObject( PHYSDEV dev, HGDIOBJ obj )
{
    METARECORD mr;
    METAFILEDRV_PDEVICE *physDev = (METAFILEDRV_PDEVICE *)dev;
    INT16 index;
    BOOL ret = TRUE;

    index = MFDRV_FindObject(dev, obj);
    if( index < 0 )
        return FALSE;

    mr.rdSize = sizeof mr / 2;
    mr.rdFunction = META_DELETEOBJECT;
    mr.rdParm[0] = index;

    if(!MFDRV_WriteRecord( dev, &mr, mr.rdSize*2 ))
        ret = FALSE;

    physDev->handles[index] = 0;
    physDev->cur_handles--;
    return ret;
}