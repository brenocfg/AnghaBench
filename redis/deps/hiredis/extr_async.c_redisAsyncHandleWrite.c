#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; TYPE_1__* funcs; } ;
typedef  TYPE_2__ redisContext ;
struct TYPE_9__ {TYPE_2__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;
struct TYPE_7__ {int /*<<< orphan*/  (* async_write ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int REDIS_CONNECTED ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ __redisAsyncHandleConnect (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void redisAsyncHandleWrite(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (!(c->flags & REDIS_CONNECTED)) {
        /* Abort connect was not successful. */
        if (__redisAsyncHandleConnect(ac) != REDIS_OK)
            return;
        /* Try again later when the context is still not connected. */
        if (!(c->flags & REDIS_CONNECTED))
            return;
    }

    c->funcs->async_write(ac);
}