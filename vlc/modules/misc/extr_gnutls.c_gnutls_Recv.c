#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_3__ {int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;
struct iovec {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  gnutls_session_t ;

/* Variables and functions */
 scalar_t__ gnutls_Error (TYPE_1__*,scalar_t__) ; 
 scalar_t__ gnutls_record_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t gnutls_Recv(vlc_tls_t *tls, struct iovec *iov, unsigned count)
{
    vlc_tls_gnutls_t *priv = (vlc_tls_gnutls_t *)tls;
    gnutls_session_t session = priv->session;
    size_t rcvd = 0;

    while (count > 0)
    {
        ssize_t val = gnutls_record_recv(session, iov->iov_base, iov->iov_len);
        if (val < 0)
            return rcvd ? (ssize_t)rcvd : gnutls_Error(priv, val);

        rcvd += val;

        if ((size_t)val < iov->iov_len)
            break;

        iov++;
        count--;
    }

    return rcvd;
}