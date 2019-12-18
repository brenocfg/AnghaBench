#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* socket; } ;
struct TYPE_9__ {int /*<<< orphan*/  peers_by_address; } ;
typedef  TYPE_2__ SocketPeer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static SocketPeer *socket_peer_free(SocketPeer *p) {
        assert(p);

        if (p->socket)
                set_remove(p->socket->peers_by_address, p);

        return mfree(p);
}