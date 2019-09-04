#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  fr_c; } ;
struct TYPE_8__ {TYPE_1__* close; int /*<<< orphan*/  identifier; } ;
struct TYPE_7__ {scalar_t__ type; unsigned int number; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_CLOSE_NONE ; 
 scalar_t__ GROUPCHAT_CLOSE_ONLINE ; 
 size_t MAX_GROUP_CONNECTIONS ; 
 TYPE_2__* get_group_c (TYPE_3__*,int) ; 
 int /*<<< orphan*/  send_packet_online (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_conns_type_close(Group_Chats *g_c, int groupnumber, int friendcon_id, uint8_t type)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return;

    uint32_t i;

    for (i = 0; i < MAX_GROUP_CONNECTIONS; ++i) {
        if (g->close[i].type == GROUPCHAT_CLOSE_NONE)
            continue;

        if (g->close[i].number != (unsigned int)friendcon_id)
            continue;

        if (type == GROUPCHAT_CLOSE_ONLINE) {
            send_packet_online(g_c->fr_c, friendcon_id, groupnumber, g->identifier);
        } else {
            g->close[i].type = type;
        }
    }
}