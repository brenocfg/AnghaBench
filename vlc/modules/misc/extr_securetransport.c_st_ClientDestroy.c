#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ whitelist; } ;
typedef  TYPE_1__ vlc_tls_creds_sys_t ;
struct TYPE_7__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_tls_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static void st_ClientDestroy (vlc_tls_client_t *crd) {
    msg_Dbg(crd, "close secure transport client");

    vlc_tls_creds_sys_t *sys = crd->sys;

    if (sys->whitelist)
        CFRelease(sys->whitelist);

    free(sys);
}