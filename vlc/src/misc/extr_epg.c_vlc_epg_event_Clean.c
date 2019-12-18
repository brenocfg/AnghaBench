#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_description_items; TYPE_3__* psz_name; TYPE_3__* psz_short_description; TYPE_3__* psz_description; TYPE_3__* description_items; } ;
typedef  TYPE_1__ vlc_epg_event_t ;
struct TYPE_5__ {struct TYPE_5__* psz_value; struct TYPE_5__* psz_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void vlc_epg_event_Clean(vlc_epg_event_t *p_event)
{
    for(int i=0; i<p_event->i_description_items; i++)
    {
        free(p_event->description_items[i].psz_key);
        free(p_event->description_items[i].psz_value);
    }
    free(p_event->description_items);
    free(p_event->psz_description);
    free(p_event->psz_short_description);
    free(p_event->psz_name);
}