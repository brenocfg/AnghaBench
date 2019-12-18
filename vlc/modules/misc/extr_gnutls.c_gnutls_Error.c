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
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ vlc_tls_gnutls_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EINTR ; 
#define  GNUTLS_E_AGAIN 129 
#define  GNUTLS_E_INTERRUPTED 128 
 int /*<<< orphan*/  WSAECONNRESET ; 
 int /*<<< orphan*/  WSAEINTR ; 
 int /*<<< orphan*/  WSAEWOULDBLOCK ; 
 int /*<<< orphan*/  WSASetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gnutls_error_is_fatal (int) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int gnutls_Error(vlc_tls_gnutls_t *priv, int val)
{
    switch (val)
    {
        case GNUTLS_E_AGAIN:
#ifdef _WIN32
            WSASetLastError (WSAEWOULDBLOCK);
#endif
            errno = EAGAIN;
            break;

        case GNUTLS_E_INTERRUPTED:
#ifdef _WIN32
            WSASetLastError (WSAEINTR);
#endif
            errno = EINTR;
            break;

        default:
            msg_Err(priv->obj, "%s", gnutls_strerror (val));
#ifndef NDEBUG
            if (!gnutls_error_is_fatal (val))
                msg_Err(priv->obj, "Error above should be handled");
#endif
#ifdef _WIN32
            WSASetLastError (WSAECONNRESET);
#endif
            errno = ECONNRESET;
    }
    return -1;
}