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
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 char* libvlc_media_get_mrl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
path_to_mrl(libvlc_instance_t *p_vlc, const char *psz_path)
{
    libvlc_media_t *p_m = libvlc_media_new_path(p_vlc, psz_path);
    char *psz_mrl = libvlc_media_get_mrl(p_m);
    libvlc_media_release(p_m);
    return psz_mrl;
}