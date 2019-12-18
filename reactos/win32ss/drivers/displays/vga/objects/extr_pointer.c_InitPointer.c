#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VIDEO_POINTER_ATTRIBUTES ;
typedef  int ULONG ;
struct TYPE_7__ {int Width; int Height; int WidthInBytes; scalar_t__ Row; scalar_t__ Column; scalar_t__ Enable; scalar_t__ Flags; } ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {int /*<<< orphan*/  ImageBehindCursor; TYPE_4__* pPointerAttributes; TYPE_1__ xyHotSpot; } ;
typedef  TYPE_2__* PPDEV ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 TYPE_4__* EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VGADDI_AllocSavedScreenBits (int) ; 

BOOL InitPointer(PPDEV ppdev)
{
    ULONG CursorWidth = 32, CursorHeight = 32;
    ULONG PointerAttributesSize;
    ULONG SavedMemSize;

    ppdev->xyHotSpot.x = 0;
    ppdev->xyHotSpot.y = 0;

    /* Determine the size of the pointer attributes */
    PointerAttributesSize = sizeof(VIDEO_POINTER_ATTRIBUTES) +
      ((CursorWidth * CursorHeight * 2) >> 3);

    /* Allocate memory for pointer attributes */
    ppdev->pPointerAttributes = EngAllocMem(0, PointerAttributesSize, ALLOC_TAG);

    ppdev->pPointerAttributes->Flags = 0; /* FIXME: Do this right */
    ppdev->pPointerAttributes->Width = CursorWidth;
    ppdev->pPointerAttributes->Height = CursorHeight;
    ppdev->pPointerAttributes->WidthInBytes = CursorWidth >> 3;
    ppdev->pPointerAttributes->Enable = 0;
    ppdev->pPointerAttributes->Column = 0;
    ppdev->pPointerAttributes->Row = 0;

    /* Allocate memory for the pixels behind the cursor */
    SavedMemSize = ((((CursorWidth + 7) & ~0x7) + 16) * CursorHeight) >> 3;
    ppdev->ImageBehindCursor = VGADDI_AllocSavedScreenBits(SavedMemSize);

    return TRUE;
}