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
struct conf {int /*<<< orphan*/  pool; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ array_n (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_pool_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_pop_scalar (struct conf*) ; 
 int /*<<< orphan*/  nc_free (struct conf*) ; 

void
conf_destroy(struct conf *cf)
{
    while (array_n(&cf->arg) != 0) {
        conf_pop_scalar(cf);
    }
    array_deinit(&cf->arg);

    while (array_n(&cf->pool) != 0) {
        conf_pool_deinit(array_pop(&cf->pool));
    }
    array_deinit(&cf->pool);

    nc_free(cf);
}