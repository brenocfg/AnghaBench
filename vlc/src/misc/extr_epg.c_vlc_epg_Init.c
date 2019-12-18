#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_present; int /*<<< orphan*/  pp_event; int /*<<< orphan*/  i_event; int /*<<< orphan*/ * p_current; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/  i_source_id; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ vlc_epg_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_epg_Init( vlc_epg_t *p_epg, uint32_t i_id, uint16_t i_source_id )
{
    p_epg->i_id = i_id;
    p_epg->i_source_id = i_source_id;
    p_epg->psz_name = NULL;
    p_epg->p_current = NULL;
    p_epg->b_present = false;
    TAB_INIT( p_epg->i_event, p_epg->pp_event );
}