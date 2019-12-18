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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  obj; int /*<<< orphan*/  p_context; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 scalar_t__ SSLRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ errSSLClosedGraceful ; 
 scalar_t__ errSSLClosedNoNotify ; 
 scalar_t__ errSSLWouldBlock ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ noErr ; 
 size_t st_Error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t st_Recv (vlc_tls_t *session, struct iovec *iov, unsigned count)
{
    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;

    if (unlikely(count == 0))
        return 0;

    vlc_mutex_lock(&sys->lock);

    size_t actualSize;
    OSStatus ret = SSLRead(sys->p_context, iov->iov_base, iov->iov_len,
                           &actualSize);

    if (ret == errSSLWouldBlock && actualSize) {
        vlc_mutex_unlock(&sys->lock);
        return actualSize;
    }

    /* peer performed shutdown */
    if (ret == errSSLClosedNoNotify || ret == errSSLClosedGraceful) {
        msg_Dbg(sys->obj, "Got close notification with code %i", (int)ret);
        vlc_mutex_unlock(&sys->lock);
        return 0;
    }

    vlc_mutex_unlock(&sys->lock);
    return ret != noErr ? st_Error(session, ret) : actualSize;
}