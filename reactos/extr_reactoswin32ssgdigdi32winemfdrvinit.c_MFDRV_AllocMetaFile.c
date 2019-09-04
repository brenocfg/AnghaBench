#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_12__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_11__ {int /*<<< orphan*/  physDev; } ;
struct TYPE_10__ {int handles_size; TYPE_4__ dev; TYPE_1__* mh; scalar_t__ hFile; scalar_t__ cur_handles; void* handles; } ;
struct TYPE_9__ {int mtHeaderSize; int mtVersion; int mtSize; scalar_t__ mtNoParameters; scalar_t__ mtMaxRecord; scalar_t__ mtNoObjects; } ;
typedef  int /*<<< orphan*/  METAHEADER ;
typedef  TYPE_2__ METAFILEDRV_PDEVICE ;
typedef  TYPE_3__ DC ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HANDLE_LIST_INC ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MFDRV_Funcs ; 
 int /*<<< orphan*/  OBJ_METADC ; 
 int /*<<< orphan*/  SetVirtualResolution (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* alloc_dc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dc_ptr (TYPE_3__*) ; 
 int /*<<< orphan*/  push_dc_driver (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DC *MFDRV_AllocMetaFile(void)
{
    DC *dc;
    METAFILEDRV_PDEVICE *physDev;

    if (!(dc = alloc_dc_ptr( OBJ_METADC ))) return NULL;

    physDev = HeapAlloc(GetProcessHeap(),0,sizeof(*physDev));
    if (!physDev)
    {
        free_dc_ptr( dc );
        return NULL;
    }
    if (!(physDev->mh = HeapAlloc( GetProcessHeap(), 0, sizeof(*physDev->mh) )))
    {
        HeapFree( GetProcessHeap(), 0, physDev );
        free_dc_ptr( dc );
        return NULL;
    }

    push_dc_driver( &dc->physDev, &physDev->dev, &MFDRV_Funcs );

    physDev->handles = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, HANDLE_LIST_INC * sizeof(physDev->handles[0]));
    physDev->handles_size = HANDLE_LIST_INC;
    physDev->cur_handles = 0;

    physDev->hFile = 0;

    physDev->mh->mtHeaderSize   = sizeof(METAHEADER) / sizeof(WORD);
    physDev->mh->mtVersion      = 0x0300;
    physDev->mh->mtSize         = physDev->mh->mtHeaderSize;
    physDev->mh->mtNoObjects    = 0;
    physDev->mh->mtMaxRecord    = 0;
    physDev->mh->mtNoParameters = 0;

    SetVirtualResolution( physDev->dev.hdc, 0, 0, 0, 0);

    return dc;
}