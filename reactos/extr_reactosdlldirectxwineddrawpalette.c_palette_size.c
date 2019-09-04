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
typedef  int DWORD ;

/* Variables and functions */
#define  DDPCAPS_1BIT 131 
#define  DDPCAPS_2BIT 130 
#define  DDPCAPS_4BIT 129 
#define  DDPCAPS_8BIT 128 

__attribute__((used)) static unsigned int palette_size(DWORD flags)
{
    switch (flags & (DDPCAPS_1BIT | DDPCAPS_2BIT | DDPCAPS_4BIT | DDPCAPS_8BIT))
    {
        case DDPCAPS_1BIT:
            return 2;
        case DDPCAPS_2BIT:
            return 4;
        case DDPCAPS_4BIT:
            return 16;
        case DDPCAPS_8BIT:
            return 256;
        default:
            return ~0u;
    }
}