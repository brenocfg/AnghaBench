#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  source_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_13__ {scalar_t__ fd; int /*<<< orphan*/  unix_socket; TYPE_1__ tcp; } ;
struct TYPE_14__ {int options; scalar_t__ type; int /*<<< orphan*/ * timeout; TYPE_2__ endpoint; } ;
typedef  TYPE_3__ redisOptions ;
struct TYPE_15__ {int flags; scalar_t__ fd; } ;
typedef  TYPE_4__ redisContext ;

/* Variables and functions */
 int REDIS_BLOCK ; 
 int REDIS_CONNECTED ; 
 scalar_t__ REDIS_CONN_TCP ; 
 scalar_t__ REDIS_CONN_UNIX ; 
 scalar_t__ REDIS_CONN_USERFD ; 
 scalar_t__ REDIS_INVALID_FD ; 
 int REDIS_NO_AUTO_FREE ; 
 int REDIS_OPT_NOAUTOFREE ; 
 int REDIS_OPT_NONBLOCK ; 
 int REDIS_OPT_REUSEADDR ; 
 int REDIS_REUSEADDR ; 
 int /*<<< orphan*/  redisContextConnectBindTcp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisContextConnectUnix (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* redisContextInit (TYPE_3__ const*) ; 
 int /*<<< orphan*/  redisContextSetTimeout (TYPE_4__*,int /*<<< orphan*/ ) ; 

redisContext *redisConnectWithOptions(const redisOptions *options) {
    redisContext *c = redisContextInit(options);
    if (c == NULL) {
        return NULL;
    }
    if (!(options->options & REDIS_OPT_NONBLOCK)) {
        c->flags |= REDIS_BLOCK;
    }
    if (options->options & REDIS_OPT_REUSEADDR) {
        c->flags |= REDIS_REUSEADDR;
    }
    if (options->options & REDIS_OPT_NOAUTOFREE) {
      c->flags |= REDIS_NO_AUTO_FREE;
    }

    if (options->type == REDIS_CONN_TCP) {
        redisContextConnectBindTcp(c, options->endpoint.tcp.ip,
                                   options->endpoint.tcp.port, options->timeout,
                                   options->endpoint.tcp.source_addr);
    } else if (options->type == REDIS_CONN_UNIX) {
        redisContextConnectUnix(c, options->endpoint.unix_socket,
                                options->timeout);
    } else if (options->type == REDIS_CONN_USERFD) {
        c->fd = options->endpoint.fd;
        c->flags |= REDIS_CONNECTED;
    } else {
        // Unknown type - FIXME - FREE
        return NULL;
    }
    if (options->timeout != NULL && (c->flags & REDIS_BLOCK) && c->fd != REDIS_INVALID_FD) {
        redisContextSetTimeout(c, *options->timeout);
    }
    return c;
}