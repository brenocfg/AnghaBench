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
typedef  int /*<<< orphan*/  tv ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {struct timeval* timeout; } ;
struct TYPE_5__ {TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 struct timeval* calloc (int,int) ; 

void redisAsyncSetTimeout(redisAsyncContext *ac, struct timeval tv) {
    if (!ac->c.timeout) {
        ac->c.timeout = calloc(1, sizeof(tv));
    }

    if (tv.tv_sec == ac->c.timeout->tv_sec &&
        tv.tv_usec == ac->c.timeout->tv_usec) {
        return;
    }

    *ac->c.timeout = tv;
}