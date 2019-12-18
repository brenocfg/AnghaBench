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
typedef  int /*<<< orphan*/  vlc_epg_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  vlc_epg_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vlc_epg_t *vlc_epg_New( uint32_t i_id, uint16_t i_source_id )
{
    vlc_epg_t *p_epg = malloc( sizeof(*p_epg) );
    if( p_epg )
        vlc_epg_Init( p_epg, i_id, i_source_id );
    return p_epg;
}