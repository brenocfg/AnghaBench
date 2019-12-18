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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPGA_VERSION (int) ; 

__attribute__((used)) static int MpgaGetFrameSamples( uint32_t h )
{
    const int i_layer = 3 - (((h)>>17)&0x03);
    switch( i_layer )
    {
    case 0:
        return 384;
    case 1:
        return 1152;
    case 2:
        return MPGA_VERSION(h) ? 576 : 1152;
    default:
        return 0;
    }
}