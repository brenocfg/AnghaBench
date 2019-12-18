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

/* Variables and functions */

__attribute__((used)) static void EITDecodeMjd( int i_mjd, int *p_y, int *p_m, int *p_d )
{
    const int yp = (int)( ( (double)i_mjd - 15078.2)/365.25 );
    const int mp = (int)( ((double)i_mjd - 14956.1 - (int)(yp * 365.25)) / 30.6001 );
    const int c = ( mp == 14 || mp == 15 ) ? 1 : 0;

    *p_y = 1900 + yp + c*1;
    *p_m = mp - 1 - c*12;
    *p_d = i_mjd - 14956 - (int)(yp*365.25) - (int)(mp*30.6001);
}