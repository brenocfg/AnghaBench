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
struct TYPE_2__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  p_context; scalar_t__ b_handshaked; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 scalar_t__ SSLClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_SessionShutdown (vlc_tls_t *session, bool duplex) {

    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;

    msg_Dbg(sys->obj, "shutdown TLS session");

    vlc_mutex_destroy(&sys->lock);

    OSStatus ret = noErr;
    VLC_UNUSED(duplex);

    if (sys->b_handshaked) {
        ret = SSLClose(sys->p_context);
    }

    if (ret != noErr) {
        msg_Warn(sys->obj, "Cannot close ssl context (%i)", (int)ret);
        return ret;
    }

    return 0;
}