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
typedef  int uint_fast16_t ;
typedef  int uint8_t ;
typedef  int int_fast16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int_fast16_t dat12tos16( uint_fast16_t y )
{
    static const int16_t diff[16] = {
       0x0000, 0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600,
       0x0A00, 0x0B00, 0x0C00, 0x0D00, 0x0E00, 0x0F00, 0x1000, 0x1000,
    };
    static const uint8_t shift[16] = {
        0, 0, 1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1, 0, 0
    };

    assert(y < 0x1000);

    int d = y >> 8;
    return ((int)y - diff[d]) << shift[d];
}