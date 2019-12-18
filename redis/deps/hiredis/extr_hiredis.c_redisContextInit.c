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
typedef  int /*<<< orphan*/  redisOptions ;
struct TYPE_5__ {int /*<<< orphan*/ * reader; int /*<<< orphan*/ * obuf; int /*<<< orphan*/  fd; int /*<<< orphan*/ * funcs; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_INVALID_FD ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  redisContextDefaultFuncs ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 
 int /*<<< orphan*/ * redisReaderCreate () ; 
 int /*<<< orphan*/ * sdsempty () ; 

__attribute__((used)) static redisContext *redisContextInit(const redisOptions *options) {
    redisContext *c;

    c = calloc(1, sizeof(*c));
    if (c == NULL)
        return NULL;

    c->funcs = &redisContextDefaultFuncs;
    c->obuf = sdsempty();
    c->reader = redisReaderCreate();
    c->fd = REDIS_INVALID_FD;

    if (c->obuf == NULL || c->reader == NULL) {
        redisFree(c);
        return NULL;
    }
    (void)options; /* options are used in other functions */
    return c;
}