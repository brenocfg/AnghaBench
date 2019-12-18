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
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_ITEM_URI_NOP ; 
 int /*<<< orphan*/ * input_item_New (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_from_input_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/ * media_get_subitems (int /*<<< orphan*/ *,int) ; 

libvlc_media_t * libvlc_media_new_as_node( libvlc_instance_t *p_instance,
                                           const char * psz_name )
{
    input_item_t * p_input_item;
    libvlc_media_t * p_md;
    libvlc_media_list_t * p_subitems;

    p_input_item = input_item_New( INPUT_ITEM_URI_NOP, psz_name );

    if (!p_input_item)
    {
        libvlc_printerr( "Not enough memory" );
        return NULL;
    }

    p_md = libvlc_media_new_from_input_item( p_instance, p_input_item );
    input_item_Release( p_input_item );

    p_subitems = media_get_subitems( p_md, true );
    if( p_subitems == NULL) {
        libvlc_media_release( p_md );
        return NULL;
    }

    return p_md;
}