#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_3__ {int /*<<< orphan*/ ** Font; } ;
typedef  TYPE_1__* PGUI_CONSOLE_DATA ;

/* Variables and functions */
 size_t ARRAYSIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 

VOID
DeleteFonts(PGUI_CONSOLE_DATA GuiData)
{
    ULONG i;
    for (i = 0; i < ARRAYSIZE(GuiData->Font); ++i)
    {
        if (GuiData->Font[i] != NULL) DeleteObject(GuiData->Font[i]);
        GuiData->Font[i] = NULL;
    }
}