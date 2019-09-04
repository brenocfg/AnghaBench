#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int /*<<< orphan*/  clients_waiting_acks; } ;

/* Variables and functions */
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 

void unblockClientWaitingReplicas(client *c) {
    listNode *ln = listSearchKey(server.clients_waiting_acks,c);
    serverAssert(ln != NULL);
    listDelNode(server.clients_waiting_acks,ln);
}