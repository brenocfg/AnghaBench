#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * emh; } ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  ENHMETAHEADER ;
typedef  TYPE_1__ ENHMETAFILEOBJ ;

/* Variables and functions */
 TYPE_1__* GDI_GetObjPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GDI_ReleaseObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_ENHMETAFILE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static ENHMETAHEADER *EMF_GetEnhMetaHeader( HENHMETAFILE hmf )
{
    ENHMETAHEADER *ret = NULL;
    ENHMETAFILEOBJ *metaObj = GDI_GetObjPtr( hmf, OBJ_ENHMETAFILE );
    TRACE("hmf %p -> enhmetaObj %p\n", hmf, metaObj);
    if (metaObj)
    {
        ret = metaObj->emh;
        GDI_ReleaseObj( hmf );
    }
    return ret;
}