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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_OSD ; 
 scalar_t__ VoutSnapshotPip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_OSDMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void VoutOsdSnapshot( vout_thread_t *p_vout, picture_t *p_pic, const char *psz_filename )
{
    msg_Dbg( p_vout, "snapshot taken (%s)", psz_filename );
    vout_OSDMessage( p_vout, VOUT_SPU_CHANNEL_OSD, "%s", psz_filename );

    if( var_InheritBool( p_vout, "snapshot-preview" ) )
    {
        if( VoutSnapshotPip( p_vout, p_pic ) )
            msg_Warn( p_vout, "Failed to display snapshot" );
    }
}