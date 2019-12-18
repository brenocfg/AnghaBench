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
struct redisCommand {int dummy; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_6__ {int numops; TYPE_2__* ops; } ;
typedef  TYPE_1__ redisOpArray ;
struct TYPE_7__ {int dbid; int argc; int target; int /*<<< orphan*/ ** argv; struct redisCommand* cmd; } ;
typedef  TYPE_2__ redisOp ;

/* Variables and functions */
 TYPE_2__* zrealloc (TYPE_2__*,int) ; 

int redisOpArrayAppend(redisOpArray *oa, struct redisCommand *cmd, int dbid,
                       robj **argv, int argc, int target)
{
    redisOp *op;

    oa->ops = zrealloc(oa->ops,sizeof(redisOp)*(oa->numops+1));
    op = oa->ops+oa->numops;
    op->cmd = cmd;
    op->dbid = dbid;
    op->argv = argv;
    op->argc = argc;
    op->target = target;
    oa->numops++;
    return oa->numops;
}