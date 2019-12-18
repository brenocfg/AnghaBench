#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct redisCommand {int flags; int* (* getkeys_proc ) (struct redisCommand*,int /*<<< orphan*/ **,int,int*) ;} ;
typedef  int /*<<< orphan*/  robj ;

/* Variables and functions */
 int CMD_MODULE ; 
 int CMD_MODULE_GETKEYS ; 
 int* getKeysUsingCommandTable (struct redisCommand*,int /*<<< orphan*/ **,int,int*) ; 
 int* moduleGetCommandKeysViaAPI (struct redisCommand*,int /*<<< orphan*/ **,int,int*) ; 
 int* stub1 (struct redisCommand*,int /*<<< orphan*/ **,int,int*) ; 

int *getKeysFromCommand(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
    if (cmd->flags & CMD_MODULE_GETKEYS) {
        return moduleGetCommandKeysViaAPI(cmd,argv,argc,numkeys);
    } else if (!(cmd->flags & CMD_MODULE) && cmd->getkeys_proc) {
        return cmd->getkeys_proc(cmd,argv,argc,numkeys);
    } else {
        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
    }
}