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
struct TYPE_5__ {char* masterhost; int /*<<< orphan*/  second_replid_offset; int /*<<< orphan*/  master_repl_offset; int /*<<< orphan*/  replid2; int /*<<< orphan*/  replid; int /*<<< orphan*/  masterport; } ;
struct TYPE_4__ {int version; char* masterhost; int /*<<< orphan*/  repl2_offset; int /*<<< orphan*/  repl1_offset; int /*<<< orphan*/  replid2; int /*<<< orphan*/  replid1; int /*<<< orphan*/  masterport; int /*<<< orphan*/  master; } ;
typedef  TYPE_1__ RedisModuleReplicationInfoV1 ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ server ; 

int modulePopulateReplicationInfoStructure(void *ri, int structver) {
    if (structver != 1) return REDISMODULE_ERR;

    RedisModuleReplicationInfoV1 *ri1 = ri;
    memset(ri1,0,sizeof(*ri1));
    ri1->version = structver;
    ri1->master = server.masterhost==NULL;
    ri1->masterhost = server.masterhost? server.masterhost: "";
    ri1->masterport = server.masterport;
    ri1->replid1 = server.replid;
    ri1->replid2 = server.replid2;
    ri1->repl1_offset = server.master_repl_offset;
    ri1->repl2_offset = server.second_replid_offset;
    return REDISMODULE_OK;
}