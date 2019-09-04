#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* label; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ cctrl_item ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void item_free(cctrl_item *item)
{
    DestroyWindow(item->hwnd);
    HeapFree(GetProcessHeap(), 0, item->label);
    HeapFree(GetProcessHeap(), 0, item);
}