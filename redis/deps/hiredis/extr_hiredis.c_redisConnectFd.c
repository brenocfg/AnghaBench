#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {TYPE_1__ endpoint; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ redisOptions ;
typedef  int /*<<< orphan*/  redisFD ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CONN_USERFD ; 
 int /*<<< orphan*/ * redisConnectWithOptions (TYPE_2__*) ; 

redisContext *redisConnectFd(redisFD fd) {
    redisOptions options = {0};
    options.type = REDIS_CONN_USERFD;
    options.endpoint.fd = fd;
    return redisConnectWithOptions(&options);
}