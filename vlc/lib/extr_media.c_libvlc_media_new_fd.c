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
typedef  int /*<<< orphan*/  mrl ;
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/ * libvlc_media_new_location (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

libvlc_media_t *libvlc_media_new_fd( libvlc_instance_t *p_instance, int fd )
{
    char mrl[16];
    snprintf( mrl, sizeof(mrl), "fd://%d", fd );

    return libvlc_media_new_location( p_instance, mrl );
}