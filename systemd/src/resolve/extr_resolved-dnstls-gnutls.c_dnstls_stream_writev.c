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
struct iovec {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ gnutls_transport_ptr_t ;
typedef  int /*<<< orphan*/  giovec_t ;
typedef  int /*<<< orphan*/  DnsStream ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_STREAM_WRITE_TLS_DATA ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int dns_stream_writev (int /*<<< orphan*/ *,struct iovec const*,int,int /*<<< orphan*/ ) ; 
 int errno ; 

__attribute__((used)) static ssize_t dnstls_stream_writev(gnutls_transport_ptr_t p, const giovec_t *iov, int iovcnt) {
        int r;

        assert(p);

        r = dns_stream_writev((DnsStream*) p, (const struct iovec*) iov, iovcnt, DNS_STREAM_WRITE_TLS_DATA);
        if (r < 0) {
                errno = -r;
                return -1;
        }

        return r;
}