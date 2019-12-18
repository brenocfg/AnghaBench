#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * description_items; scalar_t__ i_description_items; int /*<<< orphan*/  i_duration; int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_1__ vlc_epg_event_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlc_epg_event_Init(vlc_epg_event_t *p_event, uint16_t i_id,
                               int64_t i_start, uint32_t i_duration)
{
    memset(p_event, 0, sizeof(*p_event));
    p_event->i_start = i_start;
    p_event->i_id = i_id;
    p_event->i_duration = i_duration;
    p_event->i_description_items = 0;
    p_event->description_items = NULL;
}