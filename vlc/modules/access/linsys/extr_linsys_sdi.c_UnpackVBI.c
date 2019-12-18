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
 int U ; 
 int V ; 
 int Y1 ; 
 int Y2 ; 

__attribute__((used)) static void UnpackVBI( const uint8_t *p_line, unsigned int i_size,
                       uint8_t *p_dest )
{
    const uint8_t *p_end = p_line + i_size;

    while ( p_line < p_end )
    {
        *p_dest++ = (U + 2) / 4;
        *p_dest++ = (Y1 + 2) / 4;
        *p_dest++ = (V + 2) / 4;
        *p_dest++ = (Y2 + 2) / 4;
        p_line += 5;
    }
}