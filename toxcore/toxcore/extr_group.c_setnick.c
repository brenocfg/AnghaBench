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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  group_namelistchange_userdata; int /*<<< orphan*/  m; int /*<<< orphan*/  (* peer_namelistchange ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__* group; } ;
struct TYPE_7__ {int /*<<< orphan*/  nick_len; int /*<<< orphan*/  nick; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  CHAT_CHANGE_PEER_NAME ; 
 int /*<<< orphan*/  MAX_NAME_LENGTH ; 
 TYPE_2__* get_group_c (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setnick(Group_Chats *g_c, int groupnumber, int peer_index, const uint8_t *nick, uint16_t nick_len)
{
    if (nick_len > MAX_NAME_LENGTH)
        return -1;

    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    /* same name as already stored? */
    if (g->group[peer_index].nick_len == nick_len)
        if (nick_len == 0 || !memcmp(g->group[peer_index].nick, nick, nick_len))
            return 0;

    if (nick_len)
        memcpy(g->group[peer_index].nick, nick, nick_len);

    g->group[peer_index].nick_len = nick_len;

    if (g_c->peer_namelistchange)
        g_c->peer_namelistchange(g_c->m, groupnumber, peer_index, CHAT_CHANGE_PEER_NAME, g_c->group_namelistchange_userdata);

    return 0;
}