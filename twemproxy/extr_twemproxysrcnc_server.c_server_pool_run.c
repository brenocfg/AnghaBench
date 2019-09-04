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
struct server_pool {int dist_type; int /*<<< orphan*/  server; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DIST_KETAMA 130 
#define  DIST_MODULA 129 
#define  DIST_RANDOM 128 
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
 scalar_t__ array_n (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ketama_update (struct server_pool*) ; 
 int /*<<< orphan*/  modula_update (struct server_pool*) ; 
 int /*<<< orphan*/  random_update (struct server_pool*) ; 

rstatus_t
server_pool_run(struct server_pool *pool)
{
    ASSERT(array_n(&pool->server) != 0);

    switch (pool->dist_type) {
    case DIST_KETAMA:
        return ketama_update(pool);

    case DIST_MODULA:
        return modula_update(pool);

    case DIST_RANDOM:
        return random_update(pool);

    default:
        NOT_REACHED();
        return NC_ERROR;
    }

    return NC_OK;
}