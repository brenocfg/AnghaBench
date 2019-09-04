#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {TYPE_3__* m; TYPE_4__* chats; } ;
struct TYPE_13__ {int number_joined; int /*<<< orphan*/  real_pk; scalar_t__ peer_number; int /*<<< orphan*/ * identifier; int /*<<< orphan*/  status; } ;
struct TYPE_12__ {int /*<<< orphan*/  name_length; int /*<<< orphan*/  name; TYPE_2__* dht; TYPE_1__* net_crypto; } ;
struct TYPE_11__ {int /*<<< orphan*/  self_public_key; } ;
struct TYPE_10__ {int /*<<< orphan*/  self_public_key; } ;
typedef  TYPE_4__ Group_c ;
typedef  TYPE_5__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPCHAT_STATUS_CONNECTED ; 
 int addpeer (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int create_group_chat (TYPE_5__*) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnick (TYPE_5__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int add_groupchat(Group_Chats *g_c, uint8_t type)
{
    int groupnumber = create_group_chat(g_c);

    if (groupnumber == -1)
        return -1;

    Group_c *g = &g_c->chats[groupnumber];

    g->status = GROUPCHAT_STATUS_CONNECTED;
    g->number_joined = -1;
    new_symmetric_key(g->identifier + 1);
    g->identifier[0] = type;
    g->peer_number = 0; /* Founder is peer 0. */
    memcpy(g->real_pk, g_c->m->net_crypto->self_public_key, crypto_box_PUBLICKEYBYTES);
    int peer_index = addpeer(g_c, groupnumber, g->real_pk, g_c->m->dht->self_public_key, 0);

    if (peer_index == -1) {
        return -1;
    }

    setnick(g_c, groupnumber, peer_index, g_c->m->name, g_c->m->name_length);

    return groupnumber;
}