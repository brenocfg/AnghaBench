#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  __redisSetErrorFromErrno (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redisNetClose (TYPE_1__*) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int redisSetReuseAddr(redisContext *c) {
    int on = 1;
    if (setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        redisNetClose(c);
        return REDIS_ERR;
    }
    return REDIS_OK;
}