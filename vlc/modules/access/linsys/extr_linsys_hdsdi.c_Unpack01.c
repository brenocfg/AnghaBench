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
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  Y1 ; 
 int /*<<< orphan*/  Y2 ; 

__attribute__((used)) static void Unpack01( const uint8_t *p_line, unsigned int i_size,
                      uint8_t *p_y, uint8_t *p_u, uint8_t *p_v )
{
    const uint8_t *p_end = p_line + i_size;

    while ( p_line < p_end )
    {
        *p_u++ = U;
        *p_y++ = Y1;
        *p_v++ = V;
        *p_y++ = Y2;
        p_line += 4;
    }
}