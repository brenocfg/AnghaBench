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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_parse_flag_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ media_parse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

int
libvlc_media_parse_with_options( libvlc_media_t *media,
                                 libvlc_media_parse_flag_t parse_flag,
                                 int timeout )
{
    return media_parse( media, true, parse_flag, timeout ) == VLC_SUCCESS ? 0 : -1;
}