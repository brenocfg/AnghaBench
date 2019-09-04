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
struct stats {int /*<<< orphan*/  tid; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stats*) ; 
 int /*<<< orphan*/  stats_enabled ; 
 scalar_t__ stats_listen (struct stats*) ; 
 int /*<<< orphan*/  stats_loop ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static rstatus_t
stats_start_aggregator(struct stats *st)
{
    rstatus_t status;

    if (!stats_enabled) {
        return NC_OK;
    }

    status = stats_listen(st);
    if (status != NC_OK) {
        return status;
    }

    status = pthread_create(&st->tid, NULL, stats_loop, st);
    if (status < 0) {
        log_error("stats aggregator create failed: %s", strerror(status));
        return NC_ERROR;
    }

    return NC_OK;
}