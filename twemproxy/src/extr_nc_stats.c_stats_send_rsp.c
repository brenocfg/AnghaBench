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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct stats {int sd; TYPE_1__ buf; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VERB ; 
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nc_sendn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stats_make_rsp (struct stats*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
stats_send_rsp(struct stats *st)
{
    rstatus_t status;
    ssize_t n;
    int sd;

    status = stats_make_rsp(st);
    if (status != NC_OK) {
        return status;
    }

    sd = accept(st->sd, NULL, NULL);
    if (sd < 0) {
        log_error("accept on m %d failed: %s", st->sd, strerror(errno));
        return NC_ERROR;
    }

    log_debug(LOG_VERB, "send stats on sd %d %d bytes", sd, st->buf.len);

    n = nc_sendn(sd, st->buf.data, st->buf.len);
    if (n < 0) {
        log_error("send stats on sd %d failed: %s", sd, strerror(errno));
        close(sd);
        return NC_ERROR;
    }

    close(sd);

    return NC_OK;
}