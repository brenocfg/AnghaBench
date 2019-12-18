#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_9__ {int /*<<< orphan*/ * hdc; int /*<<< orphan*/ * next; int /*<<< orphan*/ * funcs; } ;
struct TYPE_10__ {int refcount; int /*<<< orphan*/ * hdc; TYPE_1__ NullPhysDev; TYPE_1__* physDev; int /*<<< orphan*/  iType; void* hPalette; void* hPen; void* hBrush; void* hFont; } ;
typedef  TYPE_2__ WINEDC ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  DEFAULT_PALETTE ; 
 int /*<<< orphan*/  DummyPhysDevFuncs ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDILoObjType_LO_METADC16_TYPE ; 
 int /*<<< orphan*/ * GdiCreateClientObj (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdiSetLDC (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* GetStockObject (int /*<<< orphan*/ ) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LDC_EMFLDC ; 
 int /*<<< orphan*/ * NtGdiCreateMetafileDC (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJ_ENHMETADC ; 
 scalar_t__ OBJ_METADC ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

WINEDC*
alloc_dc_ptr(WORD magic)
{
    WINEDC* pWineDc;

    /* Allocate the Wine DC */
    pWineDc = HeapAlloc(GetProcessHeap(), 0, sizeof(*pWineDc));
    if (pWineDc == NULL)
    {
        return NULL;
    }

    ZeroMemory(pWineDc, sizeof(*pWineDc));
    pWineDc->refcount = 1;
    pWineDc->hFont = GetStockObject(SYSTEM_FONT);
    pWineDc->hBrush = GetStockObject(WHITE_BRUSH);
    pWineDc->hPen = GetStockObject(BLACK_PEN);
    pWineDc->hPalette = GetStockObject(DEFAULT_PALETTE);

    if (magic == OBJ_ENHMETADC)
    {
        /* We create a metafile DC, but we ignore the reference DC, this is
           handled by the wine code */
        pWineDc->hdc = NtGdiCreateMetafileDC(NULL);
        if (pWineDc->hdc == NULL)
        {
            HeapFree(GetProcessHeap(), 0, pWineDc);
            return NULL;
        }

        pWineDc->iType = LDC_EMFLDC;

        /* Set the Wine DC as LDC */
        GdiSetLDC(pWineDc->hdc, pWineDc);
    }
    else if (magic == OBJ_METADC)
    {
        pWineDc->hdc = GdiCreateClientObj(pWineDc, GDILoObjType_LO_METADC16_TYPE);
        if (pWineDc->hdc == NULL)
        {
            HeapFree(GetProcessHeap(), 0, pWineDc);
            return NULL;
        }
    }
    else
    {
        // nothing else supported!
        ASSERT(FALSE);
    }

    pWineDc->physDev = &pWineDc->NullPhysDev;
    pWineDc->NullPhysDev.funcs = &DummyPhysDevFuncs;
    pWineDc->NullPhysDev.next = NULL;

    pWineDc->NullPhysDev.hdc = pWineDc->hdc;
    return pWineDc;
}