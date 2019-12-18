#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  new_duration; } ;
struct TYPE_13__ {TYPE_3__ input_item_duration_changed; } ;
struct TYPE_14__ {TYPE_4__ u; } ;
typedef  TYPE_5__ vlc_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_6__ libvlc_media_t ;
struct TYPE_10__ {int /*<<< orphan*/  new_duration; } ;
struct TYPE_11__ {TYPE_1__ media_duration_changed; } ;
struct TYPE_16__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_7__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  from_mtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_MediaDurationChanged ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_7__*) ; 

__attribute__((used)) static void input_item_duration_changed( const vlc_event_t *p_event,
                                         void * user_data )
{
    libvlc_media_t * p_md = user_data;
    libvlc_event_t event;

    /* Construct the event */
    event.type = libvlc_MediaDurationChanged;
    event.u.media_duration_changed.new_duration =
        from_mtime(p_event->u.input_item_duration_changed.new_duration);

    /* Send the event */
    libvlc_event_send( &p_md->event_manager, &event );
}