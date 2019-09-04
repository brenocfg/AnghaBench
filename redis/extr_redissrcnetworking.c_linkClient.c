#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  client_list_node; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  clients_index; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  listLast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

void linkClient(client *c) {
    listAddNodeTail(server.clients,c);
    /* Note that we remember the linked list node where the client is stored,
     * this way removing the client in unlinkClient() will not require
     * a linear scan, but just a constant time operation. */
    c->client_list_node = listLast(server.clients);
    uint64_t id = htonu64(c->id);
    raxInsert(server.clients_index,(unsigned char*)&id,sizeof(id),c,NULL);
}