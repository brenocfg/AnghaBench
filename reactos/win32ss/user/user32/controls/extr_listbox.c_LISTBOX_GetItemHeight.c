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
struct TYPE_5__ {int style; scalar_t__ nb_items; int /*<<< orphan*/  item_height; TYPE_1__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_INDEX ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int /*<<< orphan*/  LB_ERR ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT LISTBOX_GetItemHeight( const LB_DESCR *descr, INT index )
{
    if (descr->style & LBS_OWNERDRAWVARIABLE && descr->nb_items > 0)
    {
        if ((index < 0) || (index >= descr->nb_items))
        {
            SetLastError(ERROR_INVALID_INDEX);
            return LB_ERR;
        }
        return descr->items[index].height;
    }
    else return descr->item_height;
}