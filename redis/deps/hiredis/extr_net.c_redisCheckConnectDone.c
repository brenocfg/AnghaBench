#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addrlen; scalar_t__ saddr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
#define  EALREADY 131 
#define  EINPROGRESS 130 
#define  EISCONN 129 
#define  EWOULDBLOCK 128 
 int REDIS_ERR ; 
 int REDIS_OK ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int errno ; 

int redisCheckConnectDone(redisContext *c, int *completed) {
    int rc = connect(c->fd, (const struct sockaddr *)c->saddr, c->addrlen);
    if (rc == 0) {
        *completed = 1;
        return REDIS_OK;
    }
    switch (errno) {
    case EISCONN:
        *completed = 1;
        return REDIS_OK;
    case EALREADY:
    case EINPROGRESS:
    case EWOULDBLOCK:
        *completed = 0;
        return REDIS_OK;
    default:
        return REDIS_ERR;
    }
}