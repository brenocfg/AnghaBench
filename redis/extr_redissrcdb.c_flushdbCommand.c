#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_10__ {int /*<<< orphan*/  ok; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ emptyDb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ getFlushCommandFlags (TYPE_2__*,int*) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalFlushedDb (int /*<<< orphan*/ ) ; 

void flushdbCommand(client *c) {
    int flags;

    if (getFlushCommandFlags(c,&flags) == C_ERR) return;
    signalFlushedDb(c->db->id);
    server.dirty += emptyDb(c->db->id,flags,NULL);
    addReply(c,shared.ok);
}