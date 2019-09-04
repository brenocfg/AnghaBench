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

/* Variables and functions */
 int pointer_size ; 
 unsigned int win32_packing ; 
 unsigned int win64_packing ; 

__attribute__((used)) static inline unsigned int clamp_align(unsigned int align)
{
    unsigned int packing = (pointer_size == 4) ? win32_packing : win64_packing;
    if(align > packing) align = packing;
    return align;
}