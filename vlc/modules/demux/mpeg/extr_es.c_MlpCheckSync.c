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
 int /*<<< orphan*/  VLC_UNUSED (unsigned int*) ; 

__attribute__((used)) static int MlpCheckSync( const uint8_t *p_peek, unsigned *pi_samples )
{
    if( p_peek[4+0] != 0xf8 || p_peek[4+1] != 0x72 || p_peek[4+2] != 0x6f )
        return -1;

    if( p_peek[4+3] != 0xbb )
        return -1;

    /* TODO checksum and real size for robustness */
    VLC_UNUSED(pi_samples);
    return 0;
}