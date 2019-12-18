#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ module_id; struct TYPE_7__* next; int /*<<< orphan*/  (* callback ) (TYPE_2__*,char const*,size_t,unsigned char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ moduleClusterReceiver ;
struct TYPE_8__ {int /*<<< orphan*/  client; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 TYPE_2__ REDISMODULE_CTX_INIT ; 
 TYPE_1__** clusterReceivers ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_2__*) ; 
 int /*<<< orphan*/  moduleFreeContextReusedClient ; 
 int /*<<< orphan*/  selectDb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,size_t,unsigned char const*,int /*<<< orphan*/ ) ; 

void moduleCallClusterReceivers(const char *sender_id, uint64_t module_id, uint8_t type, const unsigned char *payload, uint32_t len) {
    moduleClusterReceiver *r = clusterReceivers[type];
    while(r) {
        if (r->module_id == module_id) {
            RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
            ctx.module = r->module;
            ctx.client = moduleFreeContextReusedClient;
            selectDb(ctx.client, 0);
            r->callback(&ctx,sender_id,type,payload,len);
            moduleFreeContext(&ctx);
            return;
        }
        r = r->next;
    }
}