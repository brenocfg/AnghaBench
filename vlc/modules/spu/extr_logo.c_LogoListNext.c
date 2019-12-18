#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_7__ {int i_delay; } ;
typedef  TYPE_1__ logo_t ;
struct TYPE_8__ {int i_counter; int i_count; int i_delay; scalar_t__ i_next_pic; } ;
typedef  TYPE_2__ logo_list_t ;

/* Variables and functions */
 TYPE_1__* LogoListCurrent (TYPE_2__*) ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 

__attribute__((used)) static logo_t *LogoListNext( logo_list_t *p_list, vlc_tick_t i_date )
{
    p_list->i_counter = ( p_list->i_counter + 1 ) % p_list->i_count;

    logo_t *p_logo = LogoListCurrent( p_list );

    p_list->i_next_pic = i_date + VLC_TICK_FROM_MS( p_logo->i_delay != -1 ?
                          p_logo->i_delay : p_list->i_delay );
    return p_logo;
}