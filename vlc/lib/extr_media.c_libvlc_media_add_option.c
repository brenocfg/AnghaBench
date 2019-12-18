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

/* Variables and functions */
 int VLC_INPUT_OPTION_TRUSTED ; 
 int VLC_INPUT_OPTION_UNIQUE ; 
 int /*<<< orphan*/  libvlc_media_add_option_flag (int /*<<< orphan*/ *,char const*,int) ; 

void libvlc_media_add_option( libvlc_media_t * p_md,
                              const char * psz_option )
{
    libvlc_media_add_option_flag( p_md, psz_option,
                          VLC_INPUT_OPTION_UNIQUE|VLC_INPUT_OPTION_TRUSTED );
}