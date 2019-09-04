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
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {int /*<<< orphan*/  clients_to_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_CLOSE_ASAP ; 
 int /*<<< orphan*/  freeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

void freeClientsInAsyncFreeQueue(void) {
    while (listLength(server.clients_to_close)) {
        listNode *ln = listFirst(server.clients_to_close);
        client *c = listNodeValue(ln);

        c->flags &= ~CLIENT_CLOSE_ASAP;
        freeClient(c);
        listDelNode(server.clients_to_close,ln);
    }
}