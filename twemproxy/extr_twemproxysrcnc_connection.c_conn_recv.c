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
struct conn {int recv_ready; size_t recv_bytes; int eof; int /*<<< orphan*/  sd; scalar_t__ err; int /*<<< orphan*/  send_bytes; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_VERB ; 
 scalar_t__ NC_EAGAIN ; 
 scalar_t__ NC_ERROR ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nc_read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

ssize_t
conn_recv(struct conn *conn, void *buf, size_t size)
{
    ssize_t n;

    ASSERT(buf != NULL);
    ASSERT(size > 0);
    ASSERT(conn->recv_ready);

    for (;;) {
        n = nc_read(conn->sd, buf, size);

        log_debug(LOG_VERB, "recv on sd %d %zd of %zu", conn->sd, n, size);

        if (n > 0) {
            if (n < (ssize_t) size) {
                conn->recv_ready = 0;
            }
            conn->recv_bytes += (size_t)n;
            return n;
        }

        if (n == 0) {
            conn->recv_ready = 0;
            conn->eof = 1;
            log_debug(LOG_INFO, "recv on sd %d eof rb %zu sb %zu", conn->sd,
                      conn->recv_bytes, conn->send_bytes);
            return n;
        }

        if (errno == EINTR) {
            log_debug(LOG_VERB, "recv on sd %d not ready - eintr", conn->sd);
            continue;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            conn->recv_ready = 0;
            log_debug(LOG_VERB, "recv on sd %d not ready - eagain", conn->sd);
            return NC_EAGAIN;
        } else {
            conn->recv_ready = 0;
            conn->err = errno;
            log_error("recv on sd %d failed: %s", conn->sd, strerror(errno));
            return NC_ERROR;
        }
    }

    NOT_REACHED();

    return NC_ERROR;
}