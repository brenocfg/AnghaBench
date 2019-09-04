#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* Peb; } ;
struct TYPE_10__ {struct TYPE_10__* pPoolRgnAttr; struct TYPE_10__* pPoolBrushAttr; struct TYPE_10__* pPoolDcAttr; int /*<<< orphan*/  GDIDcAttrFreeList; int /*<<< orphan*/  GDIBrushAttrFreeList; int /*<<< orphan*/  PrivateFontListLock; scalar_t__ PrivateMemFontHandleCount; int /*<<< orphan*/  PrivateMemFontListHead; int /*<<< orphan*/  PrivateFontListHead; } ;
struct TYPE_9__ {int /*<<< orphan*/  GdiDCAttributeList; int /*<<< orphan*/  GdiSharedHandleTable; } ;
typedef  int /*<<< orphan*/  RGN_ATTR ;
typedef  TYPE_2__* PPROCESSINFO ;
typedef  TYPE_3__* PEPROCESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DC_ATTR ;
typedef  int /*<<< orphan*/  BRUSH_ATTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  ExInitializeFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GDI_BATCH_LIMIT ; 
 int /*<<< orphan*/  GDI_MapHandleTable (TYPE_3__*) ; 
 void* GdiPoolCreate (int,char) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 TYPE_2__* PsGetProcessWin32Process (TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
GdiProcessCreate(PEPROCESS Process)
{
    PPROCESSINFO ppiCurrent = PsGetProcessWin32Process(Process);
    ASSERT(ppiCurrent);

    InitializeListHead(&ppiCurrent->PrivateFontListHead);
    InitializeListHead(&ppiCurrent->PrivateMemFontListHead);
    ppiCurrent->PrivateMemFontHandleCount = 0;
    ExInitializeFastMutex(&ppiCurrent->PrivateFontListLock);

    InitializeListHead(&ppiCurrent->GDIBrushAttrFreeList);
    InitializeListHead(&ppiCurrent->GDIDcAttrFreeList);

    /* Map the GDI handle table to user land */
    Process->Peb->GdiSharedHandleTable = GDI_MapHandleTable(Process);
    Process->Peb->GdiDCAttributeList = GDI_BATCH_LIMIT;

    /* Create pools for GDI object attributes */
    ppiCurrent->pPoolDcAttr = GdiPoolCreate(sizeof(DC_ATTR), 'acdG');
    ppiCurrent->pPoolBrushAttr = GdiPoolCreate(sizeof(BRUSH_ATTR), 'arbG');
    ppiCurrent->pPoolRgnAttr = GdiPoolCreate(sizeof(RGN_ATTR), 'agrG');
    ASSERT(ppiCurrent->pPoolDcAttr);
    ASSERT(ppiCurrent->pPoolBrushAttr);
    ASSERT(ppiCurrent->pPoolRgnAttr);

    return STATUS_SUCCESS;
}