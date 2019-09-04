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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ TVHITTESTINFO ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ TREEVIEW_IsFullRowSelect (int /*<<< orphan*/  const*) ; 
 int TVHT_ONITEM ; 
 int TVHT_ONITEMBUTTON ; 
 int TVHT_ONITEMINDENT ; 
 int TVHT_ONITEMRIGHT ; 

__attribute__((used)) static BOOL
TREEVIEW_IsItemHit(const TREEVIEW_INFO *infoPtr, const TVHITTESTINFO *ht)
{
    if (TREEVIEW_IsFullRowSelect(infoPtr))
        return ht->flags & (TVHT_ONITEMINDENT | TVHT_ONITEMBUTTON | TVHT_ONITEM | TVHT_ONITEMRIGHT);
    else
        return ht->flags & TVHT_ONITEM;
}