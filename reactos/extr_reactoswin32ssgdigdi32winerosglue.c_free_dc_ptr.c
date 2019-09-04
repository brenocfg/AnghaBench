#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hdc; TYPE_3__* physDev; } ;
typedef  TYPE_2__ WINEDC ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* pDeleteDC ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ GDILoObjType_LO_ALTDC_TYPE ; 
 scalar_t__ GDILoObjType_LO_METADC16_TYPE ; 
 scalar_t__ GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdiDeleteClientObj (int /*<<< orphan*/ ) ; 
 scalar_t__ GdiGetLDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdiSetLDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NtGdiDeleteObjectApp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

VOID
free_dc_ptr(WINEDC* pWineDc)
{
    /* Invoke the DeleteDC callback to clean up the DC */
    pWineDc->physDev->funcs->pDeleteDC(pWineDc->physDev);

    /* FIXME */
    if (GDI_HANDLE_GET_TYPE(pWineDc->hdc) == GDILoObjType_LO_ALTDC_TYPE)
    {
        /* Get rid of the LDC */
        ASSERT((WINEDC*)GdiGetLDC(pWineDc->hdc) == pWineDc);
        GdiSetLDC(pWineDc->hdc, NULL);

        /* Free the DC */
        NtGdiDeleteObjectApp(pWineDc->hdc);
    }
    else if (GDI_HANDLE_GET_TYPE(pWineDc->hdc) == GDILoObjType_LO_METADC16_TYPE)
    {
        GdiDeleteClientObj(pWineDc->hdc);
    }

    /* Free the Wine DC */
    HeapFree(GetProcessHeap(), 0, pWineDc);
}