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
struct TYPE_3__ {int /*<<< orphan*/  obj; scalar_t__ p_context; } ;
typedef  TYPE_1__ vlc_tls_st_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 scalar_t__ SSLDisposeContext (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static void st_SessionClose (vlc_tls_t *session) {

    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;
    msg_Dbg(sys->obj, "close TLS session");

    if (sys->p_context) {
#if TARGET_OS_IPHONE
        CFRelease(sys->p_context);
#else
        if (SSLDisposeContext(sys->p_context) != noErr) {
            msg_Err(sys->obj, "error deleting context");
        }
#endif
    }
    free(sys);
}