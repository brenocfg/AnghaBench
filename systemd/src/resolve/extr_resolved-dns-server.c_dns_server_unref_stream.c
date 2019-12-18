#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  DnsStream ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/ * TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_stream_unref (int /*<<< orphan*/ *) ; 

void dns_server_unref_stream(DnsServer *s) {
        DnsStream *ref;

        assert(s);

        /* Detaches the default stream of this server. Some special care needs to be taken here, as that stream and
         * this server reference each other. First, take the stream out of the server. It's destructor will check if it
         * is registered with us, hence let's invalidate this separately, so that it is already unregistered. */
        ref = TAKE_PTR(s->stream);

        /* And then, unref it */
        dns_stream_unref(ref);
}