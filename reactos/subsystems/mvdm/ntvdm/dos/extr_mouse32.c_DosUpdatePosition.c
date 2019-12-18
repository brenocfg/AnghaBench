#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ ShowCount; int /*<<< orphan*/  Position; } ;
struct TYPE_4__ {int X; int Y; } ;
typedef  int /*<<< orphan*/ * PCOORD ;
typedef  TYPE_1__ COORD ;

/* Variables and functions */
 int /*<<< orphan*/  CallMouseUserHandlers (int) ; 
 TYPE_3__ DriverState ; 
 int /*<<< orphan*/  EraseMouseCursor () ; 
 int /*<<< orphan*/  PaintMouseCursor () ; 
 TYPE_1__ VgaGetDisplayResolution () ; 
 int /*<<< orphan*/  VgaGetDoubleVisionState (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline VOID DosUpdatePosition(PCOORD NewPosition)
{
    COORD Resolution = VgaGetDisplayResolution();

    /* Check for text mode */
    if (!VgaGetDoubleVisionState(NULL, NULL))
    {
        Resolution.X *= 8;
        Resolution.Y *= 8;
    }

    if (DriverState.ShowCount > 0) EraseMouseCursor();
    DriverState.Position = *NewPosition;
    if (DriverState.ShowCount > 0) PaintMouseCursor();

    /* Call the mouse handlers */
    CallMouseUserHandlers(0x0001); // We use MS MOUSE v1.0+ format
}