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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int HasAncillary( const uint8_t *p_anc )
{
    return ( (p_anc[0] == 0x0 && p_anc[1] == 0xfc && p_anc[2] == 0xff
               && (p_anc[3] & 0x3f) == 0x3f) );
}