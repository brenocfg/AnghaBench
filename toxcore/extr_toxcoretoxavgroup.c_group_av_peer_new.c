#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  g_c; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Group_Peer_AV ;
typedef  TYPE_2__ Group_AV ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_JBUF_SIZE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  create_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_peer_set_object (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 

__attribute__((used)) static void group_av_peer_new(void *object, int groupnumber, int friendgroupnumber)
{
    Group_AV *group_av = object;
    Group_Peer_AV *peer_av = calloc(1, sizeof(Group_Peer_AV));

    if (!peer_av)
        return;

    peer_av->buffer = create_queue(GROUP_JBUF_SIZE);
    group_peer_set_object(group_av->g_c, groupnumber, friendgroupnumber, peer_av);
}