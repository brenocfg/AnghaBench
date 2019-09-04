#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_4__ {int /*<<< orphan*/ * obuf; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OOM ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  __redisSetError (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sdscatlen (int /*<<< orphan*/ *,char const*,size_t) ; 

int __redisAppendCommand(redisContext *c, const char *cmd, size_t len) {
    sds newbuf;

    newbuf = sdscatlen(c->obuf,cmd,len);
    if (newbuf == NULL) {
        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
        return REDIS_ERR;
    }

    c->obuf = newbuf;
    return REDIS_OK;
}