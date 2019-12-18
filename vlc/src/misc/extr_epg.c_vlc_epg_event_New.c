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
typedef  int /*<<< orphan*/  vlc_epg_event_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  vlc_epg_event_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vlc_epg_event_t * vlc_epg_event_New(uint16_t i_id,
                                    int64_t i_start, uint32_t i_duration)
{
    vlc_epg_event_t *p_event = (vlc_epg_event_t *) malloc(sizeof(*p_event));
    if(p_event)
        vlc_epg_event_Init(p_event, i_id, i_start, i_duration);

    return p_event;
}