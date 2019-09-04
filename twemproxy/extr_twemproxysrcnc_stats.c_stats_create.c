#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct stats {int interval; int sd; int /*<<< orphan*/  sum; int /*<<< orphan*/  shadow; int /*<<< orphan*/  current; scalar_t__ aggregate; scalar_t__ updated; int /*<<< orphan*/  ncurr_conn_str; int /*<<< orphan*/  ntotal_conn_str; int /*<<< orphan*/  timestamp_str; int /*<<< orphan*/  uptime_str; int /*<<< orphan*/  version; int /*<<< orphan*/  version_str; int /*<<< orphan*/  source; int /*<<< orphan*/  source_str; int /*<<< orphan*/  service; int /*<<< orphan*/  service_str; scalar_t__ tid; TYPE_1__ buf; scalar_t__ start_ts; int /*<<< orphan*/  addr; int /*<<< orphan*/  port; } ;
struct array {int dummy; } ;
typedef  scalar_t__ rstatus_t ;
typedef  scalar_t__ pthread_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 char* NC_VERSION_STRING ; 
 int /*<<< orphan*/  array_null (int /*<<< orphan*/ *) ; 
 struct stats* nc_alloc (int) ; 
 scalar_t__ stats_create_buf (struct stats*) ; 
 int /*<<< orphan*/  stats_destroy (struct stats*) ; 
 scalar_t__ stats_pool_map (int /*<<< orphan*/ *,struct array*) ; 
 scalar_t__ stats_start_aggregator (struct stats*) ; 
 int /*<<< orphan*/  string_set_raw (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_set_text (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

struct stats *
stats_create(uint16_t stats_port, char *stats_ip, int stats_interval,
             char *source, struct array *server_pool)
{
    rstatus_t status;
    struct stats *st;

    st = nc_alloc(sizeof(*st));
    if (st == NULL) {
        return NULL;
    }

    st->port = stats_port;
    st->interval = stats_interval;
    string_set_raw(&st->addr, stats_ip);

    st->start_ts = (int64_t)time(NULL);

    st->buf.len = 0;
    st->buf.data = NULL;
    st->buf.size = 0;

    array_null(&st->current);
    array_null(&st->shadow);
    array_null(&st->sum);

    st->tid = (pthread_t) -1;
    st->sd = -1;

    string_set_text(&st->service_str, "service");
    string_set_text(&st->service, "nutcracker");

    string_set_text(&st->source_str, "source");
    string_set_raw(&st->source, source);

    string_set_text(&st->version_str, "version");
    string_set_text(&st->version, NC_VERSION_STRING);

    string_set_text(&st->uptime_str, "uptime");
    string_set_text(&st->timestamp_str, "timestamp");

    string_set_text(&st->ntotal_conn_str, "total_connections");
    string_set_text(&st->ncurr_conn_str, "curr_connections");

    st->updated = 0;
    st->aggregate = 0;

    /* map server pool to current (a), shadow (b) and sum (c) */

    status = stats_pool_map(&st->current, server_pool);
    if (status != NC_OK) {
        goto error;
    }

    status = stats_pool_map(&st->shadow, server_pool);
    if (status != NC_OK) {
        goto error;
    }

    status = stats_pool_map(&st->sum, server_pool);
    if (status != NC_OK) {
        goto error;
    }

    status = stats_create_buf(st);
    if (status != NC_OK) {
        goto error;
    }

    status = stats_start_aggregator(st);
    if (status != NC_OK) {
        goto error;
    }

    return st;

error:
    stats_destroy(st);
    return NULL;
}