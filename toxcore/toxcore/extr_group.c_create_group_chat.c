#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {size_t num_chats; TYPE_3__* chats; } ;
typedef  int /*<<< orphan*/  Group_c ;
typedef  TYPE_1__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_STATUS_NONE ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc_groupchats (TYPE_1__*,int) ; 

__attribute__((used)) static int create_group_chat(Group_Chats *g_c)
{
    uint32_t i;

    for (i = 0; i < g_c->num_chats; ++i) {
        if (g_c->chats[i].status == GROUPCHAT_STATUS_NONE)
            return i;
    }

    int id = -1;

    if (realloc_groupchats(g_c, g_c->num_chats + 1) == 0) {
        id = g_c->num_chats;
        ++g_c->num_chats;
        memset(&(g_c->chats[id]), 0, sizeof(Group_c));
    }

    return id;
}