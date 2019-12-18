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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_jvm ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

void
system_Configure(libvlc_int_t *p_libvlc, int i_argc, const char *const pp_argv[])
{
    (void)i_argc; (void)pp_argv;
    assert(s_jvm != NULL);
    var_Create(p_libvlc, "android-jvm", VLC_VAR_ADDRESS);
    var_SetAddress(p_libvlc, "android-jvm", s_jvm);
}