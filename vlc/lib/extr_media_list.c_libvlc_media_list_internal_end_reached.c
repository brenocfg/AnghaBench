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
struct TYPE_5__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_media_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaListEndReached ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 

void libvlc_media_list_internal_end_reached( libvlc_media_list_t * p_mlist )
{
    libvlc_event_t event;

    event.type = libvlc_MediaListEndReached;

    /* Send the event */
    libvlc_event_send( &p_mlist->event_manager, &event );
}