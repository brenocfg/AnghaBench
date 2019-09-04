#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int btype; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {int /*<<< orphan*/ * blocked_clients_by_type; int /*<<< orphan*/  blocked_clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_BLOCKED ; 
 TYPE_2__ server ; 

void blockClient(client *c, int btype) {
    c->flags |= CLIENT_BLOCKED;
    c->btype = btype;
    server.blocked_clients++;
    server.blocked_clients_by_type[btype]++;
}