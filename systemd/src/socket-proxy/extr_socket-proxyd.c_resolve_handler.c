#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  resolve_query; } ;
typedef  TYPE_1__ sd_resolve_query ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  connection_free (TYPE_1__*) ; 
 int connection_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_resolve_query_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resolve_handler(sd_resolve_query *q, int ret, const struct addrinfo *ai, Connection *c) {
        assert(q);
        assert(c);

        if (ret != 0) {
                log_error("Failed to resolve host: %s", gai_strerror(ret));
                goto fail;
        }

        c->resolve_query = sd_resolve_query_unref(c->resolve_query);

        return connection_start(c, ai->ai_addr, ai->ai_addrlen);

fail:
        connection_free(c);
        return 0; /* ignore errors, continue serving */
}