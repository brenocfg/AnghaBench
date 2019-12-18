#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_2__ {size_t i_send_buffered_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_context; scalar_t__ b_server_mode; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
struct iovec {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int ssize_t ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 scalar_t__ SSLWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*) ; 
 scalar_t__ errSSLWouldBlock ; 
 int errno ; 
 scalar_t__ noErr ; 
 int st_Error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t st_Send (vlc_tls_t *session, const struct iovec *iov,
                        unsigned count)
{
    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;
    OSStatus ret = noErr;

    if (unlikely(count == 0))
        return 0;

    vlc_mutex_lock(&sys->lock);

    /*
     * SSLWrite does not return the number of bytes actually written to
     * the socket, but the number of bytes written to the internal cache.
     *
     * If return value is errSSLWouldBlock, the underlying socket cannot
     * send all data, but the data is already cached. In this situation,
     * we need to call SSLWrite again. To ensure this call even for the
     * last bytes, we return EAGAIN. On the next call, we give no new data
     * to SSLWrite until the error is not errSSLWouldBlock anymore.
     *
     * This code is adapted the same way as done in curl.
     * (https://github.com/bagder/curl/blob/master/lib/curl_darwinssl.c#L2067)
     */

    /* EAGAIN is not expected by net_Write in this situation,
       so use EINTR here */
    int againErr = sys->b_server_mode ? EAGAIN : EINTR;

    size_t actualSize;
    if (sys->i_send_buffered_bytes > 0) {
        ret = SSLWrite(sys->p_context, NULL, 0, &actualSize);

        if (ret == noErr) {
            /* actualSize remains zero because no new data send */
            actualSize = sys->i_send_buffered_bytes;
            sys->i_send_buffered_bytes = 0;

        } else if (ret == errSSLWouldBlock) {
            vlc_mutex_unlock(&sys->lock);
            errno = againErr;
            return -1;
        }

    } else {
        ret = SSLWrite(sys->p_context, iov->iov_base, iov->iov_len,
                       &actualSize);

        if (ret == errSSLWouldBlock) {
            sys->i_send_buffered_bytes = iov->iov_len;
            errno = againErr;
            vlc_mutex_unlock(&sys->lock);
            return -1;
        }
    }

    vlc_mutex_unlock(&sys->lock);
    return ret != noErr ? st_Error(session, ret) : actualSize;
}