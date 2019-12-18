#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ parsed_status; int is_parsed; int has_asked_preparse; int /*<<< orphan*/  event_manager; int /*<<< orphan*/  parsed_lock; int /*<<< orphan*/  parsed_cond; } ;
typedef  TYPE_3__ libvlc_media_t ;
typedef  scalar_t__ libvlc_media_parsed_status_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
struct TYPE_8__ {scalar_t__ new_status; } ;
struct TYPE_9__ {TYPE_1__ media_parsed_changed; } ;
struct TYPE_11__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaParsedChanged ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  libvlc_media_list_internal_end_reached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_media_parsed_status_done ; 
 int /*<<< orphan*/ * media_get_subitems (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_parsed_changed( libvlc_media_t *p_md,
                                 libvlc_media_parsed_status_t new_status )
{
    libvlc_event_t event;

    vlc_mutex_lock( &p_md->parsed_lock );
    if( p_md->parsed_status == new_status )
    {
        vlc_mutex_unlock( &p_md->parsed_lock );
        return;
    }

    /* Legacy: notify libvlc_media_parse */
    if( !p_md->is_parsed )
    {
        p_md->is_parsed = true;
        vlc_cond_broadcast( &p_md->parsed_cond );
    }

    p_md->parsed_status = new_status;
    if( p_md->parsed_status != libvlc_media_parsed_status_done )
        p_md->has_asked_preparse = false;

    vlc_mutex_unlock( &p_md->parsed_lock );

    if( new_status == libvlc_media_parsed_status_done )
    {
        libvlc_media_list_t *p_subitems = media_get_subitems( p_md, false );
        if( p_subitems != NULL )
        {
            /* notify the media list */
            libvlc_media_list_lock( p_subitems );
            libvlc_media_list_internal_end_reached( p_subitems );
            libvlc_media_list_unlock( p_subitems );
        }
    }

    /* Construct the event */
    event.type = libvlc_MediaParsedChanged;
    event.u.media_parsed_changed.new_status = new_status;

    /* Send the event */
    libvlc_event_send( &p_md->event_manager, &event );
}