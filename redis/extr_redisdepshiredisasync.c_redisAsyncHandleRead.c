#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_10__ {TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 int REDIS_CONNECTED ; 
 scalar_t__ REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  _EL_ADD_READ (TYPE_2__*) ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_2__*) ; 
 scalar_t__ __redisAsyncHandleConnect (TYPE_2__*) ; 
 scalar_t__ redisBufferRead (TYPE_1__*) ; 
 int /*<<< orphan*/  redisProcessCallbacks (TYPE_2__*) ; 

void redisAsyncHandleRead(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (!(c->flags & REDIS_CONNECTED)) {
        /* Abort connect was not successful. */
        if (__redisAsyncHandleConnect(ac) != REDIS_OK)
            return;
        /* Try again later when the context is still not connected. */
        if (!(c->flags & REDIS_CONNECTED))
            return;
    }

    if (redisBufferRead(c) == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        /* Always re-schedule reads */
        _EL_ADD_READ(ac);
        redisProcessCallbacks(ac);
    }
}