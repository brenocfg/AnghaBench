#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ module_id; struct TYPE_10__* next; void* callback; TYPE_1__* module; } ;
typedef  TYPE_2__ moduleClusterReceiver ;
struct TYPE_12__ {int /*<<< orphan*/  cluster_enabled; } ;
struct TYPE_11__ {TYPE_1__* module; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  void* RedisModuleClusterMessageReceiver ;

/* Variables and functions */
 TYPE_2__** clusterReceivers ; 
 scalar_t__ moduleTypeEncodeId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 TYPE_2__* zmalloc (int) ; 

void RM_RegisterClusterMessageReceiver(RedisModuleCtx *ctx, uint8_t type, RedisModuleClusterMessageReceiver callback) {
    if (!server.cluster_enabled) return;

    uint64_t module_id = moduleTypeEncodeId(ctx->module->name,0);
    moduleClusterReceiver *r = clusterReceivers[type], *prev = NULL;
    while(r) {
        if (r->module_id == module_id) {
            /* Found! Set or delete. */
            if (callback) {
                r->callback = callback;
            } else {
                /* Delete the receiver entry if the user is setting
                 * it to NULL. Just unlink the receiver node from the
                 * linked list. */
                if (prev)
                    prev->next = r->next;
                else
                    clusterReceivers[type]->next = r->next;
                zfree(r);
            }
            return;
        }
        prev = r;
        r = r->next;
    }

    /* Not found, let's add it. */
    if (callback) {
        r = zmalloc(sizeof(*r));
        r->module_id = module_id;
        r->module = ctx->module;
        r->callback = callback;
        r->next = clusterReceivers[type];
        clusterReceivers[type] = r;
    }
}