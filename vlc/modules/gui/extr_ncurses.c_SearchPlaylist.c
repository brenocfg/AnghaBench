#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {char* search_chain; int box_idx; TYPE_1__ pl_item_names; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CheckIdx (TYPE_2__*) ; 
 int SubSearchPlaylist (TYPE_2__*,char*,int,int) ; 

__attribute__((used)) static void SearchPlaylist(intf_sys_t *sys)
{
    char *str = sys->search_chain;
    int i_first = sys->box_idx;
    if (i_first < 0)
        i_first = 0;

    if (!str || !*str)
        return;

    int i_item = SubSearchPlaylist(sys, str, i_first + 1,
                                   sys->pl_item_names.size);
    if (i_item < 0)
        i_item = SubSearchPlaylist(sys, str, 0, i_first);

    if (i_item > 0) {
        sys->box_idx = i_item;
        CheckIdx(sys);
    }
}