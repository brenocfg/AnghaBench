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
struct TYPE_6__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {scalar_t__ cluster_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROPAGATE_REPL ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clusterPropagatePublish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forceCommandPropagation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pubsubPublishMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

void publishCommand(client *c) {
    int receivers = pubsubPublishMessage(c->argv[1],c->argv[2]);
    if (server.cluster_enabled)
        clusterPropagatePublish(c->argv[1],c->argv[2]);
    else
        forceCommandPropagation(c,PROPAGATE_REPL);
    addReplyLongLong(c,receivers);
}