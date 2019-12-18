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
struct TYPE_4__ {int flags; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ EWOULDBLOCK ; 
 int REDIS_BLOCK ; 
 int /*<<< orphan*/  REDIS_ERR_EOF ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int /*<<< orphan*/  REDIS_ERR_TIMEOUT ; 
 int /*<<< orphan*/  __redisSetError (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int recv (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

int redisNetRead(redisContext *c, char *buf, size_t bufcap) {
    int nread = recv(c->fd, buf, bufcap, 0);
    if (nread == -1) {
        if ((errno == EWOULDBLOCK && !(c->flags & REDIS_BLOCK)) || (errno == EINTR)) {
            /* Try again later */
            return 0;
        } else if(errno == ETIMEDOUT && (c->flags & REDIS_BLOCK)) {
            /* especially in windows */
            __redisSetError(c, REDIS_ERR_TIMEOUT, "recv timeout");
            return -1;
        } else {
            __redisSetError(c, REDIS_ERR_IO, NULL);
            return -1;
        }
    } else if (nread == 0) {
        __redisSetError(c, REDIS_ERR_EOF, "Server closed the connection");
        return -1;
    } else {
        return nread;
    }
}