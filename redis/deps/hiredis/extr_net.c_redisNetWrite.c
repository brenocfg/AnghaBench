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
struct TYPE_4__ {int flags; int /*<<< orphan*/  obuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int REDIS_BLOCK ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int /*<<< orphan*/  __redisSetError (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int redisNetWrite(redisContext *c) {
    int nwritten = send(c->fd, c->obuf, sdslen(c->obuf), 0);
    if (nwritten < 0) {
        if ((errno == EWOULDBLOCK && !(c->flags & REDIS_BLOCK)) || (errno == EINTR)) {
            /* Try again later */
        } else {
            __redisSetError(c, REDIS_ERR_IO, NULL);
            return -1;
        }
    }
    return nwritten;
}