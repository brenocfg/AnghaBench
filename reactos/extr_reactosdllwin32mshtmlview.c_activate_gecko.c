#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  window; int /*<<< orphan*/  hwnd; TYPE_1__* doc; } ;
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_2__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nsIBaseWindow_SetEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIBaseWindow_SetVisibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void activate_gecko(NSContainer *This)
{
    TRACE("(%p) %p\n", This, This->window);

    SetParent(This->hwnd, This->doc->hwnd);
    ShowWindow(This->hwnd, SW_SHOW);

    nsIBaseWindow_SetVisibility(This->window, TRUE);
    nsIBaseWindow_SetEnabled(This->window, TRUE);
}