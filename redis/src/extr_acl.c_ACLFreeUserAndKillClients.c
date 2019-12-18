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
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_5__ {scalar_t__ authenticated; int /*<<< orphan*/ * user; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLFreeUser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DefaultUser ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_1__*) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

void ACLFreeUserAndKillClients(user *u) {
    listIter li;
    listNode *ln;
    listRewind(server.clients,&li);
    while ((ln = listNext(&li)) != NULL) {
        client *c = listNodeValue(ln);
        if (c->user == u) {
            /* We'll free the conenction asynchronously, so
             * in theory to set a different user is not needed.
             * However if there are bugs in Redis, soon or later
             * this may result in some security hole: it's much
             * more defensive to set the default user and put
             * it in non authenticated mode. */
            c->user = DefaultUser;
            c->authenticated = 0;
            freeClientAsync(c);
        }
    }
    ACLFreeUser(u);
}