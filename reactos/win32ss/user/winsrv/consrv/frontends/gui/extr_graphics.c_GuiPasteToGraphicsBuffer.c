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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  PGRAPHICS_SCREEN_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  UNIMPLEMENTED ; 

VOID
GuiPasteToGraphicsBuffer(PGRAPHICS_SCREEN_BUFFER Buffer,
                         PGUI_CONSOLE_DATA GuiData)
{
    /*
     * This function supposes that the system clipboard was opened.
     */

    // PCONSRV_CONSOLE Console = Buffer->Header.Console;

    UNIMPLEMENTED;
}