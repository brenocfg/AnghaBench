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
struct TYPE_4__ {struct TYPE_4__* parent; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
TREEVIEW_IsChildOf(const TREEVIEW_ITEM *parent, const TREEVIEW_ITEM *child)
{
    do
    {
	child = child->parent;
	if (child == parent) return TRUE;
    } while (child != NULL);

    return FALSE;
}