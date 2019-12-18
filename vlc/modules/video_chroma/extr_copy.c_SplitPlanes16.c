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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPLIT_PLANES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLIT_PLANES_SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SPLIT_PLANES_SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uint16_t ; 

__attribute__((used)) static void SplitPlanes16(uint8_t *dstu, size_t dstu_pitch,
                          uint8_t *dstv, size_t dstv_pitch,
                          const uint8_t *src, size_t src_pitch, unsigned height,
                          int bitshift)
{
    if (bitshift == 0)
        SPLIT_PLANES(uint16_t, 4);
    else if (bitshift > 0)
        SPLIT_PLANES_SHIFTR(uint16_t, 4, bitshift & 0xf);
    else
        SPLIT_PLANES_SHIFTL(uint16_t, 4, (-bitshift) & 0xf);
}