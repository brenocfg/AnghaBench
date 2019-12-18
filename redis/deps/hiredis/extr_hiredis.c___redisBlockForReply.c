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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int REDIS_BLOCK ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ redisGetReply (TYPE_1__*,void**) ; 

__attribute__((used)) static void *__redisBlockForReply(redisContext *c) {
    void *reply;

    if (c->flags & REDIS_BLOCK) {
        if (redisGetReply(c,&reply) != REDIS_OK)
            return NULL;
        return reply;
    }
    return NULL;
}