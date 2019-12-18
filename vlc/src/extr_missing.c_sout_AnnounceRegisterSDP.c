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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  session_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

session_descriptor_t *sout_AnnounceRegisterSDP (vlc_object_t *obj,
                                                const char *sdp,
                                                const char *dst)
{
    VLC_UNUSED (sdp); VLC_UNUSED (dst);
    msg_Err (obj, "SDP export not compiled-in!");
    return NULL;
}