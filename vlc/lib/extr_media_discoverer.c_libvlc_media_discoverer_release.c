#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_libvlc_instance; int /*<<< orphan*/  catname_to_submedialist; int /*<<< orphan*/  p_mlist; int /*<<< orphan*/ * p_sd; } ;
typedef  TYPE_1__ libvlc_media_discoverer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MediaListDictValueRelease ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_discoverer_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
libvlc_media_discoverer_release( libvlc_media_discoverer_t * p_mdis )
{
    if( p_mdis->p_sd != NULL )
        libvlc_media_discoverer_stop( p_mdis );

    libvlc_media_list_release( p_mdis->p_mlist );

    vlc_dictionary_clear( &p_mdis->catname_to_submedialist,
        MediaListDictValueRelease, NULL );

    libvlc_release( p_mdis->p_libvlc_instance );

    free( p_mdis );
}