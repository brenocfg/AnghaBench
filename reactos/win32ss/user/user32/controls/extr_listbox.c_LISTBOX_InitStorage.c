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
struct TYPE_4__ {int /*<<< orphan*/ * items; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LB_ITEMDATA ;
typedef  TYPE_1__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LBN_ERRSPACE ; 
 int LB_ARRAY_GRANULARITY ; 
 int /*<<< orphan*/  LB_ERRSPACE ; 
 int /*<<< orphan*/  LB_OKAY ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT LISTBOX_InitStorage( LB_DESCR *descr, INT nb_items )
{
    LB_ITEMDATA *item;

    nb_items += LB_ARRAY_GRANULARITY - 1;
    nb_items -= (nb_items % LB_ARRAY_GRANULARITY);
    if (descr->items) {
        nb_items += HeapSize( GetProcessHeap(), 0, descr->items ) / sizeof(*item);
	item = HeapReAlloc( GetProcessHeap(), 0, descr->items,
                              nb_items * sizeof(LB_ITEMDATA));
    }
    else {
	item = HeapAlloc( GetProcessHeap(), 0,
                              nb_items * sizeof(LB_ITEMDATA));
    }

    if (!item)
    {
        SEND_NOTIFICATION( descr, LBN_ERRSPACE );
        return LB_ERRSPACE;
    }
    descr->items = item;
    return LB_OKAY;
}