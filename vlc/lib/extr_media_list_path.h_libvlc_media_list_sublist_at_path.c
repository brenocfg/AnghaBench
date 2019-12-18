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
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/ * libvlc_media_list_item_at_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_subitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libvlc_media_list_t *
libvlc_media_list_sublist_at_path( libvlc_media_list_t * p_mlist, const libvlc_media_list_path_t path )
{
    libvlc_media_list_t * ret;
    libvlc_media_t * p_md = libvlc_media_list_item_at_path( p_mlist, path );
    if( !p_md )
        return NULL;

    ret = libvlc_media_subitems( p_md );
    libvlc_media_release( p_md );

    return ret;
}