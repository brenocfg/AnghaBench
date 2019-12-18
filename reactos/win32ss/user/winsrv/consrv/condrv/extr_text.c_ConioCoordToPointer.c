#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {size_t Y; size_t X; } ;
struct TYPE_5__ {size_t VirtualY; TYPE_1__ ScreenBufferSize; int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_2__* PTEXTMODE_SCREEN_BUFFER ;
typedef  int /*<<< orphan*/ * PCHAR_INFO ;

/* Variables and functions */

PCHAR_INFO
ConioCoordToPointer(PTEXTMODE_SCREEN_BUFFER Buff, ULONG X, ULONG Y)
{
    return &Buff->Buffer[((Y + Buff->VirtualY) % Buff->ScreenBufferSize.Y) * Buff->ScreenBufferSize.X + X];
}