#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gdi_obj_funcs {int dummy; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * HGDIOBJ ;
typedef  scalar_t__ GDILOOBJTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ConvertObjectType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDILoObjType_LO_METADC16_TYPE ; 
 scalar_t__ GDILoObjType_LO_METAFILE16_TYPE ; 
 scalar_t__ GDILoObjType_LO_METAFILE_TYPE ; 
 int /*<<< orphan*/ * GdiCreateClientObj (int /*<<< orphan*/ ,scalar_t__) ; 

HGDIOBJ
alloc_gdi_handle(
    PVOID pvObject,
    WORD wType,
    const struct gdi_obj_funcs *funcs)
{
    GDILOOBJTYPE eObjType;

    /* Get the GDI object type */
    eObjType = ConvertObjectType(wType);
    if ((eObjType != GDILoObjType_LO_METAFILE_TYPE) &&
        (eObjType != GDILoObjType_LO_METAFILE16_TYPE) &&
        (eObjType != GDILoObjType_LO_METADC16_TYPE))
    {
        /* This is not supported! */
        ASSERT(FALSE);
        return NULL;
    }

    /* Insert the client object */
    return GdiCreateClientObj(pvObject, eObjType);
}