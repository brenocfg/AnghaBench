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
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; scalar_t__ hwndNotify; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GW_OWNER ; 
 scalar_t__ GetParent (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HWND
REBAR_GetNotifyParent (const REBAR_INFO *infoPtr)
{
    HWND parent, owner;

    parent = infoPtr->hwndNotify;
    if (!parent) {
        parent = GetParent (infoPtr->hwndSelf);
	owner = GetWindow (infoPtr->hwndSelf, GW_OWNER);
	if (owner) parent = owner;
    }
    return parent;
}