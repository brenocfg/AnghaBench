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
struct TYPE_3__ {scalar_t__ hWindow; int /*<<< orphan*/ * Console; } ;
typedef  TYPE_1__* PGUI_CONSOLE_DATA ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PGUI_CONSOLE_DATA
GuiGetGuiData(HWND hWnd)
{
    /* This function ensures that the console pointer is not NULL */
    PGUI_CONSOLE_DATA GuiData = (PGUI_CONSOLE_DATA)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    return ( ((GuiData == NULL) || (GuiData->hWindow == hWnd && GuiData->Console != NULL)) ? GuiData : NULL );
}