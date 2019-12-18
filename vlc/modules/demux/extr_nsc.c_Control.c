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
typedef  int va_list ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 

__attribute__((used)) static int Control( demux_t *p_demux, int i_query, va_list args )
{
    VLC_UNUSED( p_demux ); VLC_UNUSED( i_query ); VLC_UNUSED( args );
    //FIXME
    return VLC_EGENERIC;
}