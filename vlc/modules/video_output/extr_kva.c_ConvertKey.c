#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_2__ {scalar_t__ i_pmkey; int i_vlckey; } ;

/* Variables and functions */
 TYPE_1__* pmkeys_to_vlckeys ; 

__attribute__((used)) static int ConvertKey( USHORT i_pmkey )
{
    int i;
    for( i = 0; pmkeys_to_vlckeys[ i ].i_pmkey != 0; i++ )
    {
        if( pmkeys_to_vlckeys[ i ].i_pmkey == i_pmkey )
            return pmkeys_to_vlckeys[ i ].i_vlckey;
    }
    return 0;
}