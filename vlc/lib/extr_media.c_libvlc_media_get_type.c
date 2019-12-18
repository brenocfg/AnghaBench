#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_type_t ;
struct TYPE_5__ {TYPE_2__* p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_6__ {int i_type; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ input_item_t ;
typedef  enum input_item_type_e { ____Placeholder_input_item_type_e } input_item_type_e ;

/* Variables and functions */
#define  ITEM_TYPE_DIRECTORY 133 
#define  ITEM_TYPE_DISC 132 
#define  ITEM_TYPE_FILE 131 
#define  ITEM_TYPE_NODE 130 
#define  ITEM_TYPE_PLAYLIST 129 
#define  ITEM_TYPE_STREAM 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_type_directory ; 
 int /*<<< orphan*/  libvlc_media_type_disc ; 
 int /*<<< orphan*/  libvlc_media_type_file ; 
 int /*<<< orphan*/  libvlc_media_type_playlist ; 
 int /*<<< orphan*/  libvlc_media_type_stream ; 
 int /*<<< orphan*/  libvlc_media_type_unknown ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

libvlc_media_type_t libvlc_media_get_type( libvlc_media_t *p_md )
{
    assert( p_md );

    enum input_item_type_e i_type;
    input_item_t *p_input_item = p_md->p_input_item;

    vlc_mutex_lock( &p_input_item->lock );
    i_type = p_md->p_input_item->i_type;
    vlc_mutex_unlock( &p_input_item->lock );

    switch( i_type )
    {
    case ITEM_TYPE_FILE:
        return libvlc_media_type_file;
    case ITEM_TYPE_NODE:
    case ITEM_TYPE_DIRECTORY:
        return libvlc_media_type_directory;
    case ITEM_TYPE_DISC:
        return libvlc_media_type_disc;
    case ITEM_TYPE_STREAM:
        return libvlc_media_type_stream;
    case ITEM_TYPE_PLAYLIST:
        return libvlc_media_type_playlist;
    default:
        return libvlc_media_type_unknown;
    }
}