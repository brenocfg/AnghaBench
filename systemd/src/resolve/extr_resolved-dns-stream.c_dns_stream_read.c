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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; scalar_t__ encrypted; } ;
typedef  TYPE_1__ DnsStream ;

/* Variables and functions */
 scalar_t__ dnstls_stream_read (TYPE_1__*,void*,size_t) ; 
 scalar_t__ errno ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t dns_stream_read(DnsStream *s, void *buf, size_t count) {
        ssize_t ss;

#if ENABLE_DNS_OVER_TLS
        if (s->encrypted)
                ss = dnstls_stream_read(s, buf, count);
        else
#endif
        {
                ss = read(s->fd, buf, count);
                if (ss < 0)
                        return -errno;
        }

        return ss;
}