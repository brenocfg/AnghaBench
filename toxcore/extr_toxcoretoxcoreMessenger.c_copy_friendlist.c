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
typedef  size_t uint32_t ;
struct TYPE_5__ {scalar_t__ numfriends; TYPE_1__* friendlist; } ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */

uint32_t copy_friendlist(Messenger const *m, uint32_t *out_list, uint32_t list_size)
{
    if (!out_list)
        return 0;

    if (m->numfriends == 0) {
        return 0;
    }

    uint32_t i;
    uint32_t ret = 0;

    for (i = 0; i < m->numfriends; i++) {
        if (ret >= list_size) {
            break; /* Abandon ship */
        }

        if (m->friendlist[i].status > 0) {
            out_list[ret] = i;
            ret++;
        }
    }

    return ret;
}