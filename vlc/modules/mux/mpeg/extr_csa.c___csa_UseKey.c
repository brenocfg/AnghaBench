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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int use_odd; } ;
typedef  TYPE_1__ csa_t ;

/* Variables and functions */
 int VLC_ENOOBJ ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 

int csa_UseKey( vlc_object_t *p_caller, csa_t *c, bool use_odd )
{
    if ( !c ) return VLC_ENOOBJ;
    c->use_odd = use_odd;
#ifndef TS_NO_CSA_CK_MSG
        msg_Dbg( p_caller, "using the %s key for scrambling",
                 use_odd ? "odd" : "even" );
#endif
    return VLC_SUCCESS;
}