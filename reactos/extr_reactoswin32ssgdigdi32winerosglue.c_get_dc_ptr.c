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
typedef  int /*<<< orphan*/  WINEDC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ GDILoObjType_LO_ALTDC_TYPE ; 
 scalar_t__ GDILoObjType_LO_METADC16_TYPE ; 
 scalar_t__ GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GdiGetClientObjLink (int /*<<< orphan*/ ) ; 
 scalar_t__ GdiGetLDC (int /*<<< orphan*/ ) ; 

WINEDC*
get_dc_ptr(HDC hdc)
{
    /* Check for EMF DC */
    if (GDI_HANDLE_GET_TYPE(hdc) == GDILoObjType_LO_ALTDC_TYPE)
    {
        /* The Wine DC is stored as the LDC */
        return (WINEDC*)GdiGetLDC(hdc);
    }

    /* Check for METADC16 */
    if (GDI_HANDLE_GET_TYPE(hdc) == GDILoObjType_LO_METADC16_TYPE)
    {
        return GdiGetClientObjLink(hdc);
    }

    return NULL;
}