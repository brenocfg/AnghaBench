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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  A0 ; 
 int /*<<< orphan*/  A1 ; 
 int /*<<< orphan*/  A2 ; 
 int /*<<< orphan*/  A3 ; 

__attribute__((used)) static void UnpackAnc( const uint8_t *p_anc, unsigned int i_size,
                       uint16_t *p_dest )
{
    const uint8_t *p_end = p_anc + i_size;

    while ( p_anc <= p_end - 5 )
    {
        *p_dest++ = A0;
        *p_dest++ = A1;
        *p_dest++ = A2;
        *p_dest++ = A3;
        p_anc += 5;
    }
}