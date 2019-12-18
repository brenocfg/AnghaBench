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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  scalar_t__ GDILOOBJTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ConvertObjectType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDILoObjType_LO_ALTDC_TYPE ; 
 scalar_t__ GDILoObjType_LO_METADC16_TYPE ; 
 scalar_t__ GDILoObjType_LO_METAFILE16_TYPE ; 
 scalar_t__ GDILoObjType_LO_METAFILE_TYPE ; 
 scalar_t__ GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GdiGetClientObjLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GdiGetLDC (int /*<<< orphan*/ ) ; 

PVOID
GDI_GetObjPtr(
    HGDIOBJ hobj,
    WORD wType)
{
    GDILOOBJTYPE eObjType;

    /* Check if the object type matches */
    eObjType = ConvertObjectType(wType);
    if ((eObjType == 0) || (GDI_HANDLE_GET_TYPE(hobj) != eObjType))
    {
        return NULL;
    }

    /* Check if we have an ALTDC */
    if (eObjType == GDILoObjType_LO_ALTDC_TYPE)
    {
        /* Object is stored as LDC */
        return GdiGetLDC(hobj);
    }

    /* Check for client objects */
    if ((eObjType == GDILoObjType_LO_METAFILE_TYPE) ||
        (eObjType == GDILoObjType_LO_METAFILE16_TYPE) ||
        (eObjType == GDILoObjType_LO_METADC16_TYPE))
    {
        return GdiGetClientObjLink(hobj);
    }

    /* This should never happen! */
    ASSERT(FALSE);
    return NULL;
}