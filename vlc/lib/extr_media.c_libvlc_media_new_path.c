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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * libvlc_media_new_location (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

libvlc_media_t *libvlc_media_new_path( libvlc_instance_t *p_instance,
                                       const char *path )
{
    char *mrl = vlc_path2uri( path, NULL );
    if( unlikely(mrl == NULL) )
    {
        libvlc_printerr( "%s", vlc_strerror_c(errno) );
        return NULL;
    }

    libvlc_media_t *m = libvlc_media_new_location( p_instance, mrl );
    free( mrl );
    return m;
}