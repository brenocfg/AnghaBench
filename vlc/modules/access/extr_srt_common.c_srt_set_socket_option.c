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
typedef  int /*<<< orphan*/  SRT_SOCKOPT ;
typedef  int /*<<< orphan*/  SRTSOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srt_getlasterror_str () ; 
 int srt_setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

int srt_set_socket_option(vlc_object_t *this, const char *srt_param,
        SRTSOCKET u, SRT_SOCKOPT opt, const void *optval, int optlen)
{
    int stat = 0;

    stat = srt_setsockopt( u, 0, opt, optval, optlen );
    if (stat)
    msg_Err( this, "Failed to set socket option %s (reason: %s)", srt_param,
            srt_getlasterror_str() );

    return stat;
}