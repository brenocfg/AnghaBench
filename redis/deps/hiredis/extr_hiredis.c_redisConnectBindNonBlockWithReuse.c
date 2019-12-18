#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* source_addr; } ;
struct TYPE_7__ {TYPE_1__ tcp; } ;
struct TYPE_8__ {int options; TYPE_2__ endpoint; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ redisOptions ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_OPTIONS_SET_TCP (TYPE_3__*,char const*,int) ; 
 int REDIS_OPT_NONBLOCK ; 
 int REDIS_OPT_REUSEADDR ; 
 int /*<<< orphan*/ * redisConnectWithOptions (TYPE_3__*) ; 

redisContext *redisConnectBindNonBlockWithReuse(const char *ip, int port,
                                                const char *source_addr) {
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, ip, port);
    options.endpoint.tcp.source_addr = source_addr;
    options.options |= REDIS_OPT_NONBLOCK|REDIS_OPT_REUSEADDR;
    return redisConnectWithOptions(&options);
}