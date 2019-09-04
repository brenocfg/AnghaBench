#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int _redisContextConnectTcp (int /*<<< orphan*/ *,char const*,int,struct timeval const*,char const*) ; 

int redisContextConnectBindTcp(redisContext *c, const char *addr, int port,
                               const struct timeval *timeout,
                               const char *source_addr) {
    return _redisContextConnectTcp(c, addr, port, timeout, source_addr);
}