#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  group_namelistchange_userdata; int /*<<< orphan*/  m; int /*<<< orphan*/  (* peer_namelistchange ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fr_c; } ;
struct TYPE_16__ {void* object; int /*<<< orphan*/  real_pk; } ;
struct TYPE_15__ {size_t numpeers; int /*<<< orphan*/  object; int /*<<< orphan*/  (* peer_on_leave ) (int /*<<< orphan*/ ,int,int,void*) ;TYPE_3__* group; int /*<<< orphan*/  changed; TYPE_1__* closest_peers; } ;
struct TYPE_14__ {scalar_t__ entry; int /*<<< orphan*/  real_pk; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Peer ;
typedef  TYPE_4__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  CHAT_CHANGE_PEER_DEL ; 
 size_t DESIRED_CLOSE_CONNECTIONS ; 
 int /*<<< orphan*/  GROUPCHAT_CLOSEST_REMOVED ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_2__* get_group_c (TYPE_4__*,int) ; 
 int getfriend_conn_id_pk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* realloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  remove_close_conn (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int,void*) ; 

__attribute__((used)) static int delpeer(Group_Chats *g_c, int groupnumber, int peer_index)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    uint32_t i;

    for (i = 0; i < DESIRED_CLOSE_CONNECTIONS; ++i) { /* If peer is in closest_peers list, remove it. */
        if (g->closest_peers[i].entry && id_equal(g->closest_peers[i].real_pk, g->group[peer_index].real_pk)) {
            g->closest_peers[i].entry = 0;
            g->changed = GROUPCHAT_CLOSEST_REMOVED;
            break;
        }
    }

    int friendcon_id = getfriend_conn_id_pk(g_c->fr_c, g->group[peer_index].real_pk);

    if (friendcon_id != -1) {
        remove_close_conn(g_c, groupnumber, friendcon_id);
    }

    Group_Peer *temp;
    --g->numpeers;

    void *peer_object = g->group[peer_index].object;

    if (g->numpeers == 0) {
        free(g->group);
        g->group = NULL;
    } else {
        if (g->numpeers != (uint32_t)peer_index)
            memcpy(&g->group[peer_index], &g->group[g->numpeers], sizeof(Group_Peer));

        temp = realloc(g->group, sizeof(Group_Peer) * (g->numpeers));

        if (temp == NULL)
            return -1;

        g->group = temp;
    }

    if (g_c->peer_namelistchange)
        g_c->peer_namelistchange(g_c->m, groupnumber, peer_index, CHAT_CHANGE_PEER_DEL, g_c->group_namelistchange_userdata);

    if (g->peer_on_leave)
        g->peer_on_leave(g->object, groupnumber, peer_index, peer_object);

    return 0;
}