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
 int GetDWBE (int const*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 

__attribute__((used)) static bool ID3TAG_IsTag( const uint8_t *p_buffer, bool b_footer )
{
    return( memcmp(p_buffer, (b_footer) ? "3DI" : "ID3", 3) == 0 &&
            p_buffer[3] < 0xFF &&
            p_buffer[4] < 0xFF &&
           ((GetDWBE(&p_buffer[6]) & 0x80808080) == 0) );
}