#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_event; TYPE_1__** pp_event; } ;
typedef  TYPE_2__ vlc_epg_t ;
struct TYPE_4__ {char const* psz_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void assert_events( const vlc_epg_t *p_epg, const char *psz_names, size_t i_names )
{
    assert( p_epg->i_event == i_names );
    for( size_t i = 0; i < p_epg->i_event; i++ )
    {
        assert( p_epg->pp_event[i]->psz_name &&
                p_epg->pp_event[i]->psz_name[0] == psz_names[i] );
    }
}