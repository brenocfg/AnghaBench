#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int Left; int Right; int Top; int Bottom; } ;
typedef  TYPE_1__ SMALL_RECT ;
typedef  TYPE_1__* PSMALL_RECT ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 scalar_t__ DoubleHeight ; 
 scalar_t__ DoubleWidth ; 
 scalar_t__ GRAPHICS_MODE ; 
 int /*<<< orphan*/ * GraphicsConsoleBuffer ; 
 scalar_t__ ScreenMode ; 
 int /*<<< orphan*/ * TextConsoleBuffer ; 
 int /*<<< orphan*/  __InvalidateConsoleDIBits (int /*<<< orphan*/ *,TYPE_1__*) ; 

VOID VgaConsoleRepaintScreen(PSMALL_RECT Rect)
{
    HANDLE ConsoleBufferHandle = NULL;
    SMALL_RECT UpdateRectangle = *Rect;

    /* Check if we are in text or graphics mode */
    if (ScreenMode == GRAPHICS_MODE)
    {
        /* Graphics mode */
        ConsoleBufferHandle = GraphicsConsoleBuffer;

        /* In DoubleVision mode, scale the update rectangle */
        if (DoubleWidth)
        {
            UpdateRectangle.Left *= 2;
            UpdateRectangle.Right = UpdateRectangle.Right * 2 + 1;
        }
        if (DoubleHeight)
        {
            UpdateRectangle.Top *= 2;
            UpdateRectangle.Bottom = UpdateRectangle.Bottom * 2 + 1;
        }
    }
    else
    {
        /* Text mode */
        ConsoleBufferHandle = TextConsoleBuffer;
    }

    /* Redraw the screen */
    __InvalidateConsoleDIBits(ConsoleBufferHandle, &UpdateRectangle);
}