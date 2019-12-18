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

/* Variables and functions */
 int /*<<< orphan*/  CloseExtraDll () ; 
 int /*<<< orphan*/  dll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dll_handle ; 
 int /*<<< orphan*/  omx_core_mutex ; 
 scalar_t__ omx_refcount ; 
 int /*<<< orphan*/  pf_deinit () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void DeinitOmxCore(void)
{
    vlc_mutex_lock( &omx_core_mutex );
    omx_refcount--;
    if( omx_refcount == 0 )
    {
        pf_deinit();
        dll_close( dll_handle );
        CloseExtraDll();
    }
    vlc_mutex_unlock( &omx_core_mutex );
}