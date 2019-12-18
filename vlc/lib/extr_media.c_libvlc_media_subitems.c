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

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * media_get_subitems (int /*<<< orphan*/ *,int) ; 

libvlc_media_list_t *
libvlc_media_subitems( libvlc_media_t * p_md )
{
    libvlc_media_list_t *p_subitems = media_get_subitems( p_md, true );
    if( p_subitems )
        libvlc_media_list_retain( p_subitems );
    return p_subitems;
}