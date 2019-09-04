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
typedef  scalar_t__ uint32_t ;
struct stats_server {int /*<<< orphan*/  metric; int /*<<< orphan*/  name; } ;
struct stats_pool {int /*<<< orphan*/  server; int /*<<< orphan*/  metric; int /*<<< orphan*/  name; } ;
struct stats {int /*<<< orphan*/  sum; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 void* array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ array_n (int /*<<< orphan*/ *) ; 
 scalar_t__ stats_add_footer (struct stats*) ; 
 scalar_t__ stats_add_header (struct stats*) ; 
 scalar_t__ stats_begin_nesting (struct stats*,int /*<<< orphan*/ *) ; 
 scalar_t__ stats_copy_metric (struct stats*,int /*<<< orphan*/ *) ; 
 scalar_t__ stats_end_nesting (struct stats*) ; 

__attribute__((used)) static rstatus_t
stats_make_rsp(struct stats *st)
{
    rstatus_t status;
    uint32_t i;

    status = stats_add_header(st);
    if (status != NC_OK) {
        return status;
    }

    for (i = 0; i < array_n(&st->sum); i++) {
        struct stats_pool *stp = array_get(&st->sum, i);
        uint32_t j;

        status = stats_begin_nesting(st, &stp->name);
        if (status != NC_OK) {
            return status;
        }

        /* copy pool metric from sum(c) to buffer */
        status = stats_copy_metric(st, &stp->metric);
        if (status != NC_OK) {
            return status;
        }

        for (j = 0; j < array_n(&stp->server); j++) {
            struct stats_server *sts = array_get(&stp->server, j);

            status = stats_begin_nesting(st, &sts->name);
            if (status != NC_OK) {
                return status;
            }

            /* copy server metric from sum(c) to buffer */
            status = stats_copy_metric(st, &sts->metric);
            if (status != NC_OK) {
                return status;
            }

            status = stats_end_nesting(st);
            if (status != NC_OK) {
                return status;
            }
        }

        status = stats_end_nesting(st);
        if (status != NC_OK) {
            return status;
        }
    }

    status = stats_add_footer(st);
    if (status != NC_OK) {
        return status;
    }

    return NC_OK;
}