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
struct TYPE_5__ {int /*<<< orphan*/  queries; } ;
typedef  TYPE_1__ DnsStream ;
typedef  int /*<<< orphan*/  DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_query_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_stream_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/ * set_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_stub_stream_complete(DnsStream *s, int error) {
        assert(s);

        log_debug_errno(error, "DNS TCP connection terminated, destroying queries: %m");

        for (;;) {
                DnsQuery *q;

                q = set_first(s->queries);
                if (!q)
                        break;

                dns_query_free(q);
        }

        /* This drops the implicit ref we keep around since it was allocated, as incoming stub connections
         * should be kept as long as the client wants to. */
        dns_stream_unref(s);
        return 0;
}