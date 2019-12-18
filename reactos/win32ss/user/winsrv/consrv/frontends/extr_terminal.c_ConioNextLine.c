#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {scalar_t__ Top; scalar_t__ Bottom; scalar_t__ Right; scalar_t__ Left; } ;
struct TYPE_8__ {scalar_t__ Y; } ;
struct TYPE_9__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_10__ {scalar_t__ VirtualY; TYPE_1__ CursorPosition; TYPE_2__ ScreenBufferSize; } ;
typedef  int /*<<< orphan*/ * PUINT ;
typedef  TYPE_3__* PTEXTMODE_SCREEN_BUFFER ;
typedef  TYPE_4__* PSMALL_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  ClearLineBuffer (TYPE_3__*) ; 

__attribute__((used)) static VOID
ConioNextLine(PTEXTMODE_SCREEN_BUFFER Buff, PSMALL_RECT UpdateRect, PUINT ScrolledLines)
{
    /* If we hit bottom, slide the viewable screen */
    if (++Buff->CursorPosition.Y == Buff->ScreenBufferSize.Y)
    {
        Buff->CursorPosition.Y--;
        if (++Buff->VirtualY == Buff->ScreenBufferSize.Y)
        {
            Buff->VirtualY = 0;
        }
        (*ScrolledLines)++;
        ClearLineBuffer(Buff);
        if (UpdateRect->Top != 0)
        {
            UpdateRect->Top--;
        }
    }
    UpdateRect->Left = 0;
    UpdateRect->Right = Buff->ScreenBufferSize.X - 1;
    UpdateRect->Bottom = Buff->CursorPosition.Y;
}