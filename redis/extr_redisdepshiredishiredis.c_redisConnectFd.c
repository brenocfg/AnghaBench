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
struct TYPE_4__ {int fd; int flags; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int REDIS_BLOCK ; 
 int REDIS_CONNECTED ; 
 TYPE_1__* redisContextInit () ; 

redisContext *redisConnectFd(int fd) {
    redisContext *c;

    c = redisContextInit();
    if (c == NULL)
        return NULL;

    c->fd = fd;
    c->flags |= REDIS_BLOCK | REDIS_CONNECTED;
    return c;
}