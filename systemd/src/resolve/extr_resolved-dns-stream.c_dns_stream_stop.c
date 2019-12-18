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
struct TYPE_5__ {int /*<<< orphan*/  fd; void* timeout_event_source; void* io_event_source; } ;
typedef  TYPE_1__ DnsStream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_stream_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 

__attribute__((used)) static void dns_stream_stop(DnsStream *s) {
        assert(s);

        s->io_event_source = sd_event_source_unref(s->io_event_source);
        s->timeout_event_source = sd_event_source_unref(s->timeout_event_source);
        s->fd = safe_close(s->fd);

        /* Disconnect us from the server object if we are now not usable anymore */
        dns_stream_detach(s);
}