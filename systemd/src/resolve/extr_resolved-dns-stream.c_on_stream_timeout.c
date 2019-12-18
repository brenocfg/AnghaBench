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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  DnsStream ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_stream_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_stream_timeout(sd_event_source *es, usec_t usec, void *userdata) {
        DnsStream *s = userdata;

        assert(s);

        return dns_stream_complete(s, ETIMEDOUT);
}