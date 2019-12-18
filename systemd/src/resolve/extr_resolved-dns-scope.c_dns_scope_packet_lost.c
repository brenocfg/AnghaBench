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
typedef  int usec_t ;
struct TYPE_4__ {int resend_timeout; } ;
typedef  TYPE_1__ DnsScope ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULTICAST_RESEND_TIMEOUT_MAX_USEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void dns_scope_packet_lost(DnsScope *s, usec_t usec) {
        assert(s);

        if (s->resend_timeout <= usec)
                s->resend_timeout = MIN(s->resend_timeout * 2, MULTICAST_RESEND_TIMEOUT_MAX_USEC);
}