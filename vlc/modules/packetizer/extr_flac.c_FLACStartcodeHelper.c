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
 int* memchr (int const*,int,int) ; 

__attribute__((used)) static const uint8_t * FLACStartcodeHelper(const uint8_t *p, const uint8_t *end)
{
    while( p && p < end )
    {
        if( (p = memchr(p, 0xFF, end - p)) )
        {
            if( end - p > 1 && (p[1] & 0xFE) == 0xF8 )
                return p;
            else
                p++;
        }
    }
    return NULL;
}