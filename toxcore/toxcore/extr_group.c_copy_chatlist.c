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
typedef  size_t int32_t ;
struct TYPE_5__ {scalar_t__ num_chats; TYPE_1__* chats; } ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_2__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_STATUS_NONE ; 

uint32_t copy_chatlist(Group_Chats *g_c, int32_t *out_list, uint32_t list_size)
{
    if (!out_list) {
        return 0;
    }

    if (g_c->num_chats == 0) {
        return 0;
    }

    uint32_t i, ret = 0;

    for (i = 0; i < g_c->num_chats; ++i) {
        if (ret >= list_size) {
            break;  /* Abandon ship */
        }

        if (g_c->chats[i].status > GROUPCHAT_STATUS_NONE) {
            out_list[ret] = i;
            ret++;
        }
    }

    return ret;
}