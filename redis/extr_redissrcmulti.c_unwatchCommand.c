#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DIRTY_CAS ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  unwatchAllKeys (TYPE_1__*) ; 

void unwatchCommand(client *c) {
    unwatchAllKeys(c);
    c->flags &= (~CLIENT_DIRTY_CAS);
    addReply(c,shared.ok);
}